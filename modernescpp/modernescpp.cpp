#include <condition_variable>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>


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

int main()
{
	std::cout << std::endl;
	std::thread t1(waitingForWork);
	std::thread t2(setDataReady);

	t1.join();
	t2.join();

	for (size_t i = 0; i < mySharedWork.size(); i++)
	{
		std::cout << mySharedWork[i] << " ";
	}

	std::cout << "\n\n";
}