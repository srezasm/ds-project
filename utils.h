#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <limits>

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

float meanArray(long long array[], int n) {
    float sum = 0.0;

    for (int i = 0; i < n; i++)
        sum += array[i];

    return sum / n;
}

long long maxArray(long long array[], int n) {
    float res = array[0];

    for (int i = 1; i < n; i++)
        if (array[i] > res)
            res = array[i];

    return res;
}

long long minArray(long long array[], int n) {
    float res = array[0];

    for (int i = 1; i < n; i++)
        if (array[i] < res)
            res = array[i];

    return res;
}