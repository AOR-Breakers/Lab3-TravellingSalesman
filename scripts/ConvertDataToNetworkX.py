import os
import networkx as nx
import tsplib95
from pathlib import Path
from typing import Dict

tsp_data_directory = "../data/tsp/"
raw_data_directory = "../data/raw/"


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
            offset = 0
            if not graph.has_node(0):
                offset = -1
                mapping = {i: i - 1 for i in range(graph.number_of_nodes() + 1)}
                graph = nx.relabel_nodes(graph, mapping)
            graphs[graph_name] = (graph, offset)
    return graphs


# EXAMPLE 1.
# graph_dict = CollectTspFilesToGraphs(tsp_data_directory)
# example_graph = graph_dict['ch150']
# print(example_graph[1][3])

# EXAMPLE 2.
# graph_dict = CollectTspFilesToGraphs(tsp_data_directory)
# example_graph = graph_dict['ch150']
# print(nx.readwrite.write_weighted_edgelist(example_graph, raw_data_directory + 'ch150'))


if __name__ == "__main__":
    graphs_dict = CollectTspFilesToGraphs(tsp_data_directory)

    for _, problem_name in enumerate(graphs_dict):
        current_graph, offset = graphs_dict[problem_name]
        raw_data_filename = raw_data_directory + problem_name

        nx.readwrite.write_weighted_edgelist(current_graph, raw_data_filename)
        with open(raw_data_filename, "r+") as file:
            data = file.read()
            file.seek(0, 0)
            file.write(
                f"{current_graph.number_of_nodes()} {current_graph.number_of_edges()} {offset}\n"
            )
            file.write(data)
