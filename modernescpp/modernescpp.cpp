#include <atomic>
#include <thread>

class Spinlock
{
	std::atomic_flag flag;

public:
	Spinlock() : flag(ATOMIC_FLAG_INIT) {}

	void Lock()
	{
		while (flag.test_and_set());
	}

	void Unlock()
	{
		flag.clear();
	}
};

Spinlock spin;

void WorkOnResource()
{
	spin.Lock();
	// shared resource
	spin.Unlock();
}

int main()
{
	std::thread t(WorkOnResource);
	std::thread t2(WorkOnResource);

	t.join();
	t2.join();
}