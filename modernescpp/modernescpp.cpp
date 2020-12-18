// modernescpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>

class scoped_thread
{
public:
    explicit scoped_thread(std::thread t_) : t(std::move(t_))
    {
        if (!t.joinable())
            throw std::logic_error("No thread");
    }

    ~scoped_thread()
    {
        t.join();
    }

    scoped_thread(scoped_thread&) = delete;
    scoped_thread& operator=(scoped_thread const&) = delete;

private:
    std::thread t;
};

int main()
{
    scoped_thread t(std::thread([] {std::cout << std::this_thread::get_id() << std::endl; }));

    std::thread t1;
    scoped_thread st(std::move(t1));
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
