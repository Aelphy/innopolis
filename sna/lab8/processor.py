import networkx as nx
import matplotlib.pyplot as plt
import random
import operator

def delete_from_graph(G, strategy):
    graph_size = len(G.nodes())
    G_CC_size = len(sorted(nx.connected_components(G), key=len, reverse=True)[0])
    total = 0

    while G_CC_size > graph_size / 2:
        if strategy == 'random':
            node = random.choice(G.nodes())
        elif strategy == 'degree':
            node = sorted(G.degree().items(), key=operator.itemgetter(1), reverse=True)[0][0]
        elif strategy == 'betweenes':
            node = sorted(nx.betweenness_centrality(G).items(), key=operator.itemgetter(1), reverse=True)[0][0]

        G.remove_node(node)
        G_CC_size = len(sorted(nx.connected_components(G), key=len, reverse=True)[0])

        total += 1

    return total


G = nx.Graph()

with open('data.txt') as f:
    for line in f:
        [user1, user2] = line.strip().split()

        G.add_edge(int(user1), int(user2))

G_nodes_count = G.number_of_nodes()
G_edges_count = G.number_of_edges()

random_G = G.copy()
degree_G = G.copy()
betweenes_G = G.copy()

random_total = delete_from_graph(random_G, 'random')
degree_total = delete_from_graph(degree_G, 'degree')
betweenes_total = delete_from_graph(betweenes_G, 'betweenes')

print('random {0}%\ndegree {1}%\nbetweenes {2}%\n'.format(100 * random_total / float(G_nodes_count), 100 * degree_total / float(G_nodes_count), 100 * betweenes_total / float(G_nodes_count)))

random_G = nx.fast_gnp_random_graph(G_nodes_count, G_edges_count / float(G_nodes_count * (G_nodes_count - 1) / 2))

random_rG = random_G.copy()
degree_rG = random_G.copy()
betweenes_rG = random_G.copy()

r_random_total = delete_from_graph(random_rG, 'random')
r_degree_total = delete_from_graph(degree_rG, 'degree')
r_betweenes_total = delete_from_graph(betweenes_rG, 'betweenes')

print('random {0}%\ndegree {1}%\nbetweenes {2}%'.format(100 * r_random_total / float(G_nodes_count), 100 * r_degree_total / float(G_nodes_count), 100 * r_betweenes_total / float(G_nodes_count)))

fig = plt.figure()
sub = fig.add_subplot(231)
nx.draw(G)
sub = fig.add_subplot(232)
nx.draw(random_G)
sub = fig.add_subplot(233)
nx.draw(betweenes_G)

plt.show()
