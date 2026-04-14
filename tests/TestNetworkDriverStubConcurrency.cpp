#include <atomic>
#include <chrono>
#include <gtest/gtest.h>
#include <thread>

#include "NetworkDriverStub.h"

namespace {

class TestNetworkListener final : public NetworkDriverListenerIfc {
public:

    void onInterfaceStatusChanged(NetworkIfStatus const status) override {
        m_lastStatus.store(status, std::memory_order_relaxed);
    }

    void onScanCompleted(bool success) override {
        m_scanCompletedCount.fetch_add(1, std::memory_order_relaxed);
        m_lastScanSuccess.store(success, std::memory_order_relaxed);
    }

    void onScanResultsAvailable(ScanResult& result) override {
        (void)result;
        m_scanResultCount.fetch_add(1, std::memory_order_relaxed);
    }

    int scanCompletedCount() const {
        return m_scanCompletedCount.load(std::memory_order_relaxed);
    }

private:

    std::atomic<NetworkIfStatus> m_lastStatus {NetworkIfStatus::UNKNOWN};
    std::atomic<int> m_scanCompletedCount {0};
    std::atomic<int> m_scanResultCount {0};
    std::atomic<bool> m_lastScanSuccess {false};
};

} // namespace

TEST(NetworkDriverStubConcurrencyTest, rapidConnectDisconnectKeepsDriverStable) {
    NetworkDriverStub driver {};
    TestNetworkListener listener {};
    driver.attach(&listener);

    ASSERT_TRUE(driver.up("wlan0").isSuccess());

    for (int i = 0; i < 3; ++i) {
        EXPECT_TRUE(driver.connectTo("stress-test-ssid").isSuccess());
        EXPECT_TRUE(driver.disconnect().isSuccess());
    }

    EXPECT_TRUE(driver.down().isSuccess());
}

TEST(NetworkDriverStubConcurrencyTest, secondScanIsRejectedWhileFirstIsRunning) {
    NetworkDriverStub driver {};
    TestNetworkListener listener {};
    driver.attach(&listener);

    ASSERT_TRUE(driver.up("wlan0").isSuccess());

    NetworkResult const firstScan {driver.triggerScan()};
    EXPECT_TRUE(firstScan.isSuccess());
    EXPECT_TRUE(firstScan.value());

    NetworkResult const secondScan {driver.triggerScan()};
    EXPECT_TRUE(secondScan.isSuccess());
    EXPECT_FALSE(secondScan.value());

    std::this_thread::sleep_for(std::chrono::milliseconds(2300));

    NetworkResult const thirdScan {driver.triggerScan()};
    EXPECT_TRUE(thirdScan.isSuccess());
    EXPECT_TRUE(thirdScan.value());

    std::this_thread::sleep_for(std::chrono::milliseconds(2300));

    EXPECT_GE(listener.scanCompletedCount(), 2);
    EXPECT_TRUE(driver.down().isSuccess());
}
