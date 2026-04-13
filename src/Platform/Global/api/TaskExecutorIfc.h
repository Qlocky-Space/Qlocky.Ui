#ifndef SRC_PLATFORM_GLOBAL_API_TASK_EXECUTOR_IFC_H
#define SRC_PLATFORM_GLOBAL_API_TASK_EXECUTOR_IFC_H

#include <functional>

/**
 * Generic asynchronous task executor abstraction.
 *
 * Components submit short non-blocking tasks to this interface when they need
 * asynchronous execution without owning worker threads directly.
 */
class TaskExecutorIfc {
public:

    /**
     * Unit of work accepted by the task executor.
     */
    using Task = std::function<void()>;

    /**
     * Queue a task for asynchronous execution.
     * @param task Work item to schedule.
     */
    virtual void enqueue(Task task) = 0;

    virtual ~TaskExecutorIfc() = default;
};

#endif // SRC_PLATFORM_GLOBAL_API_TASK_EXECUTOR_IFC_H
