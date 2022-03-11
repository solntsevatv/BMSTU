#include "time.h"

void time()
{
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	std::ofstream resfile;
	resfile.open("results.txt");

	for (int node_col = 2; node_col <= 10; node_col++)
	{
        long long brute_force_avg = 0;
        long long ant_avg = 0;
        
        for (int i = 0; i < 10; i++)
        {
            brute_force br_fc;
            ants ants_s;

            std::vector<std::vector<Path>> path_mat;
            std::vector<Node> nodes;

            std::vector<int> result_path;
            int result_len = 0;

            int max_distance = 10;

            generate_graph(path_mat, nodes, node_col, max_distance);

            begin = std::chrono::steady_clock::now();
            br_fc.brute_force_search(path_mat, nodes, result_path, result_len);
            end = std::chrono::steady_clock::now();
            brute_force_avg += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

            begin = std::chrono::steady_clock::now();
            ants_s.ant_search(path_mat, nodes, result_path, result_len);
            end = std::chrono::steady_clock::now();
            ant_avg += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        }

        brute_force_avg /= 10;
        ant_avg /= 10;

        resfile << brute_force_avg << ' ';
        resfile << ant_avg << ' ';
        resfile << std::endl;
	}

	resfile.close();
}