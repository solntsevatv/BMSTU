import networkx as nx
import matplotlib.pyplot as plt
from concurrent.futures import thread
from graph import *
from time import *
from simple_dfs import *
from parallel_dfs import *

import sys
sys.setrecursionlimit(4000)

parallel_dfs = ParallelDFS()
simple_dfs = SimpleDFS()

node_col = int(input('Enter node count: '))
n_thread = int(input('Enter thread count: '))

t_end_s = 0
t_end_p = 0

graph = generate_graph(node_col)

t_start_s = process_time_ns()
res_1 = simple_dfs.simple_dfs(1, graph)
t_end_s += process_time_ns() - t_start_s
    
t_start_p = process_time_ns()
res_2 = parallel_dfs.parallel_dfs(1, n_thread, graph)
t_end_p += process_time_ns() - t_start_p

print('Simple results:')
print('Time: ', t_end_s)
print('Paths: ', res_1)

print('Parallel results:')
print('Time: ', t_end_p)
print('Paths: ', res_2)

graph.print_graph()
graph.draw_graph()