from graph import *
from time import *
from simple_dfs import *
from parallel_dfs import *

import sys
sys.setrecursionlimit(4000)

graph_1 = generate_graph(1)
graph_2 = generate_graph(10)
graph_3 = generate_graph(11)

simple_dfs = SimpleDFS()
parallel_dfs = ParallelDFS()

res_simple_1 = simple_dfs.simple_dfs(1, graph_1)
res_parallel_1 = parallel_dfs.parallel_dfs(1, 2, graph_1)

res_simple_2 = simple_dfs.simple_dfs(1, graph_2)
res_parallel_2 = parallel_dfs.parallel_dfs(1, 2, graph_2)

res_simple_3 = simple_dfs.simple_dfs(1, graph_3)
res_parallel_3 = parallel_dfs.parallel_dfs(1, 2, graph_3)

print("One node test:", res_simple_1 == res_parallel_1)
print("Even node count test:", res_simple_2 == res_parallel_2)
print("Not even node count test:", res_simple_3 == res_parallel_3)