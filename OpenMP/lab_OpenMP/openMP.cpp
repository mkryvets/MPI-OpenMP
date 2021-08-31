#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <omp.h>
#include <vector>

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
    int a = 1, b = 10000; 
    double res_time, timein, timeout;
    timein = omp_get_wtime();
    omp_set_num_threads(4);
    int count = 0;
#pragma omp parallel for
    for (int n = a; n < b; n++)
        if (isPalindrome(n)) printf("Palindrom - %d\n", n);
        // if (isPalindrome(n)) palindrom_vector.push_back(n);
    timeout = omp_get_wtime();
    res_time = timeout - timein;
    printf("CPU Time: %lf ms\n", res_time);

    return 0;
}
