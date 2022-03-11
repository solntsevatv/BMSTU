#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <cmath>

struct Path
{
	int distance;
	int node_to;
	double ferromone;
};

struct Node
{
	int x;
	int y;
	bool visited;
};

void generate_graph(std::vector<std::vector<Path>>& path_matrix, std::vector<Node>& nodes, int node_count, int max_path_len);
void print_nodes(std::vector<Node>& nodes);
void print_paths(std::vector<std::vector<Path>>& path_matrix);