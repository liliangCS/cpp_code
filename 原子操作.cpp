#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> shared_data = 0;

void t_test()
{
    for (int i = 0; i < 100000; i++)
    {
        shared_data++;
    }
}

int main()
{
    std::thread t1(t_test);
    std::thread t2(t_test);

    t1.join();
    t2.join();

    std::cout << "shared_data = " << shared_data << std::endl;

    return 0;
}
