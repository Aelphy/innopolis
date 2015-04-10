import math
import random
import numpy as np

clusters_number = 10

latitude = []
longitude = []
g_clusters = {}

with open('data.txt') as f:
    for line in f:
        params = line.split()

        latitude.append(float(params[2]))
        longitude.append(float(params[3]))

minimum_latitude = min(latitude)
minimum_longitude = min(longitude)
maximum_latitude = max(latitude)
maximum_longitude = max(longitude)

latitudes_centers = [random.uniform(minimum_latitude, maximum_latitude) for i in range(clusters_number)]
longitude_centers = [random.uniform(minimum_longitude, maximum_longitude) for i in range(clusters_number)]

count = 0

def euclidean_distance(p1, p2):
    return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

while True:
    change = 0
    clusters = {}

    for i in range(len(latitude)):
        minimum_distance = euclidean_distance([latitude[i], longitude[i]], [latitudes_centers[0], longitude_centers[0]])
        cluster = 0

        for j in range(1, len(latitudes_centers)):
            distance = euclidean_distance([latitude[i], longitude[i]], [latitudes_centers[j], longitude_centers[j]])

            if minimum_distance > distance:
                minimum_distance = distance
                cluster = j

        if cluster not in clusters:
            clusters[cluster] = []

        clusters[cluster].append([latitude[i], longitude[i]])

    g_clusters = clusters

    for i in g_clusters.keys():
        coordinates_storage = g_clusters[i]

        lat = [coordinates[0] for coordinates in coordinates_storage]
        lon = [coordinates[1] for coordinates in coordinates_storage]

        new_center = [np.mean(lat), np.mean(lon)]

        change += euclidean_distance([new_center[0], new_center[1]], [latitudes_centers[i], longitude_centers[i]])

        latitudes_centers[i] = new_center[0]
        longitude_centers[i] = new_center[1]

    if change < 0.1:
        break

    count += 1

    print '{0} - {1}'.format(count, change)


