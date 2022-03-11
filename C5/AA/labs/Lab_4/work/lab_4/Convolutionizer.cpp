#include "Convolutionizer.h"

Convolutionizer::Convolutionizer(){}

std::vector<std::vector<int>> Convolutionizer::convolution(std::vector<std::vector<int>> matrix)
{
	std::vector<std::vector<int>> new_matrix(matrix.size() - 2, std::vector<int>(matrix[0].size() - 2, 0));

	apply_kernel(matrix, new_matrix);
	return new_matrix;
}

void apply_kernel_parallel(int i_s, int step, std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& new_matrix, std::vector<std::vector<int>>& kernel)
{
	for (int i_t = i_s; i_t < matrix.size() - 1; i_t += step)
	{
		for (int j_t = 1; j_t < matrix[i_t].size() - 1; j_t++)
		{
			int new_elem = 0;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					new_elem += matrix[i - 1 + i_t][j - 1 + j_t] * kernel[i][j];
				}
			}
			new_matrix[i_t - 1][j_t - 1] = new_elem;
		}
	}
}

std::vector<std::vector<int>> Convolutionizer::convolution_parallel(std::vector<std::vector<int>> matrix, int n_threads)
{
	std::vector<std::vector<int>> new_matrix(matrix.size() - 2, std::vector<int>(matrix[0].size() - 2, 0));

	std::vector<std::thread> threads;

	for (int i = 1; i <= n_threads; i++)
	{
		threads.push_back(std::thread(apply_kernel_parallel, i, n_threads, std::ref(matrix), std::ref(new_matrix), std::ref(kernel)));
	}

	for (auto& thread : threads)
		thread.join();
	threads.clear();


	return new_matrix;
}

void Convolutionizer::apply_kernel(std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& new_matrix)
{
	for (int i_t = 1; i_t < matrix.size() - 1; i_t++)
	{
		for (int j_t = 1; j_t < matrix[i_t].size() - 1; j_t++)
		{
			int new_elem = 0;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					new_elem += matrix[i - 1 + i_t][j - 1 + j_t] * kernel[i][j];
				}
			}
			new_matrix[i_t - 1][j_t - 1] = new_elem;
		}
	}
}

void Convolutionizer::print_matrix(std::vector<std::vector<int>>& matrix)
{
	for (auto& row : matrix)
	{
		for (auto& elem : row)
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
