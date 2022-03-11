#include "time.h"

void test_time()
{
	conveyor conv;
	std::list<std::vector<int>> arrs; // = { {1, 3, 4, -5}, {2, 4, 1, 4}, {1, 5, 2, 1}, {1, 3, 4, 5} };
	std::vector<int> min;
	std::vector<int> max;
	std::vector<int> sum;

	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	std::ofstream resfile;
	resfile.open("results.txt");

	for (int i = 10000; i <= 500000; i += 10000)
	{
		resfile << i << ' ';
		arrs.clear();
		for (int k = 0; k < 10; k++)
		{
			std::vector<int> temp;
			for (int j = 0; j < i; j++)
			{
				temp.push_back(rand());
			}
			arrs.push_back(temp);
		}
		long long count_avg = 0;
		long long conv_count_avg = 0;

		for (int i = 0; i < 10; i++)
		{
			begin = std::chrono::steady_clock::now();
			conv.count_arr(arrs, min, max, sum);
			end = std::chrono::steady_clock::now();
			count_avg += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

			max.clear();
			min.clear();
			sum.clear();
			begin = std::chrono::steady_clock::now();
			conv.count_arr_conv(arrs, min, max, sum);
			end = std::chrono::steady_clock::now();
			conv_count_avg += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
		}

		count_avg /= 10;
		conv_count_avg /= 10;

		resfile << count_avg << ' ';
		resfile << conv_count_avg << ' ';
		resfile << std::endl;
	}

	resfile.close();
}