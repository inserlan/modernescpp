#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <future>

void f1(int n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 1 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void f2(int& n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 2 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

class foo
{
public:
    void bar()
    {
        for (int i = 0; i < 5; ++i) {
            std::cout << "Thread 3 executing\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    int n = 0;
};

class baz
{
public:
    void operator()()
    {
        for (int i = 0; i < 5; ++i) {
            std::cout << "Thread 4 executing\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    int n = 0;
};

void doTheWork()
{
    std::cout << "Processing shared data." << std::endl;
}

void waitingForWork(std::future<void>&& fut)
{
    std::cout << "Worker: Waiting for work." << std::endl;
    fut.wait();
    doTheWork();
    std::cout << "Work done." << std::endl;
}

void setDataReady(std::promise<void>&& prom)
{
    std::cout << "Sender: Data is ready." << std::endl;
    prom.set_value();
}

int main()
{
    std::cout << std::endl;

    std::promise<void> sendReady;
    auto fut = sendReady.get_future();
    std::thread t1(waitingForWork, std::move(fut));
    std::thread t2(setDataReady, std::move(sendReady));

    t1.join();
    t2.join();

    std::cout << "main thread" << std::endl;
}