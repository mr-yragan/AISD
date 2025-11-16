#ifndef ARRAY_GENERATOR_H
#define ARRAY_GENERATOR_H

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class ArrayGenerator {
public:
    ArrayGenerator() { std::srand(std::time(nullptr)); }

    std::vector<int> randomArray(int n, int maxValue = 10000) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = std::rand() % (maxValue + 1);
        }
        return arr;
    }

    std::vector<int> reversedArray(int n, int maxValue = 10000) {
        auto arr = randomArray(n, maxValue);
        std::sort(arr.begin(), arr.end(), std::greater<int>());
        return arr;
    }

    std::vector<int> nearlySortedArray(int n, int swaps = 10) {
        auto arr = randomArray(n);
        std::sort(arr.begin(), arr.end());
        for (int i = 0; i < swaps; ++i) {
            int a = std::rand() % n;
            int b = std::rand() % n;
            std::swap(arr[a], arr[b]);
        }
        return arr;
    }
};

#endif
