#include <iostream>
#include <future>
#include <thread>

int taskFunction(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return x * 2;
}

int main() {
    // 创建 std::packaged_task 对象
    std::packaged_task<int(int)> task(taskFunction);

    // 获取与任务相关联的 future 对象
    std::future<int> result = task.get_future();

    // 启动一个线程并运行任务
    std::thread t(std::move(task), 10);

    std::cout << "Waiting for the result..." << std::endl;

    // 获取结果，若任务未完成会阻塞等待
    int value = result.get();

    std::cout << "The result is: " << value << std::endl;

    t.join();
    return 0;
}
