#pragma once
#include <iostream>
#include <vector>
#include <thread>

class Convolutionizer
{
public:
	Convolutionizer();

	std::vector<std::vector<int>> kernel = {
		{0, -1, 0},
		{-1, 5, -1},
		{0, -1, 0}
	};

	std::vector<std::vector<int>> convolution(std::vector<std::vector<int>> matrix);
	std::vector<std::vector<int>> convolution_parallel(std::vector<std::vector<int>> matrix, int n_threads);

	void apply_kernel(std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& new_matrix);

	void print_matrix(std::vector<std::vector<int>>& matrix);
};