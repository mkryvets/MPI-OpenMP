#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <chrono>

using namespace std;
std::vector<int> palindrom_vector;

bool isPalindrome(int x) {
    if (x < 0)
        return false;
    int digit, rev = 0, num = x;
    // get the rev - reversed of x
    do
    {
        digit = num % 10;
        rev = (rev * 10) + digit;
        num = num / 10;
    } while (num != 0);
    // if reversed is base x -> palindrom
    if (rev == x) return true;
    else return false;
}

int main(int argc, char* argv[])
{
    int a = 1, b = 100000;
    auto startTime = std::chrono::high_resolution_clock::now();

    for (int n = a; n < b; n++)
        if (isPalindrome(n)) printf("Palindrom - %d\n", n);
        // if (isPalindrome(n)) palindrom_vector.push_back(n);

    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << "CPU time: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms\n";
    return 0;
}