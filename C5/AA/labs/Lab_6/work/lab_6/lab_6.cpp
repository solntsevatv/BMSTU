#include <iostream>
#include "matrix_generator.h"
#include "brute_force.h"
#include "ants.h"
#include "tests.h"
#include "param_search.h"
#include "time.h"
#include <chrono>

int main()
{
    brute_force br_fc;
    ants ants_s;

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;

    std::vector<std::vector<Path>> path_mat;
    std::vector<Node> nodes;

    std::vector<int> result_path;
    int result_len = 0;

    int node_col;
    int max_distance;

    std::cout << "Enter graph params [node count, max distance]: ";
    std::cin >> node_col >> max_distance;

    generate_graph(path_mat, nodes, node_col, max_distance);
    begin = std::chrono::steady_clock::now();
    br_fc.brute_force_search(path_mat, nodes, result_path, result_len);
    end = std::chrono::steady_clock::now();
    std::cout << "time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanoseconds" << std::endl;

    std::cout << "result path: " << std::endl;
    for (int i = 0; i < result_path.size(); i++)
        std::cout << result_path[i] << ' ';

    std::cout << std::endl;
    std::cout << "min distance: " << result_len << std::endl;

    begin = std::chrono::steady_clock::now();
    ants_s.ant_search(path_mat, nodes, result_path, result_len);
    end = std::chrono::steady_clock::now();
    std::cout << "time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanoseconds" << std::endl;

    std::cout << "result path: " << std::endl;
    for (int i = 0; i < result_path.size(); i++)
        std::cout << result_path[i] << ' ';

    std::cout << std::endl;
    std::cout << "min distance: " << result_len << std::endl;

    print_nodes(nodes);
    print_paths(path_mat);

    //test();

    //select_params();

    //time();
}