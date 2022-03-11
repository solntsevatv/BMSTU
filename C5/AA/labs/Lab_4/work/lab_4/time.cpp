#include "time.h"

void test_time()
{
    Convolutionizer conv;

    std::ofstream resfile;
    resfile.open("results.txt");

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;

    for (int n = 100; n <= 2000; n += 100)
    {
        std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));

        for (auto& row : matrix)
        {
            for (auto& elem : row)
            {
                elem = std::rand() % 9;
            }
        }

        begin = std::chrono::steady_clock::now();
        conv.convolution(matrix);
        end = std::chrono::steady_clock::now();
        resfile << n << ' ' << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << ' ';

        int i = 1;

        while (i <= 64)
        {
            begin = std::chrono::steady_clock::now();
            conv.convolution_parallel(matrix, i);
            end = std::chrono::steady_clock::now();

            resfile << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << ' ';
            i *= 2;
        }

        resfile << std::endl;

    }
    resfile.close();
}