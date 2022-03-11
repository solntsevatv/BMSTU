#pragma once
#include "matrix_generator.h"

class ant
{
public:
	std::vector<int> path;
	int distance;
	int current_pos;

	void reset_ant();
	bool check_node_for_visided(int id);
};