#include <atomic>
#include <chrono>
#include <thread>
#include <vector>

#include <gtest/gtest.h>

#include "Subject.h"

namespace {

class TestListenerIfc {
public:
    virtual ~TestListenerIfc() = default;
    virtual void onValue(int value) = 0;
};

class TestSubject final : public Subject<TestListenerIfc> {
public:
    void fire(int value) {
        notify(&TestListenerIfc::onValue, value);
    }
};

class CountingListener final : public TestListenerIfc {
public:
    void onValue(int value) override {
        m_count.fetch_add(value, std::memory_order_relaxed);
    }

    int count() const {
        return m_count.load(std::memory_order_relaxed);
    }

private:
    std::atomic<int> m_count {0};
};

} // namespace

TEST(SubjectThreadSafetyTest, attachDetachWhileNotifyingDoesNotCrash) {
    TestSubject subject {};

    constexpr int listenerCount {24};
    std::vector<CountingListener> listeners(static_cast<size_t>(listenerCount));

    std::atomic<bool> run {true};

    std::thread notifier([&subject, &run]() {
        while (run.load(std::memory_order_relaxed)) {
            subject.fire(1);
        }
    });

    std::thread toggler([&subject, &listeners, &run]() {
        while (run.load(std::memory_order_relaxed)) {
            for (CountingListener& listener : listeners) {
                subject.attach(&listener);
            }
            for (CountingListener& listener : listeners) {
                subject.detach(&listener);
            }
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    run.store(false, std::memory_order_relaxed);

    notifier.join();
    toggler.join();

    int totalNotifications {0};
    for (CountingListener const& listener : listeners) {
        totalNotifications += listener.count();
    }

    EXPECT_GE(totalNotifications, 0);
}
