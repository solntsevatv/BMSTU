from math import ceil
from re import sub
from tkinter import E
from traceback import print_tb
from tracemalloc import start
from unittest import result
from graph import *
from threading import *
from time import *
from random import *
import sys

sys.setrecursionlimit(4000)

class ParallelDFS():
    def __init__(self) -> None:
        pass

    def parallel_search_unvisited(self, node_ids: list[int], return_ids: list[list[int]], index: int, visited: set[int], graph: Graph):
        return_id = [None] * len(node_ids)

        for i in range(0, len(node_ids)):
            conns = graph.get_node_with_id(node_ids[i]).connections
            for j in range(0, len(conns)):
                if conns[j] not in visited:
                    return_id[i] = conns[j]
                    break
        return_ids[index] = return_id

    def parallel_dfs_subgraph(self, start_id: int, visited: set[int], graph: Graph):
        dead_end = False
        path = [start_id]
        visited.add(start_id)
        node = path[-1]

        while not dead_end:
            conns = graph.get_node_with_id(node).connections
            dead_end = True
            for conn in conns:
                if conn not in visited:
                    dead_end = False
                    path.append(conn)
                    node = conn
                    visited.add(conn)
                    break

        return path, visited
        
    
    def parallel_dfs(self, start_id: int, n_threads: int, graph: Graph):
        dead_end = False
        path = [start_id]
        visited = set()

        if len(graph.nodes) == 1:
            return [path]

        while not dead_end:
            node = path[-1]
            conns = graph.get_node_with_id(node).connections
            
            dead_end = True
            for conn in conns:
                if conn not in visited and dead_end:
                    dead_end = False
                    path.append(conn)
                    visited.add(node)
        
        visited.add(path[-1])

        all_nodes = set()
        for node in graph.nodes:
            all_nodes.add(node.id)
        
        paths = [path]        
        unchecked_queue = [[[], path]]

        while len(all_nodes) != len(visited):
            new_unchecked_queue = unchecked_queue.copy()
            for pair in unchecked_queue:
                path = pair[1]
                old_path = pair[0]

                # find unchecked nodes
                node_index = 0
                batch_size = ceil(len(path) / n_threads)
                batches = []
                batch = []

                path_len = len(path)
                while node_index < path_len:
                    batch.append(path[node_index])
                    if len(batch) == batch_size:
                        batches.append(batch)
                        batch = []
                    node_index += 1

                if len(batch) > 0:
                    if len(batches) == 0:
                        batches.append(batch)
                    else:
                        batches[-1].extend(batch)

                sum_size = 0
                for batch in batches:
                    sum_size += len(batch)

                result_ids = [[]] * len(batches)
                index = 0
                threads = []

                for batch in batches:
                    thread = Thread(target=self.parallel_search_unvisited, args=(batch, result_ids, index, visited, graph))
                    thread.start()
                    threads.append(thread)
                    index += 1

                for thread in threads:
                    thread.join()
                
                result_pass = []
                for result_id in result_ids:
                    result_pass.extend(result_id)
                result_pass.reverse() # this list contains inverted next node to check in path

                # search for unvisited vertex
                res_pass_len = len(result_pass)
                for i in range(0, res_pass_len):
                    if result_pass[i] != None and result_pass[i] not in visited:
                        new_path, visited = self.parallel_dfs_subgraph(result_pass[i], visited, graph)
                        new_res = path[:(res_pass_len - i)]
                        new_res.extend(new_path)
                        old_path.extend(new_res)
                        new_unchecked_queue.append([old_path, new_path]) # adding path and last added node to unchecked queue
                        paths.append(old_path)
            unchecked_queue = new_unchecked_queue

        return paths

if __name__ == '__main__':
    graph = generate_graph(400)
    parallel_dfs = ParallelDFS()
    
    t_start = process_time_ns()
    res = parallel_dfs.parallel_dfs(1, 1, graph)
    t_end = process_time_ns() - t_start
    print(t_end)

    t_start = process_time_ns()
    res = parallel_dfs.parallel_dfs(1, 2, graph)
    t_end = process_time_ns() - t_start
    print(t_end)

    t_start = process_time_ns()
    res = parallel_dfs.parallel_dfs(1, 4, graph)
    t_end = process_time_ns() - t_start
    print(t_end)

    t_start = process_time_ns()
    res = parallel_dfs.parallel_dfs(1, 8, graph)
    t_end = process_time_ns() - t_start
    print(t_end)
    #print(res)
    #graph.draw_graph()
    '''
    graph.print_graph()
    '''