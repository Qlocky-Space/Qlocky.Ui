#ifndef SRC_PLATFORM_GLOBAL_UTIL_ASYNC_TASK_EXECUTOR_H
#define SRC_PLATFORM_GLOBAL_UTIL_ASYNC_TASK_EXECUTOR_H

#include <condition_variable>
#include <cstddef>
#include <deque>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

/**
 * Shared task executor for lightweight asynchronous work.
 *
 * Tasks are queued and executed by a fixed worker set. The executor is thread-safe
 * and can be shared by components that want task-style asynchronous execution
 * without starting one thread per work item.
 */
class AsyncTaskExecutor final {
public:

    using Task = std::function<void()>;

    AsyncTaskExecutor();
    ~AsyncTaskExecutor();

    AsyncTaskExecutor(AsyncTaskExecutor const&) = delete;
    AsyncTaskExecutor& operator=(AsyncTaskExecutor const&) = delete;
    AsyncTaskExecutor(AsyncTaskExecutor&&) = delete;
    AsyncTaskExecutor& operator=(AsyncTaskExecutor&&) = delete;

    /**
     * Queue a task for background execution.
     *
     * If shutdown has already started the task is ignored.
     * @param task The work item to enqueue.
     */
    void enqueue(Task task);

private:

    void processTasks();

    std::deque<Task> m_tasks {};
    std::vector<std::thread> m_workers {};
    std::mutex m_mutex {};
    std::condition_variable m_condition {};
    bool m_isStopping {false};
};

#endif // SRC_PLATFORM_GLOBAL_UTIL_ASYNC_TASK_EXECUTOR_H