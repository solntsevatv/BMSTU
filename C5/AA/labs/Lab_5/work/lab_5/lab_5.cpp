#include <iostream>
#include <random>
#include <chrono>
#include "time.h"
#include "test.h"
#include "conveyor.h"

int main()
{
	conveyor conv;
	std::list<std::vector<int>> arrs;
	std::vector<int> min;
	std::vector<int> max;
	std::vector<int> sum;

	int arr_count;
	int arr_len;
	std::cout << "Enter gen params [arr_count] [arr_len]: ";
	std::cin >> arr_count >> arr_len;

	for (int i = 0; i < arr_count; i += 1)
	{
		std::vector<int> temp;
		for (int j = 0; j < arr_len; j++)
		{
			temp.push_back(rand());
		}
		arrs.push_back(temp);
	}

	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	begin = std::chrono::steady_clock::now();
	conv.count_arr(arrs, min, max, sum);
	end = std::chrono::steady_clock::now();

	std::cout << "Without conveyor:" << std::endl;
	std::cout << "time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << std::endl;
	for (auto& arr : arrs)
	{
		for (auto& elem : arr)
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (auto& elem : min)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	for (auto& elem : max)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	for (auto& elem : sum)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	max.clear();
	min.clear();
	sum.clear();
	std::cout << std::endl;

	begin = std::chrono::steady_clock::now();
	conv.count_arr_conv(arrs, min, max, sum);
	end = std::chrono::steady_clock::now();

	std::cout << "With conveyor:" << std::endl;
	std::cout << "time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << std::endl;
	for (auto& arr : arrs)
	{
		for (auto& elem : arr)
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (auto& elem : min)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	for (auto& elem : max)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	for (auto& elem : sum)
	{
		std::cout << elem << ' ';
	}
	
	max.clear();
	min.clear();
	sum.clear();

	std::cout << std::endl;
	begin = std::chrono::steady_clock::now();
	conv.count_arr_conv_log(arrs, min, max, sum);
	end = std::chrono::steady_clock::now();

	std::cout << "With conveyor & log:" << std::endl;
	std::cout << "time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << std::endl;
	for (auto& arr : arrs)
	{
		for (auto& elem : arr)
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (auto& elem : min)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	for (auto& elem : max)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	for (auto& elem : sum)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}