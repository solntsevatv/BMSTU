#include "test.h"

void test()
{
	conveyor conv;
	std::list<std::vector<int>> arrs = { {1, 3, 4, -5}, {2, 4, 1, 4}, {1, 5, 2, 1}, {1, 3, 4, 5} };
	std::vector<int> min;
	std::vector<int> max;
	std::vector<int> sum;

	std::vector<int> min_true = { -5, 1, 1, 1 };
	std::vector<int> max_true = { 4, 4, 5, 5 };
	std::vector<int> sum_true = { 3, 11, 9, 13 };

	conv.count_arr(arrs, min, max, sum);

	std::cout << "Without conveyor result:" << std::endl;
	std::cout << "Minimun correct: " << (min == min_true) << std::endl;
	std::cout << "Maximun correct: " << (max == max_true) << std::endl;
	std::cout << "Sum correct: " << (sum == sum_true) << std::endl;

	max.clear();
	min.clear();
	sum.clear();
	conv.count_arr_conv(arrs, min, max, sum);

	std::cout << "With conveyor result:" << std::endl;
	std::cout << "Minimun correct: " << (min == min_true) << std::endl;
	std::cout << "Maximun correct: " << (max == max_true) << std::endl;
	std::cout << "Sum correct: " << (sum == sum_true) << std::endl;
}