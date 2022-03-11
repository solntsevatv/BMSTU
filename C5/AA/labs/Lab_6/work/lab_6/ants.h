#pragma once
#include "matrix_generator.h"
#include "ant.h"
#include <random>
#include <limits>

class ants
{
public:
	int day_count = 300;
	int ant_count = 5;
	double alpha = 0.6;
	double beta = 0.4;
	double evap_rate = 0.8;
	double ferr_for_ant = 10;
	void ant_search(std::vector<std::vector<Path>>& paths, std::vector<Node>& nodes, std::vector<int>& result_path, int& result_len);
};