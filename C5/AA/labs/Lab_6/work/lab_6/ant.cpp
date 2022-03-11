#include "ant.h"

void ant::reset_ant()
{
	distance = 0;
	path.clear();
	current_pos = 0;
}

/*
false if not visited, true if visited
*/
bool ant::check_node_for_visided(int id)
{
	bool visited = false;
	for (auto& node : path)
	{
		if (node == id)
			visited = true;
	}
	return visited;
}
