#include <condition_variable>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include <assert.h>

//std::vector<int> mySharedWork;
//std::mutex mutex_;
//std::condition_variable condVar;
//
//
//bool dataReady;
//
//void waitingForWork()
//{
//	std::cout << "Waiting" << std::endl;
//	std::unique_lock<std::mutex> lck(mutex_);
//	condVar.wait(lck, [] { return dataReady; });
//	mySharedWork[1] = 2;
//	std::cout << "Work done" << std::endl;
//}
//
//void setDataReady()
//{
//	mySharedWork = { 1,0,3 };
//	{
//		std::lock_guard<std::mutex> lck(mutex_);
//		dataReady = true;
//	}
//	std::cout << "Data prepared" << std::endl;
//	condVar.notify_one();
//}

std::vector<int> mySharedWork;
std::atomic<bool> dataReady(false);

void waitingForWork()
{
	std::cout << "Waiting " << std::endl;
	while (!dataReady.load())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5));	
	}
	mySharedWork[1] = 2;
	std::cout << "Work done " << std::endl;
}

void setDataReady()
{
	mySharedWork = { 1, 0, 3 };
	dataReady = true;
	std::cout << "Data prepared" << std::endl;
}

template <typename T>
requires std::is_integral<T>::value
T fetch_mult(std::atomic<T>& shared, T mult)
{
	T oldValue = shared.load();
	while (!shared.compare_exchange_strong(oldValue, oldValue * mult));
	return oldValue;
}

class MyData
{
	int m;
};

int main()
{
	std::atomic<int> myInt{ 5 };
	std::cout << myInt << std::endl;
	std::cout << fetch_mult(myInt, 5) << std::endl;
	std::cout << myInt << std::endl;

	std::shared_ptr<MyData> p;
	std::shared_ptr<MyData> p2 = std::atomic_load(&p);
	std::shared_ptr<MyData> p3(new MyData);
	std::atomic_store(&p, p3);
}