#include "ants.h"


void ants::ant_search(std::vector<std::vector<Path>>& paths, std::vector<Node>& nodes, std::vector<int>& result_path, int& result_len)
{

	result_len = 0;
	result_path.clear();
	
	if (nodes.size() < 2)
		return;

	if (paths.size() < 2)
		return;

	for (auto& node : paths)
	{
		if (node.size() != nodes.size() - 1)
			return;
	}

	// initialize ants
	std::vector<ant> colony;
	result_len = std::numeric_limits<int>::max();

	for (int i = 0; i < ant_count; i++)
	{
		ant temp;
		temp.current_pos = rand() % nodes.size();
		temp.distance = 0;
		temp.path.push_back(temp.current_pos);
		colony.push_back(temp);
	}

	while (day_count > 0)
	{
		for (auto& ant : colony)
		{
			bool all_visited = false;
			while (!all_visited)
			{
				// Probability of going to node from paths
				double temp_sum = 0;
				std::vector<double> temp_top;
				std::vector<double> temp_prob;
				std::vector<Path> avalible_paths;

				for (auto& path : paths[ant.current_pos])
				{
					if (!ant.check_node_for_visided(path.node_to))
					{
						avalible_paths.push_back(path);
						double temp = pow(1.0f / (double)path.distance, alpha) * pow(path.ferromone, beta);
						temp_sum += temp;
						temp_top.push_back(temp);
					}
				}

				if (avalible_paths.size() > 0)
				{
					for (int i = 0; i < temp_top.size(); i++)
					{
						if (temp_sum > 0.001) 
							temp_prob.push_back(temp_top[i] / temp_sum);
					}

					double coin = ((double)rand() / (double)RAND_MAX);

					int index = 0;
					while (coin >= 0)
					{
						coin -= temp_prob[index];
						index++;
						if (index == avalible_paths.size())
							index = 0;
					}

					ant.path.push_back(avalible_paths[index].node_to);
					ant.current_pos = avalible_paths[index].node_to;
					ant.distance += avalible_paths[index].distance;
				}
				else
				{
					ant.path.push_back(ant.path[0]);

					for (int i = 0; i < paths[ant.current_pos].size(); i++)
					{
						if (paths[ant.current_pos][i].node_to == ant.path[0])
							ant.distance += paths[ant.current_pos][i].distance;
					}

					all_visited = true;
				}
			}
		}

		for (auto& ant_unit : colony)
		{
			if (ant_unit.distance > 0)
			{
				double delta_ferr = ferr_for_ant / (double)ant_unit.distance;
				for (int i = 0; i < ant_unit.path.size() - 1; i++)
				{
					for (auto& path : paths[ant_unit.path[i]])
					{
						if (path.node_to == ant_unit.path[i + 1])
						{
							path.ferromone = (1 - evap_rate) * path.ferromone + delta_ferr;
							if (path.ferromone < 0.01)
								path.ferromone = 0.01;
						}
					}
				}

				if (ant_unit.distance < result_len)
				{
					result_len = ant_unit.distance;
					result_path = ant_unit.path;
				}

				ant_unit.reset_ant();
				ant_unit.current_pos = rand() % nodes.size();
			}
		}

		day_count -= 1;
	}
}