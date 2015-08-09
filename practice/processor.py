from anonimizer import Anonimizer
from community_detector import CommunityDetector
import networkx as nx
import matplotlib.pyplot as plt
import itertools

class Processor():
    def __init__(self):
        self.graph = nx.Graph()
        self.edge_file = 'karate.net'


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

                self.graph.add_edge(src[-1], dst[-1], weight=weights[-1])

        self.community_detector = CommunityDetector(self.graph)
        self.community_detector.fill_mod_matrix(src, dst, weights)
        self.communities = self.community_detector.run()

        # drawing
        # colors = ['b', 'r', 'g', 'y']
        # pos = nx.spring_layout(self.graph)

        # for i in range(len(self.communities)):
        #     nx.draw_networkx_nodes(self.graph, pos, nodelist=[i + 1], node_color=colors[self.communities[i]])
        # nx.draw_networkx_edges(self.graph, pos, edgelist=self.graph.edges())

        # plt.axis('off')
        # plt.show()

        # generate communities graph
        self.m_communities_graph = nx.MultiGraph()
        self.s_communities_graph = nx.Graph()
        communities = {}

        for node in set(self.communities):
            communities[node] = []

        for node in self.graph.nodes():
            communities[self.communities[node - 1]].append(node)

        for community_combination in itertools.combinations(communities.keys(), 2):
            for edge in itertools.product(communities[community_combination[0]], communities[community_combination[1]]):
                c_edge = (self.communities[edge[0] - 1], self.communities[edge[1] - 1])

                self.s_communities_graph.add_edge(c_edge[0], c_edge[1])
                self.m_communities_graph.add_edge(c_edge[0], c_edge[1])

        # drawing
        # pos = nx.spring_layout(self.communities_graph)

        # for community in communities:
        #     nx.draw_networkx_nodes(self.communities_graph, pos, nodelist=[community], node_color=colors[community])

        # nx.draw_networkx_edges(self.graph, pos, edgelist=self.communities_graph.edges())

        # plt.axis('off')
        # plt.show()

        self.s_anonimized_graph = Anonimizer(self.s_communities_graph).run()
        self.m_anonimized_graph = Anonimizer(self.m_communities_graph).run()
