#include "AsyncTaskExecutor.h"

AsyncTaskExecutor::AsyncTaskExecutor() {
    std::size_t const suggestedWorkerCount {static_cast<std::size_t>(std::thread::hardware_concurrency())};
    std::size_t const workerCount {suggestedWorkerCount == 0 ? 1 : suggestedWorkerCount};
    m_workers.reserve(workerCount);

    for (std::size_t index {0}; index < workerCount; ++index) {
        m_workers.emplace_back([this]() {
            processTasks();
        });
    }
}

AsyncTaskExecutor::~AsyncTaskExecutor() {
    {
        std::lock_guard<std::mutex> const lock {m_mutex};
        m_isStopping = true;
    }

    m_condition.notify_all();

    for (std::thread& worker : m_workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void AsyncTaskExecutor::enqueue(Task task) {
    {
        std::lock_guard<std::mutex> const lock {m_mutex};
        if (m_isStopping) {
            return;
        }

        m_tasks.push_back(std::move(task));
    }

    m_condition.notify_one();
}

void AsyncTaskExecutor::processTasks() {
    while (true) {
        Task task {};
        {
            std::unique_lock<std::mutex> lock {m_mutex};
            m_condition.wait(lock, [this]() {
                return m_isStopping || !m_tasks.empty();
            });

            if (m_isStopping && m_tasks.empty()) {
                return;
            }

            task = std::move(m_tasks.front());
            m_tasks.pop_front();
        }

        task();
    }
}