#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <omp.h>

using namespace std;

bool isPalindrome(int x) {
    if (x < 0)
        return false;
    int div = 1;
    while (x / div >= 10) {
        div *= 10;
    }
    while (x != 0) {
        int l = x / div;
        int r = x % 10;
        if (l != r)
            return false;
        x = (x % div) / 10;
        div /= 100;
    }
    return true;
}

int main(int argc, char* argv[])
{
    int a = 1, b = 10000; double dt, timein, timeout;
    timein = omp_get_wtime();
    omp_set_num_threads(4);
#pragma omp parallel for
    for (int n = a; n < b; n++)
        if (isPalindrome(n)) printf("Palindrom value ---> %d\n", n);
    timeout = omp_get_wtime();
    dt = timeout - timein;
    printf("CPU Time: %lf ms\n", dt);

    return 0;
}
