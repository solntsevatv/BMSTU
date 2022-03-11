from concurrent.futures import thread
from graph import *
from time import *
from simple_dfs import *
from parallel_dfs import *

import sys
sys.setrecursionlimit(4000)

parallel_dfs = ParallelDFS()
simple_dfs = SimpleDFS()

thread_count = 1
while thread_count < 10:
    print(thread_count)
    for node_count in range(100, 1501, 50):
        t_end_s = 0
        t_end_p = 0
        for i in range(0, 10):
            graph = generate_graph(node_count)

            t_start_s = process_time_ns()
            res = simple_dfs.simple_dfs(1, graph)
            t_end_s += process_time_ns() - t_start_s
                
            t_start_p = process_time_ns()
            res = parallel_dfs.parallel_dfs(1, thread_count, graph)
            t_end_p += process_time_ns() - t_start_p
        t_end_s /= 10
        t_end_p /= 10
        print(node_count, t_end_s, t_end_p)

    thread_count *= 2