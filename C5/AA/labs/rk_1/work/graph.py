import networkx as nx
import matplotlib.pyplot as plt
import random as rd
import time as t

class Node:
    def __init__(self, id: int, connections: list[int]) -> None:
        self.id = id
        self.connections = connections

    def print_node(self) -> None:
        print('Node #', self.id)
        print('Connections: ', self.connections)

class Graph:
    def __init__(self, nodes: list[Node]) -> None:
        self.nodes = nodes

    def draw_graph(self) -> None:
        G = nx.DiGraph()
        all_connections = []
        for node in self.nodes:
            for connection in node.connections:
                all_connections.append((node.id, connection))

        G.add_edges_from(all_connections)

        pos = nx.spring_layout(G)
        nx.draw_networkx_nodes(G, pos, node_size = 250, node_color='#ffffff', edgecolors='#000000')
        nx.draw_networkx_labels(G, pos)
        nx.draw_networkx_edges(G, pos, arrows=False)
        plt.show()

    def print_graph(self) -> None:
        for node in self.nodes:
            node.print_node()

    def get_node_with_id(self, id: int) -> Node:
        for node in self.nodes:
            if node.id == id:
                return node

def generate_graph(node_col: int) -> Graph:
    if node_col == 1:
        nodes = [Node(1, [])]
        return Graph(nodes)
        
    nodes = [Node(id, []) for id in range(1, node_col + 1)]

    for node in nodes:
        conns = set()
        while len(conns) == 0:
            for i in range(1, rd.randint(1, node_col/2)):
                new_conn = rd.randint(1, node_col)
                if new_conn != node.id:
                    conns.add(new_conn)
        node.connections = list(conns)

    for node in nodes:
        for conn in node.connections:
            if node.id not in nodes[conn - 1].connections:
                nodes[conn - 1].connections.append(node.id)

    return Graph(nodes)

if __name__ == '__main__':
    '''
    nodes = [Node(1, [2, 3, 4]), Node(2, [1, 3]), Node(3, [1, 2, 4]), Node(4, [1, 3])]
    for node in nodes:
        node.print_node()
    graph = Graph(nodes)
    graph.draw_graph()
    '''
    graph = generate_graph(50)
    graph.print_graph()
    graph.draw_graph()