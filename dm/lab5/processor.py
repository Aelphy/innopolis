import networkx as nx
import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()

with open('data.txt') as f:
    for line in f:
        [user1, user2] = line.strip().split()

        G.add_edge(int(user1), int(user2))

# matrix = nx.to_numpy_matrix(G)

# plt.imshow(matrix, interpolation='nearest')
# plt.show()
