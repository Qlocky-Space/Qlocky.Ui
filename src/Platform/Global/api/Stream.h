#ifndef SRC_PLATFORM_GLOBAL_API_STREAM_H
#define SRC_PLATFORM_GLOBAL_API_STREAM_H

#include <atomic>
#include <functional>
#include <memory>
#include <utility>

/**
 * Lightweight asynchronous stream abstraction.
 *
 * A Stream<T> wraps a producer that can yield zero or more items of type T
 * over time and then signal that the sequence has finished. The producer owns
 * the execution model. It may deliver values immediately, from a worker thread,
 * from an event loop callback, or in any other asynchronous way.
 *
 * The stream itself is intentionally small. It does not provide buffering,
 * back-pressure, or transformation operators. Its responsibility is limited to
 * connecting a producer with consumer callbacks and exposing cooperative
 * cancellation through Subscription.
 *
 * Typical usage has two sides:
 * - A producer creates a Stream<T> and calls the provided item and finished
 *   handlers when results become available.
 * - A consumer calls consume(...) and provides the handlers that should run for
 *   each item and for stream completion.
 *
 * Simple example:
 * @code
 * Stream<int> createCounterStream() {
 *     return Stream<int> {
 *         [](Stream<int>::ItemHandler onItem,
 *            Stream<int>::FinishedHandler onFinished,
 *            Stream<int>::Subscription const& subscription) {
 *             for (int value {0}; value < 3; ++value) {
 *                 if (subscription.isCanceled()) {
 *                     return;
 *                 }
 *
 *                 onItem(value);
 *             }
 *
 *             onFinished();
 *         }
 *     };
 * }
 *
 * auto subscription = createCounterStream().consume(
 *     [](int value) {
 *         // Handle one produced value.
 *     },
 *     []() {
 *         // Handle completion.
 *     });
 * @endcode
 *
 * @tparam T The item type yielded by the stream.
 */
template<typename T>
class Stream final {
public:

    /**
     * Handle for one active stream consumption.
     *
     * A Subscription is returned by consume(...). It allows the consumer to
     * request that the producer stops delivering more items. Cancellation is
     * cooperative: the producer must check isCanceled() and stop its own work.
     *
     * The stream also wraps the consumer callbacks so that, after cancellation,
     * further item and finished notifications become no-ops even if a producer
     * still invokes them.
     */
    class Subscription final {
    public:

        Subscription() :
            m_state {std::make_shared<State>()} {
        }

        /**
         * Request cancellation of the active stream consumption.
         *
         * Cancellation is cooperative. Producers may stop early when they
         * observe the canceled flag. Wrapped item and completion handlers also
         * become no-ops after cancellation.
         */
        void cancel() const {
            m_state->isCanceled.store(true, std::memory_order_relaxed);
        }

        /**
         * Check whether cancellation was requested.
         * @return True when the subscription has been canceled.
         */
        bool isCanceled() const {
            return m_state->isCanceled.load(std::memory_order_relaxed);
        }

    private:

        struct State {
            std::atomic<bool> isCanceled {false};
        };

        explicit Subscription(std::shared_ptr<State> state) :
            m_state {std::move(state)} {
        }

        std::shared_ptr<State> m_state;

        friend class Stream<T>;
    };

    /**
     * Callback invoked for each yielded item.
     */
    using ItemHandler = std::function<void(T const&)>;

    /**
     * Callback invoked when the stream has no more items to deliver.
     */
    using FinishedHandler = std::function<void()>;

    /**
     * Function object used to produce stream items.
     *
     * The producer receives the consumer callbacks together with the active
     * subscription. A well-behaved producer should stop work when
     * subscription.isCanceled() becomes true.
     */
    using Producer = std::function<void(ItemHandler, FinishedHandler, Subscription const&)>;

    Stream() = default;

    /**
     * Create a stream from a concrete producer implementation.
     * @param producer Function responsible for delivering items and completion.
     */
    explicit Stream(Producer producer) :
        m_producer {std::move(producer)} {
    }

    /**
     * Start consuming the stream.
     *
     * The supplied callbacks are wrapped so they stop receiving notifications
     * after cancellation. The returned subscription can be stored by the caller
     * and canceled later if the ongoing work is no longer needed.
     *
     * @param onItem Called for each yielded item.
     * @param onFinished Called after the stream has completed.
     * @return A subscription handle that can be used to cancel consumption.
     */
    Subscription consume(ItemHandler onItem, FinishedHandler onFinished = {}) const {
        Subscription subscription {};

        if (!m_producer) {
            if (onFinished && !subscription.isCanceled()) {
                onFinished();
            }
            return subscription;
        }

        ItemHandler wrappedOnItem {[subscription, onItem = std::move(onItem)](T const& item) {
            if (subscription.isCanceled() || !onItem) {
                return;
            }

            onItem(item);
        }};

        FinishedHandler wrappedOnFinished {[subscription, onFinished = std::move(onFinished)]() {
            if (subscription.isCanceled() || !onFinished) {
                return;
            }

            onFinished();
        }};

        m_producer(std::move(wrappedOnItem), std::move(wrappedOnFinished), subscription);
        return subscription;
    }

    /**
     * Check whether the stream has a producer.
     * @return True when a producer is available.
     */
    explicit operator bool() const {
        return static_cast<bool>(m_producer);
    }

private:

    Producer m_producer {};
};

#endif // SRC_PLATFORM_GLOBAL_API_STREAM_H