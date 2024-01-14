#include <chrono>
#include <functional>
#include <random>

#ifndef UTILS_H
#define UTILS_H

inline long long timer(std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();

    func();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    return duration.count();
}

inline float randomFloat() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (2000000)) - 1000000;
}

inline int randomInt(int upper, int lower = 0) {
    return lower + rand() % (upper - lower + 1);
}

float meanArray(long long*, int);
long long maxArray(long long*, int);
long long minArray(long long*, int);
const char* formatNumberForDisplay(int);
const char* longToString(long);

#endif  // UTILS_H