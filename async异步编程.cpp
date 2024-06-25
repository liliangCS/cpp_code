#include <iostream>
#include <future>
#include <chrono>

int asyncFunction(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return x * 2;
}

int main() {
    // 使用 std::async 启动异步任务
    std::future<int> result = std::async(std::launch::async, asyncFunction, 10);

    std::cout << "Waiting for the result..." << std::endl;

    // 获取结果，若任务未完成会阻塞等待
    int value = result.get();

    std::cout << "The result is: " << value << std::endl;

    return 0;
}
