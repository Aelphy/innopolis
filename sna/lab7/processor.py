import networkx as nx
import matplotlib.pyplot as plt

G = nx.DiGraph()

with open('soc-Epinions1.txt') as f:
    for line in f:
        [user1, user2] = line.strip().split()

        G.add_edge(int(user1), int(user2))

max_connections_number = len(G.nodes())
statuses = []
positive_fractions = []
similarietes = []
status_differences = []

for node in G.nodes():
    status = G.in_degree(node)
    positive_fraction = status / float(max_connections_number)

    statuses.append(status)
    positive_fractions.append(positive_fraction)

    voters = G.predecessors(node)

    for voter in voters:
        difference = G.in_degree(voter) - status
        similarity = len(set(voters).intersection(set(G.predecessors(voter)))) / float(len(voters) + len(G.predecessors(voter)))

        similarietes.append(similarity)
        status_differences.append(difference)

plt.plot(status_differences, similarietes)
plt.show()
