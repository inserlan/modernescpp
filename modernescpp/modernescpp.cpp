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

int main()
{
    std::cout << std::endl;

    auto first = std::async(std::launch::async, [] {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "first thread" << std::endl;
    });

    auto second = std::async(std::launch::async, [] {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "second thread" << std::endl; }
    );

    first.get();
    second.get();
    std::cout << "main thread" << std::endl;
}