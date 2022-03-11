#pragma once
#include "matrix_generator.h"
#include <cmath>
#include <limits>
#include <iostream>

class brute_force
{
public:
	void brute_force_search(std::vector<std::vector<Path>>& path_matrix, std::vector<Node>& nodes, std::vector<int> &result_path, int &result_len);
	void find_path_for_node(int& start_node, int node_id, std::vector<Node> nodes, std::vector<std::vector<Path>>& paths, std::vector<int>& min_path, int& min_dist);
};

