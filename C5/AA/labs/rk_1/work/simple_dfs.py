from graph import *
from time import *

import sys
sys.setrecursionlimit(4000)

class SimpleDFS:
    def __init__(self) -> None:
        pass

    def simple_dfs(self, start_id: int, graph: Graph) -> list[list[int]]:
        path = [start_id]
        if len(graph.nodes) == 1:
            return [path]
        visited = []
        paths, _ = self.simple_dfs_rec(path, visited, graph)
        return paths

    def simple_dfs_rec(self, path: list[int], visited: list[int], graph: Graph) -> list[list[int]]:
        paths = []
        visited.append(path[-1])
        dead_end = True
        for conn in graph.get_node_with_id(path[-1]).connections:
            if conn not in visited:
                dead_end = False
                new_path = path.copy()
                new_path.append(conn)
                res_path, visited = self.simple_dfs_rec(new_path, visited, graph)
                paths.extend(res_path)
                
        if dead_end:
            return [path], visited
        else:
            return paths, visited
    
if __name__ == '__main__':
    graph = generate_graph(400)
    simple_dfs = SimpleDFS()

    t_start = process_time_ns()
    res = simple_dfs.simple_dfs(1, graph)
    t_end = process_time_ns() - t_start

    print(t_end)
    #print(res)

    '''
    graph.print_graph()
    graph.draw_graph()
    '''