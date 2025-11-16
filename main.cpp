#include "ArrayGenerator.h"
#include "SortTester.h"
#include <windows.h>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;


int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    ArrayGenerator gen;
    std::vector<int> sizes;
    for (int n = 500; n <= 100000; n += 100) {
        sizes.push_back(n);
    }
    std::vector<std::string> algorithms = {"merge", "hybrid"};
    std::vector<std::string> arrayTypes = {"random", "reversed", "nearly_sorted"};
    auto randomMax = gen.randomArray(100000);
    auto reversedMax = gen.reversedArray(100000);
    auto nearlyMax = gen.nearlySortedArray(100000, 10);
    for (int n: sizes) {
        std::vector<std::vector<int> > arrays = {
            std::vector<int>(randomMax.begin(), randomMax.begin() + n),
            std::vector<int>(reversedMax.begin(), reversedMax.begin() + n),
            std::vector<int>(nearlyMax.begin(), nearlyMax.begin() + n)
        };
        for (int i = 0; i < arrays.size(); ++i) {
            for (const auto &algo: algorithms) {
                long long t = SortTester::measureTime(arrays[i], algo);
                SortTester::saveToCSV(arrayTypes[i], algo, n, t);
            }
        }
    }
    return 0;
}
