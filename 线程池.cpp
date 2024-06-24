#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>
#include <chrono>

class ThreadPool
{
public:
    ThreadPool(int numThreads) : stop(false)
    {
        for (int i = 0; i < numThreads; i++)
        {
            threads.emplace_back([this]() {
                while (1) {
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock, [this](){
                        return !tasks.empty() || stop;
                    });

                    if (stop && tasks.empty()) {
                        return;
                    }

                    std::function<void()> task = tasks.front();
                    tasks.pop();
                    lock.unlock();
                    task();
                }
            });
        }
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(mtx);
            stop = true;
        }

        cv.notify_all();

        for (std::thread &t : threads)
        {
            t.join();
        }
    }

    template<typename T, typename... Args>
    void enqueue(T &&t, Args&&... args) {
        std::function<void()> task = std::bind(std::forward<T>(t), std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.emplace(task);
        }
        cv.notify_one();
    };

private:
    std::vector<std::thread> threads;        // 线程数组
    std::queue<std::function<void()>> tasks; // 任务队列

    std::mutex mtx;
    std::condition_variable cv;

    bool stop;
};

int main()
{
    ThreadPool pool(4);

    for (int i = 0; i < 10; i++) {
        pool.enqueue([i](){
            std::cout << "task : " << i << " is runing" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "task : " << i << " is done" << std::endl;
        });
    }

    return 0;
}
