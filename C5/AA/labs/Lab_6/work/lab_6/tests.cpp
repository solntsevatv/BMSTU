#include "tests.h"

void test()
{
    brute_force br_fc;
    ants ants_s;

    std::vector<std::vector<Path>> path_mat = {
        {{7, 1, 1}, {8, 2, 1}, {7, 3, 1}, {3, 4, 1}},
        {{7, 0, 1}, {6, 2, 1}, {8, 3, 1}, {4, 4, 1}},
        {{8, 0, 1}, {6, 1, 1}, {4, 3, 1}, {7, 4, 1}},
        {{7, 0, 1}, {8, 1, 1}, {4, 2, 1}, {7, 4, 1}},
        {{3, 0, 1}, {4, 1, 1}, {7, 2, 1}, {7, 3, 1}}
    };

    std::vector<Node> nodes = {{1, 7, 0}, {4, 0, 0}, {9, 4, 0}, {8, 8, 0}, {2, 4, 0}};

    std::vector<int> result_path;
    int result_len = 0;

    // common data test for brute force
    br_fc.brute_force_search(path_mat, nodes, result_path, result_len);
    std::vector<int> true_result_path = { 0, 3, 2, 1, 4, 0 };
    int true_result_len = 24;
    std::cout << "Test on common data for brute force: ";
    if (true_result_len == result_len && result_path == true_result_path)
    {
        std::cout << "PASSED" << std::endl;
    }
    else
    {
        std::cout << "NOT PASSED" << std::endl;
    }

    // small graph data test for brute force

    path_mat.clear();
    nodes = { {1, 7, 0} };
    result_path.clear();
    result_len = 0;

    br_fc.brute_force_search(path_mat, nodes, result_path, result_len);

    true_result_len = 0;
    true_result_path.clear();

    std::cout << "Test on small graph data for brute force: ";
    if (true_result_len == result_len && result_path == true_result_path)
    {
        std::cout << "PASSED" << std::endl;
    }
    else
    {
        std::cout << "NOT PASSED" << std::endl;
    }

    // small graph data test for ants

    path_mat.clear();
    nodes = { {1, 7, 0} };
    result_path.clear();
    result_len = 0;

    ants_s.ant_search(path_mat, nodes, result_path, result_len);

    true_result_len = 0;
    true_result_path.clear();

    std::cout << "Test on small graph data for ant algorythm: ";
    if (true_result_len == result_len && result_path == true_result_path)
    {
        std::cout << "PASSED" << std::endl;
    }
    else
    {
        std::cout << "NOT PASSED" << std::endl;
    }

    // incorrect graph data test for brute force

    path_mat = {
        {{7, 1, 1}, {8, 2, 1}, {7, 3, 1}, {3, 4, 1}},
        {{7, 0, 1}, {6, 2, 1}, {8, 3, 1}, {4, 4, 1}},
        {{8, 0, 1}, {6, 1, 1}, {4, 3, 1}, {7, 4, 1}},
        {{7, 0, 1}, {8, 1, 1}, {4, 2, 1}, {7, 4, 1}},
        {{3, 0, 1}, {4, 1, 1}, {7, 2, 1}}
    };

    nodes = { {1, 7, 0}, {4, 0, 0}, {9, 4, 0}, {8, 8, 0}, {2, 4, 0} };

    result_path.clear();
    result_len = 0;

    br_fc.brute_force_search(path_mat, nodes, result_path, result_len);

    true_result_len = 0;
    true_result_path.clear();

    std::cout << "Test on incorrect graph data for brute force: ";
    if (true_result_len == result_len && result_path == true_result_path)
    {
        std::cout << "PASSED" << std::endl;
    }
    else
    {
        std::cout << "NOT PASSED" << std::endl;
    }

    // incorrect graph data test for ants

    path_mat = {
        {{7, 1, 1}, {8, 2, 1}, {7, 3, 1}, {3, 4, 1}},
        {{7, 0, 1}, {6, 2, 1}, {8, 3, 1}, {4, 4, 1}},
        {{8, 0, 1}, {6, 1, 1}, {4, 3, 1}, {7, 4, 1}},
        {{7, 0, 1}, {8, 1, 1}, {4, 2, 1}, {7, 4, 1}},
        {{3, 0, 1}, {4, 1, 1}, {7, 2, 1}}
    };

    nodes = { {1, 7, 0}, {4, 0, 0}, {9, 4, 0}, {8, 8, 0}, {2, 4, 0} };

    result_path.clear();
    result_len = 0;

    ants_s.ant_search(path_mat, nodes, result_path, result_len);

    true_result_len = 0;
    true_result_path.clear();

    std::cout << "Test on incorrect graph data for ant algorythm: ";
    if (true_result_len == result_len && result_path == true_result_path)
    {
        std::cout << "PASSED" << std::endl;
    }
    else
    {
        std::cout << "NOT PASSED" << std::endl;
    }
}