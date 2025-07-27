#include "Nl80211Driver.h"

#include <cstring>
#include <functional>
#include <iostream>
#include <linux/nl80211.h>
#include <net/if.h>
#include <netlink/attr.h>
#include <netlink/genl/ctrl.h>
#include <netlink/genl/family.h>
#include <netlink/genl/genl.h>
#include <netlink/msg.h>
#include <netlink/netlink.h>
#include <string>
#include <unistd.h>

#include "Nl80211Util.h"

struct NetlinkCallbackContext {
    std::unique_ptr<NetlinkCallback> valid;
    std::unique_ptr<NetlinkErrCallback> error;
    int32_t counter;
};

struct Socket {
    std::unique_ptr<NetlinkCallbackContext> m_context;
    std::string m_interfaceName;
    int32_t m_ifIdx;
    int32_t m_devId;

    nl_sock* pHandle;
};

static int errorHandler(sockaddr_nl* nla, nlmsgerr* nlerr, void* arg) {
    NetlinkCallbackContext* context = static_cast<NetlinkCallbackContext*>(arg);
    if (!context || !context->error) {
        std::cerr << "No error callback provided for netlink message" << std::endl;
        return NL_SKIP;
    }

    // call the error callback
    int result = (*(context->error))(nlerr);
    context->counter = 0;

    return result;
}

static int validHandler(nl_msg* msg, void* arg) {
    NetlinkCallbackContext* context = static_cast<NetlinkCallbackContext*>(arg);
    if (!context || !context->valid) {
        std::cerr << "No valid callback provided for netlink message" << std::endl;
        return NL_SKIP;
    }

    // call the valid callback
    int result = (*(context->valid))(msg);

    return result;
}

static int ackHandler(nl_msg* msg, void* arg) {
    NetlinkCallbackContext* context = static_cast<NetlinkCallbackContext*>(arg);
    if (!context) {
        std::cerr << "No context provided for netlink ack message" << std::endl;
        return NL_SKIP;
    }
    context->counter = 0;
    return NL_STOP;
}

static int finishHandler(nl_msg* msg, void* arg) {
    NetlinkCallbackContext* context = static_cast<NetlinkCallbackContext*>(arg);
    if (!context) {
        std::cerr << "No context provided for netlink finish message" << std::endl;
        return NL_SKIP;
    }
    context->counter = 0;
    return NL_SKIP;
}

Nl80211Driver::Nl80211Driver() :
    m_pSocket {},
    m_recvThread {},
    m_running {false} {
}

ResultVoid Nl80211Driver::up(std::string const& interfaceName) {
    std::cout << "Bringing up network interface: " << interfaceName << std::endl;

    m_pSocket = std::unique_ptr<Socket, std::function<void(Socket*)>>(
        new Socket(), [](Socket* pSocket) {
            std::cout << "Cleaning up socket resources" << std::endl;
            if (pSocket->pHandle) {
                nl_socket_free(pSocket->pHandle);
            }
            delete pSocket;
        });
    m_pSocket->m_interfaceName = interfaceName;
    m_pSocket->m_context = std::make_unique<NetlinkCallbackContext>();
    m_pSocket->m_context->valid = std::make_unique<NetlinkCallback>([this](nl_msg* msg) {
        return onCallbackGlobal(msg);
    });
    m_pSocket->m_context->error = std::make_unique<NetlinkErrCallback>([this](nlmsgerr* nlerr) {
        return onCallbackError(nlerr);
    });

    auto result = setupSocket();
    if (!result.isSuccess()) {
        return result;
    }

    m_running = true;
    m_recvThread = std::thread([this]() {
        while (m_running) {
            nl_recvmsgs_default(m_pSocket->pHandle);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });

    notify(&NetworkDriverListenerIfc::onNetStatusChanged, NetworkStatus::UP);

    return ResultVoid::success(true);
}

ResultVoid Nl80211Driver::down() {
    std::cout << "Bringing down network interface: " << m_pSocket->m_interfaceName << std::endl;

    m_running = false;
    m_pSocket.reset();

    if (m_recvThread.joinable()) {
        m_recvThread.join();
    }

    // TODO bring down the interface

    notify(&NetworkDriverListenerIfc::onNetStatusChanged, NetworkStatus::DOWN);

    return ResultVoid::success(true);
}

ResultVoid Nl80211Driver::triggerScan() {
    std::cout << "Triggering scan on interface: " << m_pSocket->m_interfaceName << std::endl;

    auto msg = createNetlinkMessage(NL80211_CMD_TRIGGER_SCAN, 0);
    if (!msg) {
        return ResultVoid::error("Failed to allocate netlink message for scan trigger");
    }

    nl_msg* ssids {nlmsg_alloc()};
    nla_put(ssids, 1, 0, ""); // empty SSID for wildcard scan
    nla_put_nested(msg, NL80211_ATTR_SCAN_SSIDS, ssids);
    nlmsg_free(ssids);

    uint32_t flags = 0;
    flags |= NL80211_SCAN_FLAG_COLOCATED_6GHZ;
    nla_put_u32(msg, NL80211_ATTR_SCAN_FLAGS, flags);

    return sendNetlinkRequest(msg, this, &Nl80211Driver::onCallbackOk);
}

ResultVoid Nl80211Driver::abortScan() {
    auto scanResult = createNetlinkMessage(NL80211_CMD_ABORT_SCAN, 0);
    return sendNetlinkRequest(scanResult, this, &Nl80211Driver::onCallbackOk);
}

ResultVoid Nl80211Driver::fetchScanResults() {
    auto scanResult = createNetlinkMessage(NL80211_CMD_GET_SCAN, NLM_F_DUMP);
    return sendNetlinkRequest(scanResult, this, &Nl80211Driver::onCallbackScanResult);
}

int Nl80211Driver::onCallbackOk(nl_msg* msg) {
    return NL_OK;
}

int Nl80211Driver::onCallbackScanResult(nl_msg* msg) {
    nlmsghdr* nlh = nlmsg_hdr(msg);
    genlmsghdr* gnlh = static_cast<genlmsghdr*>(nlmsg_data(nlh));
    ScanResult result {};

    struct nlattr* attrs[NL80211_ATTR_MAX + 1] = {};
    nla_parse(attrs, NL80211_ATTR_MAX, genlmsg_attrdata(gnlh, 0), genlmsg_attrlen(gnlh, 0), nullptr);

    if (!attrs[NL80211_ATTR_BSS]) {
        return NL_SKIP;
    }

    struct nlattr* bss[NL80211_BSS_MAX + 1] = {};
    nla_parse_nested(bss, NL80211_BSS_MAX, attrs[NL80211_ATTR_BSS], nullptr);

    if (bss[NL80211_BSS_SIGNAL_MBM]) {
        result.signalStrength = nla_get_u32(bss[NL80211_BSS_SIGNAL_MBM]);
    }

    if (bss[NL80211_BSS_INFORMATION_ELEMENTS]) {
        uint8_t* ie = static_cast<uint8_t*>(nla_data(bss[NL80211_BSS_INFORMATION_ELEMENTS]));
        int len = nla_len(bss[NL80211_BSS_INFORMATION_ELEMENTS]);

        for (int32_t i = 0; i + 1 < len;) {
            uint8_t id = ie[i];
            uint8_t elen = ie[i + 1];
            if (id == 0 && i + 2 + elen <= len) { // SSID element
                std::string ssid((char*)&ie[i + 2], elen);
                result.ssid = ssid;
                break;
            }
            i += elen + 2;
        }
    }

    notify(&NetworkDriverListenerIfc::onScanResultsAvailable, result);

    return NL_SKIP;
}

int Nl80211Driver::onCallbackGlobal(nl_msg* msg) {
    genlmsghdr* gnlh = static_cast<genlmsghdr*>(nlmsg_data(nlmsg_hdr(msg)));

    if (gnlh->cmd == NL80211_CMD_NEW_SCAN_RESULTS) {
        notify(&NetworkDriverListenerIfc::onScanCompleted, true);
    }
    else if (gnlh->cmd == NL80211_CMD_SCAN_ABORTED) {
        notify(&NetworkDriverListenerIfc::onScanCompleted, false);
    }
    else {
        // ignore
    }

    return NL_OK;
}

int Nl80211Driver::onCallbackError(nlmsgerr* nlerr) {
    std::cerr << "Netlink error received: " << nl_geterror(nlerr->error) << "(" << nlerr->error << ")" << std::endl;

    return NL_STOP;
}

ResultVoid Nl80211Driver::setupSocket() {
    m_pSocket->pHandle = nl_socket_alloc();
    if (!m_pSocket->pHandle) {
        return ResultVoid::error("Failed to allocate netlink socket");
    }

    if (genl_connect(m_pSocket->pHandle) != 0) {
        return ResultVoid::error("Failed to connect to netlink socket");
    }

    m_pSocket->m_devId = genl_ctrl_resolve(m_pSocket->pHandle, "nl80211");
    if (m_pSocket->m_devId < 0) {
        return ResultVoid::error("Failed to resolve nl80211 id");
    }

    m_pSocket->m_ifIdx = if_nametoindex(m_pSocket->m_interfaceName.c_str());
    if (m_pSocket->m_ifIdx <= 0) {
        return ResultVoid::error("Failed to get interface index for " + m_pSocket->m_interfaceName);
    }

    // Register for global notifications
    int mcid = genl_ctrl_resolve_grp(m_pSocket->pHandle, "nl80211", NL80211_MULTICAST_GROUP_SCAN);
    if (mcid < 0) {
        return ResultVoid::error("Failed to resolve nl80211 scan group");
    }
    if (nl_socket_add_membership(m_pSocket->pHandle, mcid) < 0) {
        return ResultVoid::error("Failed to add membership to nl80211 scan group");
    }

    nl_socket_modify_cb(m_pSocket->pHandle, NL_CB_VALID, NL_CB_CUSTOM, validHandler, m_pSocket->m_context.get());
    nl_socket_modify_err_cb(m_pSocket->pHandle, NL_CB_CUSTOM, errorHandler, m_pSocket->m_context.get());

    // Disable sequence number checking for the socket
    // This is necessary to avoid issues with sequence numbers in some cases.
    // https://stackoverflow.com/questions/64669383/cannot-understand-this-message-sequence-mismatch-error
    nl_socket_disable_seq_check(m_pSocket->pHandle);

    nl_socket_set_buffer_size(m_pSocket->pHandle, 8192, 8192);
    nl_socket_set_nonblocking(m_pSocket->pHandle);

    return ResultVoid::success(true);
}

nl_msg* Nl80211Driver::createNetlinkMessage(int const cmd, int const flags) {
    nl_msg* msg = nlmsg_alloc();
    if (!msg) {
        return nullptr;
    }

    genlmsg_put(msg,        // msg      Netlink message object
        NL_AUTO_PORT,       // port     Netlink port or NL_AUTO_PORT
        NL_AUTO_SEQ,        // seq      Sequence number of message or NL_AUTO_SEQ
        m_pSocket->m_devId, // family   Numeric family identifier
        0,                  // hdrlen   Length of user header
        flags,              // flags    Additional Netlink message flags (optional)
        cmd,                // cmd      Numeric command identifier
        0                   // version  Interface version
    );
    nla_put_u32(msg, NL80211_ATTR_IFINDEX, m_pSocket->m_ifIdx);

    return msg;
}

ResultVoid Nl80211Driver::sendNetlinkRequest(nl_msg* msg, NetlinkCallback* pCallback) {
    NetlinkCallbackContext context {};
    context.counter = 1;
    context.valid = std::unique_ptr<NetlinkCallback>(pCallback);
    context.error = std::make_unique<NetlinkErrCallback>([this](nlmsgerr* nlerr) {
        return onCallbackError(nlerr);
    });

    // True if debugging is enabled, false otherwise.
    // This can be used to enable verbose logging for debugging purposes.
    // It is set to false by default, but can be changed to true for debugging.
    bool constexpr isDebugging {false};

    nl_cb* cb = nl_cb_alloc(isDebugging ? NL_CB_DEBUG : NL_CB_DEFAULT);
    if (!cb) {
        nlmsg_free(msg);
        return ResultVoid::error("Failed to allocate netlink callback");
    }

    nl_cb_err(cb, NL_CB_CUSTOM, errorHandler, &context);
    nl_cb_set(cb, NL_CB_VALID, NL_CB_CUSTOM, validHandler, &context);
    nl_cb_set(cb, NL_CB_FINISH, NL_CB_CUSTOM, finishHandler, &context);
    nl_cb_set(cb, NL_CB_ACK, NL_CB_CUSTOM, ackHandler, &context);

    if (isDebugging) {
        nl_cb_set(cb, NL_CB_INVALID, NL_CB_DEBUG, nullptr, nullptr);
        nl_cb_set(cb, NL_CB_FINISH, NL_CB_DEBUG, nullptr, nullptr);
        nl_cb_set(cb, NL_CB_OVERRUN, NL_CB_DEBUG, nullptr, nullptr);
        nl_cb_set(cb, NL_CB_MSG_IN, NL_CB_DEBUG, nullptr, nullptr);
        nl_cb_set(cb, NL_CB_MSG_OUT, NL_CB_DEBUG, nullptr, nullptr);
    }

    int32_t err;

    err = nl_send_auto(m_pSocket->pHandle, msg);
    if (err < 0) {
        return ResultVoid::error("Failed to send netlink message: " + std::string(nl_geterror(err)));
    }

    while (context.counter > 0) {
        nl_recvmsgs(m_pSocket->pHandle, cb);
    }

    nl_cb_put(cb);
    nlmsg_free(msg);

    return ResultVoid::success(true);
}
