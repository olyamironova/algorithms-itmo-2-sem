#include <iostream>
#include "blazingio.hpp"

int main() {
    long long n, current;
    std::cin >> n;
    long long first_set = 0;
    long long second_set = 0;
    long long first_set_sum = 0;
    long long second_set_sum = 0;
    for (long long i = 0; i < n; ++i) {
        std::cin >> current;
        first_set ^= current % LONG_LONG_MAX;
        first_set_sum += current;
    }
    for (long long i = 0; i < n; ++i) {
        std::cin >> current;
        second_set ^= current % LONG_LONG_MAX;
        second_set_sum += current;
    }
    if ((first_set == second_set) && (first_set_sum == second_set_sum)) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
}