import numpy as np
import matplotlib.pyplot as plt
import math
from scipy.spatial import cKDTree

params = {}
data = {}
wines = []
measures = []
stats = []
index = 0

def euclidian_distance(v1, v2):
    total = 0

    for i in range(len(v1)):
        total += (v1[i] - v2[i]) ** 2

    return total

with open('data.csv') as f:
    for line in f:
        if index == 0:
            for i, param in enumerate(line.strip().split(';')):
                params[i] = param
        else:
            wine = []

            for param in line.strip().split(';'):
                wine.append(float(param))

            wines.append(wine)

        index = index + 1

for i in range(len(params)):
    data[params[i]] = []

    for wine in wines:
        data[params[i]].append(wine[i])

for i in range(len(params)):
    stats.append({ 'mean' : np.mean(data[params[i]]), 'var' : np.var(data[params[i]]) })

for wine in wines:
    total = 0

    for i in range(len(params)):
        total += ((wine[i] - stats[i]['mean']) / math.sqrt(stats[i]['var'])) ** 2

    measures.append(total)

plt.hist(measures, bins=50)
plt.show()

tree = cKDTree(wines)
r = 80
nn = tree.query(wines, k = len(wines), distance_upper_bound = r)
neighbors = []

for i in range(len(wines)):
    neighbors.append(len([w for w in nn[0][i] if w < float('Inf')]))

# plt.hist(neighbors, bins = 50)
# plt.show()
