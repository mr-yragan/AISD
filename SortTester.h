#ifndef SORT_TESTER_H
#define SORT_TESTER_H

#include <vector>
#include <chrono>
#include <numeric>
#include <iostream>
#include <fstream>
#include <string>

using std::vector;

class SortTester {
public:
    static void insertionSort(vector<int> &arr, int left, int right) {
        for (int i = left + 1; i < right; ++i) {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

    static void merge(vector<int> &arr, int left, int mid, int right) {
        int n1 = mid - left, n2 = right - mid;
        vector<int> L(arr.begin() + left, arr.begin() + mid);
        vector<int> R(arr.begin() + mid, arr.begin() + right);
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }
        while (i < n1) {
            arr[k++] = L[i++];
        }
        while (j < n2) {
            arr[k++] = R[j++];
        }
    }

    static void mergeSort(vector<int> &arr, int left, int right) {
        if (right - left <= 1) {
            return;
        }
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid, right);
        merge(arr, left, mid, right);
    }

    static void hybridSortWithThreshold(vector<int> &arr, int left, int right, int threshold) {
        if (right - left <= threshold) {
            insertionSort(arr, left, right);
            return;
        }
        int mid = left + (right - left) / 2;
        hybridSortWithThreshold(arr, left, mid, threshold);
        hybridSortWithThreshold(arr, mid, right, threshold);
        merge(arr, left, mid, right);
    }

    static long long measureTime(vector<int> arr, const std::string &algorithm = "merge", int threshold = 15, int repetitions = 5) {
        vector<long long> times;
        for (int i = 0; i < repetitions; ++i) {
            vector<int> copy = arr;
            auto start = std::chrono::high_resolution_clock::now();
            if (algorithm == "merge") {
                mergeSort(copy, 0, static_cast<int>(copy.size()));
            } else if (algorithm == "hybrid") {
                hybridSortWithThreshold(copy, 0, static_cast<int>(copy.size()), threshold);
            } else {
                throw std::invalid_argument("чет не то ввел" + algorithm);
            }
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count());
        }
        long long sum = std::accumulate(times.begin(), times.end(), 0LL);
        return sum / repetitions;
    }

    static void saveToCSV(const std::string &arrayType, const std::string &algorithm, int size, long long timeMs, const std::string &filename = "result.csv") {
        std::ofstream out;
        out.open(filename, std::ios::app);
        out << "array_type,algorithm,size,time_ms\n";
        out << arrayType << "," << algorithm << "," << size << "," << timeMs << "\n";
        out.close();
    }
};

#endif
