import math
import random
import numpy as np
from scipy import spatial

clusters_number = 10

coordinates = []
g_assigned = []
g_clusters = {}
min_neighbors = 10
g_visited = []
noise = []
eps = 5

def euclidean_distance(p1, p2):
    return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

def neighbors(p):
    data = tree.query(p, distance_upper_bound = eps, k = len(coordinates))

    return list(data[1][0:len([dist for dist in data[0] if dist < float('inf')])])


def expand_cluster(point, cluster, n, index):
    if cluster not in g_clusters:
        g_clusters[cluster] = []

    g_clusters[cluster].append(point)
    g_assigned[index] = True

    candidates = n

    while candidates:
        buf = []

        for p_index in n:
            print(len(g_visited))
            if p_index not in g_visited:
                g_visited.append(p_index)

                n1 = neighbors(coordinates[p_index])

                if len(n1) < min_neighbors:
                    noise.append(p_index)
                else:
                    buf += n1

            if not g_assigned[p_index]:
                g_clusters[cluster].append(coordinates[p_index])
                g_assigned[p_index] = True

        candidates = buf

with open('data.txt') as f:
    for line in f:
        params = line.split()

        coordinates.append([float(params[2]), float(params[3])])
        g_assigned.append(False)

tree = spatial.cKDTree(coordinates)

for i in range(len(coordinates)):
    if i not in g_visited:
        g_visited.append(i)

    n = neighbors(coordinates[i])

    if len(n) < min_neighbors:
        noise.append(i)
    else:
        clusers = g_clusters.keys()
        cluster = max(clusers) if clusers else 0
        g_clusters[cluster + 1] = []
        expand_cluster(coordinates[i], cluster, n, i)
