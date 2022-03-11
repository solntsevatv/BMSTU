#include <iostream>
#include <chrono>
#include <random>
#include "Convolutionizer.h"
#include "tests.h"
#include "time.h"

int main()
{
    //test();

    Convolutionizer conv;
    
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;

    std::cout << "Enter dim [n]: ";
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));

    for (auto& row : matrix)
    {
        for (auto& elem : row)
        {
            elem = std::rand() % 9;
        }
    }

    std::cout << "Enter thread count: ";
    int thread_count = 1;
    std::cin >> thread_count;

    begin = std::chrono::steady_clock::now();
    std::vector<std::vector<int>> result_1 = conv.convolution(matrix);
    end = std::chrono::steady_clock::now();

    long long T1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

    begin = std::chrono::steady_clock::now();
    std::vector<std::vector<int>> result_2 = conv.convolution_parallel(matrix, thread_count);
    end = std::chrono::steady_clock::now();

    long long T2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

    std::cout << "T 1: " << T1 << std::endl;

    std::cout << "T 2: " << T2 << std::endl;
}