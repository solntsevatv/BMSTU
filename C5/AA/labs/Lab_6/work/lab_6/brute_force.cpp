#include "brute_force.h"

void brute_force::brute_force_search(std::vector<std::vector<Path>>& path_matrix, std::vector<Node>& nodes, std::vector<int>& result_path, int& result_len)
{
	result_len = 0; 
	result_path.clear();

	if (nodes.size() < 2)
		return;

	if (path_matrix.size() < 2)
		return;

	for (auto& node : path_matrix)
	{
		if (node.size() != nodes.size() - 1)
			return;
	}

	result_len = std::numeric_limits<int>::max();

	bool all_visited = false;
	int start_node = 0;
	find_path_for_node(start_node, 0, nodes, path_matrix, result_path, result_len);
}

void brute_force::find_path_for_node(int &start_node, int node_id, std::vector<Node> nodes, std::vector<std::vector<Path>>& paths, std::vector<int>& min_path, int& min_dist)
{
	nodes[node_id].visited = true;
	
	std::vector<int> temp_path = min_path;
	temp_path.push_back(node_id);

	int new_min_distance;
	bool all_visited = true;
	for (auto& node : nodes)
	{
		if (node.visited == false)
			all_visited = false;
	}

	for (int i = 0; i < paths[node_id].size(); i++)
	{
		if (nodes[paths[node_id][i].node_to].visited == false)
		{
			std::vector<int> temp_min_path = temp_path;
			int temp_min_dist = min_dist;
			find_path_for_node(start_node, paths[node_id][i].node_to, nodes, paths, temp_min_path, temp_min_dist);
			if (temp_min_dist < min_dist)
			{
				min_dist = temp_min_dist;
				min_path = temp_min_path;
			}
		}

		if (nodes[paths[node_id][i].node_to].visited == true && all_visited && paths[node_id][i].node_to == start_node)
		{
			temp_path.push_back(start_node);

			int temp_dist = 0;
			int from;
			int to;

			for (int i = 0; i < temp_path.size() - 1; i++)
			{
				from = temp_path[i];
				to = temp_path[i + 1];
				for (auto& path : paths[from])
				{
					if (path.node_to == to)
						temp_dist += path.distance;
				}
			}

			if (temp_dist < min_dist)
			{
				min_dist = temp_dist;
				min_path = temp_path;
			}
		}
	}
}