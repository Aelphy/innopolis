from anonimizer import Anonimizer
from community_detector import CommunityDetector
import networkx as nx

class Processor():
    def __init__(self):
        self.graph = nx.Graph()
        self.edge_file = 'karate.net'
        self.comunity_graph = None


    def run(self):
        weights = []
        src = []
        dst = []

        with open(self.edge_file, 'r') as f:
            for line in f:
                parts = line.strip().split()

                if len(parts) == 3:
                    node1, node2, weight = parts
                    weights.append(float(weight))
                    src.append(int(node1))
                    dst.append(int(node2))
                else:
                    node1, node2 = parts
                    weights.append(1.0)
                    src.append(int(node1))
                    dst.append(int(node2))

                self.graph.add_edge(src[-1], dst[-1], weight = weights[-1])

        self.community_detector = CommunityDetector(self.graph)
        self.community_detector.fill_mod_matrix(src, dst, weights)
        self.comunity_graph = self.community_detector.run()

        return self.comunity_graph