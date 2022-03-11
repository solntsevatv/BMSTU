#include "matrix_generator.h"

void generate_graph(std::vector<std::vector<Path>>& path_matrix, std::vector<Node>& nodes, int node_count, int max_path_len)
{
	path_matrix = std::vector<std::vector<Path>>(node_count);
	
	for (int i = 0; i < node_count; i++)
	{
		bool equal = true;
		Node new_node = { (rand() % max_path_len), (rand() % max_path_len), false };

		while (equal)
		{
			equal = false;
			for (auto& node : nodes)
			{
				if (node.x == new_node.x && node.y == new_node.y)
				{
					new_node = { (rand() % max_path_len), (rand() % max_path_len), false };
					equal = true;
				}
			}
		}

		nodes.push_back(new_node);
	}

	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < nodes.size(); j++)
		{
			if (i != j)
			{
				path_matrix[i].push_back({ int(sqrtf(((nodes[i].x - nodes[j].x) * (nodes[i].x - nodes[j].x) + (nodes[i].y - nodes[j].y) * (nodes[i].y - nodes[j].y)))), j, 1 });
			}
		}
	}
}

void print_nodes(std::vector<Node>& nodes)
{
	std::cout << "Nodes:" << std::endl;
	for (int i = 0; i < nodes.size(); i++)
	{
		std::cout << "node #" << i << " , coords = {" << nodes[i].x << ", " << nodes[i].y << "}, visited = " << nodes[i].visited << std::endl;
	}
	std::cout << std::endl;
}

void print_path(std::vector<Path>& path)
{
	for (int j = 0; j < path.size(); j++)
	{
		std::cout << "   node to: " << path[j].node_to << ", distance: " << path[j].distance << ", ferromone: " << path[j].ferromone << std::endl;
	}
}

void print_paths(std::vector<std::vector<Path>>& path_matrix)
{
	std::cout << "Paths:" << std::endl;
	for (int i = 0; i < path_matrix.size(); i++)
	{
		std::cout << "paths for node #" << i << ":" << std::endl;
		print_path(path_matrix[i]);
	}
	std::cout << std::endl;
}