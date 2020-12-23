// conditionVariableFixed.cpp

#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <future>

std::mutex mutex_;
std::condition_variable condVar;

bool dataReady;

void doTheWork() {
    std::cout << "Processing shared data." << std::endl;
}

void waitingForWork() {
    std::cout << "Worker: Waiting for work." << std::endl;

    std::unique_lock<std::mutex> lck(mutex_);
    condVar.wait(lck, [] {return dataReady; });
    doTheWork();
    std::cout << "Work done." << std::endl;
}

void setDataReady() {
    std::lock_guard<std::mutex> lck(mutex_);
    dataReady = true;
    std::cout << "Sender: Data is ready." << std::endl;
    condVar.notify_one();
}

int main() {

    std::cout << std::endl;

    std::thread t1(waitingForWork);
    std::thread t2(setDataReady);

    t1.join();
    t2.join();

    std::cout << std::endl;

    int res = 0;
    std::thread t([&] {res = 3 + 4; });
    t.join();
    std::cout << res << std::endl;

    auto fut = std::async([] {return 3 + 4; });
    std::cout << fut.get() << std::endl;
}