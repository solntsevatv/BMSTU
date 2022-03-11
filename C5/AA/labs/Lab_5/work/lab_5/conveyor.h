#pragma once
#include <vector>
#include <thread>
#include <list>
#include <iostream>
#include <chrono>
#include <fstream>
#include <iostream>

class conveyor
{
public:

	void count_arr(std::list<std::vector<int>>& arr, std::vector<int>& min, std::vector<int>& max, std::vector<int>& sum);
	void count_arr_conv(std::list<std::vector<int>>& arr, std::vector<int>& min, std::vector<int>& max, std::vector<int>& sum);
	void count_arr_conv_log(std::list<std::vector<int>>& arr, std::vector<int>& min, std::vector<int>& max, std::vector<int>& sum);
};