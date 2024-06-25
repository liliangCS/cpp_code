#include <iostream>
#include <future>
#include <thread>

void promiseFunction(std::promise<int> promise) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    promise.set_value(42);
}

int main() {
    // 创建 std::promise 对象
    std::promise<int> promise;

    // 获取与 promise 相关联的 future 对象
    std::future<int> result = promise.get_future();

    // 启动一个线程并传递 promise
    std::thread t(promiseFunction, std::move(promise));

    std::cout << "Waiting for the result..." << std::endl;

    // 获取结果，若任务未完成会阻塞等待
    int value = result.get();

    std::cout << "The result is: " << value << std::endl;

    t.join();
    return 0;
}
