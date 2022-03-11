#include "param_search.h"

struct test_sample
{
	int day_count;
	int ant_count;
	double alpha;
	double evap_rate;
	double ferr_for_ant;
};

void test_algos(std::vector<test_sample> test_samples)
{
	std::vector<std::vector<Path>> short_paths;
	std::vector<Node> short_nodes;
	std::vector<int> short_result_path;

	int short_result_len = 0;

	std::vector<std::vector<Path>> long_paths;
	std::vector<Node> long_nodes;
	std::vector<int> long_result_path;

	int long_result_len = 0;

	int true_len = 0;
	std::vector<int> true_result_path;

	generate_graph(short_paths, short_nodes, 10, 10);

	ants ants_s;
	brute_force br_fc;

	br_fc.brute_force_search(short_paths, short_nodes, true_result_path, true_len);

	print_nodes(short_nodes);
	print_paths(short_paths);

	int count = 0;

	std::cout << "progress: " << 100 * (float)count / (float)test_samples.size() << "%, processed " << count << " out of " << test_samples.size() << std::endl;
	int processed = 0;
	int processed_new = 0;

	for (auto& test : test_samples)
	{
		double avg_min_len = 0;

		for (int i = 0; i < 5; i++)
		{
			for (auto& node : short_paths)
			{
				for (auto& path : node)
				{
					path.ferromone = 1;
				}
			}

			ants_s.ant_count = test.ant_count;
			ants_s.day_count = test.day_count;

			ants_s.alpha = test.alpha;
			ants_s.beta = 1.0 - test.alpha;
			ants_s.evap_rate = test.evap_rate;
			ants_s.ferr_for_ant = test.ferr_for_ant;

			ants_s.ant_search(short_paths, short_nodes, short_result_path, short_result_len);
			avg_min_len += short_result_len;
		}

		count++;
		processed = floor(100 * (float)count / (float)test_samples.size());
		if (processed > processed_new)
		{
			std::cout << "progress: " << 100 * (float)count / (float)test_samples.size() << "%, processed " << count << " out of " << test_samples.size() << std::endl;
			processed_new = processed;
		}
		avg_min_len /= 5;

		if ((double)avg_min_len * 0.8 < true_len)
			std::cout << test.day_count << ' ' << test.ant_count << ' ' << test.alpha << ' ' << 1.0 - test.alpha << ' ' << test.evap_rate << ' ' << test.ferr_for_ant << ' ' << avg_min_len << ' ' << true_len << std::endl;
	}
}

void select_params()
{
	/*
	int day_count = 1500;
	int ant_count = 10;
	double alpha = 0.5;
	double beta = 0.5;
	double evap_rate = 0.03;
	double ferr_for_ant = 1.8;
	*/

	// initial set
	int min_ant_count = 5;
	int max_ant_count = 5;
	int ant_step = 1;
	
	double alpha_step = 0.2;
	double min_alpha = 0;
	double max_alpha = 1;

	double min_evap_rate = 0;
	double max_evap_rate = 1;
	double evap_step = 0.2;

	double min_ferr_for_ant = 10;
	double max_ferr_for_ant = 50;
	double ferr_for_ant_step = 10;

	int min_day_count = 50;
	int max_day_count = 500;
	int day_count_step = 50;
	
	std::vector<test_sample> test_samples;
	
	for (int day_count = min_day_count; day_count <= max_day_count; day_count += day_count_step)
	{
		for (int ant_count = min_ant_count; ant_count <= max_ant_count; ant_count += ant_step)
		{
			for (double alpha = min_alpha; alpha < max_alpha; alpha += alpha_step)
			{
				for (double evap_rate = min_evap_rate; evap_rate < max_evap_rate; evap_rate += evap_step)
				{
					for (double ferr_for_ant = min_ferr_for_ant; ferr_for_ant < max_ferr_for_ant; ferr_for_ant += ferr_for_ant_step)
					{
						test_samples.push_back({ day_count, ant_count, alpha, evap_rate, ferr_for_ant });
					}
				}
			}
		}
	}

	test_algos(test_samples);
}