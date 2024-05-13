import os
import networkx as nx
import tsplib95
from typing import Dict

tsp_directory = "data/tsp/"
def TspToNetworkXGraph(filename: str) -> nx.classes.graph.Graph:
    tsp = tsplib95.load(filename)
    graph = nx.classes.graph.Graph(tsp.get_graph())
    return graph
def CollectTspFilesToGraphs(directory: str) -> Dict[str, nx.classes.graph.Graph]:
    graphs = {}
    for filename in os.listdir(directory):
        if filename.endswith(".tsp"):
            filepath = os.path.join(directory, filename)
            graph_name = os.path.splitext(filename)[0]
            graph = TspToNetworkXGraph(filepath)
            graphs[graph_name] = graph
    return graphs

# EXAMPLE 1.
# graph_dict = CollectTspFilesToGraphs(tsp_directory)
# example_graph = graph_dict['ch150']
# print(example_graph[1][3])