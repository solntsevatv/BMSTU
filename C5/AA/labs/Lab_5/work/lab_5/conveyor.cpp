#include "conveyor.h"

void min_elem(std::vector<int> arr, int &min)
{
	min = arr[0];
	for (int i = 0; i < arr.size(); i++)
	{
		if (min > arr[i])
			min = arr[i];
	}
}

void max_elem(std::vector<int> arr, int& max)
{
	max = arr[0];
	for (int i = 0; i < arr.size(); i++)
	{
		if (max < arr[i])
			max = arr[i];
	}
}

void sum_elem(std::vector<int> arr, int& sum)
{
	sum = 0;
	for (int i = 0; i < arr.size(); i++)
	{
		sum += arr[i];
	}
}

void conveyor::count_arr(std::list<std::vector<int>>& arr, std::vector<int>& min, std::vector<int>& max, std::vector<int>& sum)
{
	std::list<std::vector<int>> temp_arr;
	temp_arr = arr;
	for (auto& arr_elem : temp_arr)
	{
		int temp = 0;
		min_elem(arr_elem, temp);
		min.push_back(temp);
		max_elem(arr_elem, temp);
		max.push_back(temp);
		sum_elem(arr_elem, temp);
		sum.push_back(temp);
	}
}

void conveyor::count_arr_conv(std::list<std::vector<int>>& arr, std::vector<int>& min, std::vector<int>& max, std::vector<int>& sum)
{
	std::vector<int> first_queue;
	std::vector<int> second_queue;
	std::vector<int> third_queue;

	std::list<std::vector<int>> temp_arr;
	temp_arr = arr;

	std::thread min_thread;
	std::thread max_thread;
	std::thread sum_thread;

	int temp_min = 0;
	int temp_max = 0;
	int temp_sum = 0;

	bool first_running = true;
	bool second_running = false;
	bool third_running = false;

	first_queue = temp_arr.front();
	temp_arr.pop_front();

	while (first_running || second_running || third_running)
	{
		if (first_running)
		{
			min_thread = std::thread(min_elem, first_queue, std::ref(temp_min));
			first_running = true;
		}

		if (second_running)
		{
			max_thread = std::thread(max_elem, second_queue, std::ref(temp_max));
			second_running = true;
		}

		if (third_running)
		{
			sum_thread = std::thread(sum_elem, third_queue, std::ref(temp_sum));
			third_running = true;
		}

		if (third_running)
		{
			sum_thread.join();
			sum.push_back(temp_sum);
			third_running = false;
		}

		if (second_running)
		{
			max_thread.join();
			third_queue = second_queue;
			max.push_back(temp_max);
			third_running = true;
			second_running = false;
		}

		if (first_running)
		{
			min_thread.join();
			second_queue = first_queue;
			min.push_back(temp_min);
			second_running = true;
			first_running = false;
			if (temp_arr.size() > 0)
			{
				first_queue = temp_arr.front();
				temp_arr.pop_front();
				first_running = true;
			}
		}
	}
}

void conveyor::count_arr_conv_log(std::list<std::vector<int>>& arr, std::vector<int>& min, std::vector<int>& max, std::vector<int>& sum)
{
	std::ofstream resfile;
	resfile.open("results.txt");

	std::vector<int> first_queue;
	std::vector<int> second_queue;
	std::vector<int> third_queue;

	std::list<std::vector<int>> temp_arr;
	temp_arr = arr;

	std::thread min_thread;
	std::thread max_thread;
	std::thread sum_thread;

	int temp_min = 0;
	int temp_max = 0;
	int temp_sum = 0;

	bool first_running = true;
	bool second_running = false;
	bool third_running = false;

	first_queue = temp_arr.front();
	temp_arr.pop_front();

	int num_first = 1;
	int num_second = 0;
	int num_third = 0;

	std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

	std::chrono::steady_clock::time_point begin_first;
	std::chrono::steady_clock::time_point end_first;

	std::chrono::steady_clock::time_point begin_second;
	std::chrono::steady_clock::time_point end_second;

	std::chrono::steady_clock::time_point begin_third;
	std::chrono::steady_clock::time_point end_third;
	long long temp_1;
	long long temp_2;

	while (first_running || second_running || third_running)
	{
		if (first_running)
		{
			begin_first = std::chrono::steady_clock::now();
			min_thread = std::thread(min_elem, first_queue, std::ref(temp_min));
			first_running = true;
		}

		if (second_running)
		{
			begin_second = std::chrono::steady_clock::now();
			max_thread = std::thread(max_elem, second_queue, std::ref(temp_max));
			second_running = true;
		}

		if (third_running)
		{
			begin_third = std::chrono::steady_clock::now();
			sum_thread = std::thread(sum_elem, third_queue, std::ref(temp_sum));
			third_running = true;
		}

		if (third_running)
		{
			sum_thread.join();
			end_third = std::chrono::steady_clock::now();
			temp_1 = std::chrono::duration_cast<std::chrono::nanoseconds>(begin_third - start_time).count();
			temp_2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_third - start_time).count();
			// conv_num, task_num, start_time, end_time
			resfile << 3 << ' ' << num_third << ' ' << temp_1 << ' ' << temp_2 << std::endl;
			sum.push_back(temp_sum);
			third_running = false;
		}

		if (second_running)
		{
			max_thread.join();
			end_second = std::chrono::steady_clock::now();
			temp_1 = std::chrono::duration_cast<std::chrono::nanoseconds>(begin_second - start_time).count();
			temp_2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_second - start_time).count();
			// conv_num, task_num, start_time, end_time
			resfile << 2 << ' ' << num_second << ' ' << temp_1 << ' ' << temp_2 << std::endl;
			
			third_queue = second_queue;
			num_third += 1;

			max.push_back(temp_max);
			third_running = true;
			second_running = false;
		}

		if (first_running)
		{
			min_thread.join();
			end_first = std::chrono::steady_clock::now();
			temp_1 = std::chrono::duration_cast<std::chrono::nanoseconds>(begin_first - start_time).count();
			temp_2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_first - start_time).count();
			// conv_num, task_num, start_time, end_time
			resfile << 1 << ' ' << num_first << ' ' << temp_1 << ' ' << temp_2 << std::endl;

			second_queue = first_queue;
			num_second += 1;

			min.push_back(temp_min);
			second_running = true;
			first_running = false;
			if (temp_arr.size() > 0)
			{
				first_queue = temp_arr.front();
				num_first += 1;
				temp_arr.pop_front();
				first_running = true;
			}
		}
		resfile.close();
	}
}
