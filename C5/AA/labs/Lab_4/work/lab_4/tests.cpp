#include "tests.h"

void test()
{
	Convolutionizer conv;
	std::vector<std::vector<int>> matrix(5, std::vector<int>(5, 0));

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == j)
				matrix[i][j] = i + j;
		}
	}

	std::vector<std::vector<int>> correct_result = {
		{10, -6, 0},
		{-6, 20, -10},
		{0, -10, 30}
	};

	std::vector<std::vector<int>> result;
	bool flag;

	result = conv.convolution(matrix);
	flag = true;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (result[i][j] != correct_result[i][j])
				flag = false;
		}
	}
	std::cout << "TEST CONV SIMPLE: " << flag << std::endl;

	result = conv.convolution_parallel(matrix, 1);
	flag = true;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (result[i][j] != correct_result[i][j])
				flag = false;
		}
	}
	std::cout << "TEST CONV PARALLEL 1: " << flag << std::endl;

	result = conv.convolution_parallel(matrix, 2);
	flag = true;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (result[i][j] != correct_result[i][j])
				flag = false;
		}
	}
	std::cout << "TEST CONV PARALLEL 2: " << flag << std::endl;

	result = conv.convolution_parallel(matrix, 3);
	flag = true;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (result[i][j] != correct_result[i][j])
				flag = false;
		}
	}
	std::cout << "TEST CONV PARALLEL 3: " << flag << std::endl;

	result = conv.convolution_parallel(matrix, 4);
	flag = true;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (result[i][j] != correct_result[i][j])
				flag = false;
		}
	}
	std::cout << "TEST CONV PARALLEL 4: " << flag << std::endl;
}