import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
import operator

def add(where, graphs, G):
    for graph in graphs:
        for node in graph:
            where.insert(0, node)
            G.remove_node(node)


def slash_burn(G, k):
    hubs = []
    spokes = []

    while len(G.nodes()) >= k:
        CC = sorted(nx.connected_components(G), key=len, reverse=True)
        GCC = CC.pop(0)

        add(spokes, CC, G)

        nodes = sorted(G.degree().items(), key=operator.itemgetter(1))

        for i in range(k):
            if len(nodes) > 0:
                node = nodes.pop()[0]
                hubs.append(node)
                G.remove_node(node)
            else:
                break

    return [hubs, spokes]


def matrix(verticies, G):
    matrix = np.zeros(shape=(len(verticies),len(verticies)))

    for (i,j), value in np.ndenumerate(matrix):
        if G.has_edge(verticies[i], verticies[j]):
            matrix[i][j] = 1

    return matrix


def main():
    G = nx.Graph()

    with open('data.txt') as f:
        for line in f:
            [user1, user2] = line.strip().split()

            G.add_edge(int(user1), int(user2))

    G1 = G.copy()

    hubs, spokes = slash_burn(G1, int(0.05 * len(G.nodes())))

    print 'total hubs number = {0}'.format(len(hubs))

    verticies = G.nodes()
    slash_burn_verticies = hubs + spokes
    degree_sorted_verticies = [node[0] for node in sorted(G.degree().items(), key=operator.itemgetter(1))]

    plt.imshow(matrix(slash_burn_verticies, G), interpolation='nearest')
    plt.show()


if __name__ == '__main__':
    main()

