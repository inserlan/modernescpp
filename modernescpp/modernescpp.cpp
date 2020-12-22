// modernescpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>

constexpr int factorial(int n)
{
    return n <= 1 ? 1 : (n * factorial(n - 1));
}

class conststr
{
    const char* p;
    std::size_t sz;

public:
    template<std::size_t N>
    constexpr conststr(const char(&a)[N]) : p(a), sz(N) {}

    constexpr char operator[](std::size_t n) const
    {
        return n < sz ? p[n] : throw std::out_of_range("");
    }
    constexpr std::size_t size() const { return sz; }
};

constexpr std::size_t countlower(conststr s, std::size_t n = 0, std::size_t c = 0)
{
    return n == s.size() ? c : 
        'a' <= s[n] && s[n] <= 'z' ? countlower(s, n + 1, c + 1) :
        countlower(s, n + 1, c);
}

template<int n>
struct constN
{
    constN() { std::cout << n << '\n'; }
};

int main() {

    std::cout << "4! = ";
    constN<factorial(4)> out1; // computed at compile time

    volatile int k = 8; // disallow optimization using volatile
    std::cout << k << "! = " << factorial(k) << '\n'; // computed at run time

    std::cout << "the number of lowercase letters in \"Hello, world!\" is ";
    constN<countlower("Hello, world!")> out2; // implicitly converted to conststr
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
