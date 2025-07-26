#ifndef NL80211_DRIVER_H
#define NL80211_DRIVER_H

#include <functional>
#include <memory>
#include <Subject.h>
#include <thread>

#include "NetworkDriverIfc.h"
#include "NetworkDriverListenerIfc.h"

struct Socket;
struct nl_msg;
struct nlmsgerr;

using NetlinkCallback = std::function<int(nl_msg*)>;
using NetlinkErrCallback = std::function<int(nlmsgerr*)>;
using SocketDeleter = std::function<void(Socket*)>;

/**
 * Nl80211Driver is a concrete implementation of NetworkDriverIfc for managing Wi-Fi operations
 * using the nl80211 interface.
 *
 * This driver uses the Netlink protocol to communicate with the kernel's nl80211 subsystem,
 * allowing it to perform operations such as bringing up/down the network interface, triggering scans,
 * and fetching scan results.
 *
 * @note It does not use mediator, but instead directly notifies observers by listening to events.
 *
 * https://wireless.docs.kernel.org/en/latest/index.html
 * https://www.infradead.org/~tgr/libnl/
 */
class Nl80211Driver final : public Subject<NetworkDriverListenerIfc>, public NetworkDriverIfc {
public:

    Nl80211Driver();
    ~Nl80211Driver() final = default;

    /**
     * @see NetworkDriverIfc::up()
     */
    ResultVoid up(std::string const& interfaceName) final;

    /**
     * @see NetworkDriverIfc::down()
     */
    ResultVoid down() final;

    /**
     * @see NetworkDriverIfc::triggerScan()
     */
    ResultVoid triggerScan() final;

    /**
     * @see NetworkDriverIfc::abortScan()
     */
    ResultVoid abortScan() final;

    /**
     * @see NetworkDriverIfc::fetchScanResults()
     */
    ResultVoid fetchScanResults() final;

private:

    using ResultMsg = Result<nl_msg*, std::string>;

    int onCallbackInterfaceStats(nl_msg* msg);
    int onCallbackTriggerScan(nl_msg* msg);
    int onCallbackScanAbort(nl_msg* msg);
    int onCallbackScanResult(nl_msg* msg);
    int onCallbackGlobal(nl_msg* msg);
    int onCallbackError(nlmsgerr* nlerr);

    nl_msg* createNetlinkMessage(int const cmd, int const flags);

    template<typename T>
    ResultVoid sendNetlinkRequest(nl_msg* msg, T* instance, int (T::*method)(nl_msg*)) {
        NetlinkCallback* pCallback = new NetlinkCallback([instance, method](nl_msg* msg) {
            return (instance->*method)(msg);
        });
        return sendNetlinkRequest(msg, pCallback);
    }
    ResultVoid sendNetlinkRequest(nl_msg* msg, NetlinkCallback* pCallback);

    ResultVoid setupSocket();
    ResultVoid fetchInterfaceStats();

    std::unique_ptr<Socket, SocketDeleter> m_pSocket;
    std::thread m_recvThread;
    bool m_running;
};

#endif