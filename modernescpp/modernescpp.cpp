// modernescpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

class sleeper
{
public:
    sleeper(int& i_) : i{ i_ } {}
    void operator() (int k)
    {
        for (size_t j = 0; j < 5; j++)
        {
            std::this_thread::sleep_for(100ms);
            i += k;
        }
        std::cout << std::this_thread::get_id() << std::endl;
    }

private:
    int& i;
};

int main()
{
    std::cout << std::endl;

    int valSleeper = 1000;
    std::thread t(sleeper(valSleeper), 5);
    t.join();
    std::cout << "valSleeper = " << valSleeper << std::endl;

    std::cout << std::endl;
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
