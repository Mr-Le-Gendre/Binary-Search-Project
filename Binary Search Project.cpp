#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "BinarySearch.h"

int main() {
    // Array sizes to test
    const size_t testSizes[] = { 5000, 50000, 100000, 150000, 200000 };

    // Loop through each size
    for (const size_t N : testSizes) {
        double SumRBS = 0, SumIBS = 0, SumSeqS = 0;

        for (int run = 0; run < 10; ++run) {
            // Fill vector with random numbers
            std::vector<int> vec(N);
            std::generate(vec.begin(), vec.end(), []() { return rand() % 100 + 1; });

            // Sort the vector for binary search
            std::sort(vec.begin(), vec.end());

            // Generate a random target value
            int target = rand() % 100 + 1;

            // Measure time for Recursive Binary Search
            auto start = std::chrono::high_resolution_clock::now();
            int index = recursiveBinarySearch(vec, target, 0, vec.size() - 1);
            auto end = std::chrono::high_resolution_clock::now();
            SumRBS += std::chrono::duration<double, std::micro>(end - start).count();

            // Measure time for Iterative Binary Search
            start = std::chrono::high_resolution_clock::now();
            index = iterativeBinarySearch(vec, target);
            end = std::chrono::high_resolution_clock::now();
            SumIBS += std::chrono::duration<double, std::micro>(end - start).count();

            // Measure time for Sequential Search
            start = std::chrono::high_resolution_clock::now();
            index = sequentialSearch(vec, target);
            end = std::chrono::high_resolution_clock::now();
            SumSeqS += std::chrono::duration<double, std::micro>(end - start).count();
        }

        // Output average running times for each algorithm
        std::cout << "Array Size: " << N << "\n";
        std::cout << "Average Running Time for Recursive Binary Search in microseconds: " << SumRBS / 10 << "\n";
        std::cout << "Average Running Time for Iterative Binary Search in microseconds: " << SumIBS / 10 << "\n";
        std::cout << "Average Running Time for Sequential Search in microseconds: " << SumSeqS / 10 << "\n";
    }

    return 0;
}
