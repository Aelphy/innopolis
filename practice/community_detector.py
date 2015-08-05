import math
import random
import ipdb

class CommunityDetector():
    def __init__(self, graph):
        self.max_communities = float('inf')
        self.graph = graph
        self.modularity_matrix = []
        self.weights = []
        for edge in graph.edges():
            self.weights.append(self.graph.get_edge_data(edge[0], edge[1])['weight'])

        self.total_weight = sum(self.weights)
        self.n = len(self.graph.nodes())
        self.communities = []
        self.auto_C1 = 2.0
        self.auto_C2 = 1.5
        self.best_gain = 1.0
        self.threshold = 1e-6
        self.is_oriented = True
        self.community_number = 0


    def set_communities(self, new_communities):
        self.communities = new_communities
        self.community_number =  max(self.communities) + 1


    def modularity(self):
        result = 0

        for i in range(self.n):
            for j in range(self.n):
                if self.communities[i] == self.communities[j]:
                    result += self.modularity_matrix[i][j]

        return result


    def reassign(self, what, where):
        for i in range(len(what)):
            where[i] = what[i]


    def fill_mod_matrix(self, src, dst, weights):
        m = min(min(src), min(dst))
        self.weights = weights
        self.total_weight = sum(self.weights )

        if(m > 0):
            m = 1

        self.n = 1 + max(max(src), max(dst)) - m

        if not self.is_oriented:
            self.total_weight *= 2

        for i in range(self.n):
            self.modularity_matrix.append(self.n * [0])

        sumQ1 = self.n * [0]
        sumQ2 = self.n * [0]

        for i in range(len(src)):
            self.modularity_matrix[src[i] - m][dst[i] - m] += weights[i] / float(self.total_weight)

            if not self.is_oriented:
                self.modularity_matrix[dst[i] - m][src[i] - m] += weights[i] / float(self.total_weight)

            sumQ1[src[i] - m] += weights[i] / float(self.total_weight)
            sumQ2[dst[i] - m] += weights[i] / float(self.total_weight)

            if not self.is_oriented:
                sumQ1[dst[i] - m] += weights[i] / float(self.total_weight)
                sumQ2[src[i] - m] += weights[i] / float(self.total_weight)

        for i in range(self.n):
            for j in range(self.n):
                self.modularity_matrix[i][j] -= sumQ1[i] * sumQ2[j]

        for i in range(self.n):
            for j in range(self.n):
                self.modularity_matrix[i][j] = self.modularity_matrix[j][i]  = (self.modularity_matrix[i][j] + self.modularity_matrix[j][i]) / 2


    def init_modularity_matrix(self):
        if self.modularity_matrix:
            return

        for i in range(self.n):
            self.modularity_matrix.append(self.n * [0])

            for j in range(self.n):
                edge_data = self.graph.get_edge_data(i, j)['weight'] if self.graph.get_edge_data(i, j) else 0
                k = edge_data / float(self.total_weight)
                self.modularity_matrix[i][j] = k

        sumQ1 = self.n * [0]
        sumQ2 = self.n * [0]

        for i in range(self.n):
            for j in range(self.n):
                sumQ1[i] += self.modularity_matrix[i][j]
                sumQ2[j] += self.modularity_matrix[i][j]

        for i in range(self.n):
            for j in range(self.n):
                self.modularity_matrix[i][j] -= sumQ1[i] * sumQ2[j]

        for i in range(self.n):
            for j in range(self.n):
                self.modularity_matrix[i][j] = self.modularity_matrix[j][i]  = (self.modularity_matrix[i][j] + self.modularity_matrix[j][i]) / 2


    def community_indices(self, community):
        result = []

        for i in range(self.n):
            if self.communities[i] == community:
                result.append(i)

        return result


    def get_correction_vector(self, origin_community_indexes, dest_community_indexes):
        result = len(origin_community_indexes) * [0]

        for i in range(len(origin_community_indexes)):
            for j in range(len(dest_community_indexes)):
                result[i] += self.modularity_matrix[dest_community_indexes[j]][origin_community_indexes[i]]

        return result


    def get_modularity_submatrix(self, indices):
        n = len(indices)
        result = n * [None]

        for i in range(n):
            result[i] = n * [None]

            for j in range(n):
                result[i][j] = self.modularity_matrix[indices[i]][indices[j]]

        return result


    def compute_sum(self, matrix):
        n = len(matrix)
        result = n * [0]

        for i in range(n):
            for j in range(n):
                result[i] += matrix[i][j]

        return result


    def compute_mod_gain(self, Q, correction_vector, community):
        n = len(community)
        mod_gain = 0.0

        for i in range(n):
            for j in range(n):
                if community[i] == community[j]:
                    mod_gain += Q[i][j]
                else:
                    mod_gain -= Q[i][j]

        mod_gain *= 0.5

        for i in range(n):
            if community[i]:
                mod_gain += correction_vector[i]
            else:
                mod_gain -= correction_vector[i]

        return mod_gain


    def perform_kernighans_shift(self, Q, correction_vector, communities_old, communities_new):
        n = len(Q)
        gains = n * [0.0]

        for i in range(n):
            for j in range(n):
                if(i != j):
                    if communities_old[i] == communities_old[j]:
                        gains[i] -= Q[i][j]
                    else:
                        gains[i] += Q[i][j]

            if communities_old[i]:
                gains[i] -= correction_vector[i]
            else:
                gains[i] += correction_vector[i]

            gains[i] *= 2

        gains_got = n * [0.0]
        gains_indexes = n * [0]
        self.reassign(communities_old, communities_new)

        for i in range(n):
            gains_got[i] = max(gains)
            gains_index = gains.index(max(gains))
            gains_indexes[i] = gains_index

            if i > 0:
                gains_got[i] = gains_got[i] + gains_got[i - 1]

            for j in range(n):
                if communities_new[j] == communities_new[gains_index]:
                    gains[j] += 4 * Q[gains_index][j]
                else:
                    gains[j] -= 4 * Q[gains_index][j]

            communities_new[gains_index] = not communities_new[gains_index]
            gains[gains_index] = gains[gains_index] - 2 * n

        mod_gain = max(gains_got)
        steps_to_get_max_gain = gains_got.index(mod_gain) + 1

        if mod_gain > 0:
            self.reassign(communities_old, communities_new)

            for i in range(steps_to_get_max_gain):
                communities_new[gains_indexes[i]] = not communities_new[gains_indexes[i]]
        else:
            self.reassign(communities_old, communities_new)
            mod_gain = 0

        return mod_gain


    def split(self, Q, correction_vector, split_community):
        mod_gain = 0.0
        sum_Q = self.compute_sum(Q)
        n = len(Q)

        for i in range(n):
            Q[i][i] += 2 * correction_vector[i] - sum_Q[i]

        tries = pow(abs(math.log(self.best_gain)), self.auto_C2) / self.auto_C1 + 3
        try_i = 0

        while try_i < tries:
            try_i += 1
            communities0 = n * [None]

            for j in range(n):
                communities0[j] = random.choice([True, False])

            mod_gain0 = self.compute_mod_gain(Q, correction_vector, communities0)
            mod_gain1 = 1

            while mod_gain1 > self.threshold:
                communities_new = n * [None]
                mod_gain1 = self.perform_kernighans_shift(Q, correction_vector, communities0, communities_new)

                if mod_gain1 > self.threshold:
                    mod_gain0 += mod_gain1
                    communities0 = communities_new

            if mod_gain < mod_gain0:
                self.reassign(communities0, split_community)
                mod_gain = mod_gain0

            if mod_gain <= self.threshold:
                tries = int(tries / 2)

        if abs(mod_gain) < self.threshold:
            self.reassign(n * [True], split_community)

        return mod_gain


    def re_calc(self, moves, splits_communities, origin, dest):
        moves[origin][dest] = 0

        if origin != dest:
            origin_community_indexes = self.community_indices(origin)

            if origin_community_indexes:
                correction_vector = self.get_correction_vector(origin_community_indexes, self.community_indices(dest))
                split_community = len(origin_community_indexes) * [False]
                Q = self.get_modularity_submatrix(origin_community_indexes)

                moves[origin][dest] = self.split(Q, correction_vector, split_community)

                for i in range(len(split_community)):
                    splits_communities[dest][origin_community_indexes[i]] = split_community[i]


    def is_community_empty(self, comm):
        for i in range(self.n):
            if self.communities[i] == comm:
                return False

        return True


    def delete_community_if_empty(self, comm):
        if self.is_community_empty(comm):
            comms = set()

            for i in range(self.n):
                if self.communities[i] > comm:
                    self.communities[i] -= 1

                comms.add(self.communities[i])

            self.community_number = len(comms)
            return True

        return False


    def delete_empty_communities(self, moves, splits_communities, origin):
        if self.delete_community_if_empty(origin):
            communities_count = self.community_number

            for i in range(origin, communities_count):
                moves[i] = moves[i + 1]
            moves[communities_count] = (communities_count + 2) * [0]

            for i in range(len(moves)):
                for j in range(origin, communities_count + 1):
                    moves[i][j] = moves[i][j + 1]
                moves[i][communities_count + 1] = 0

            for i in range(origin, communities_count + 1):
                splits_communities[i] = splits_communities[i + 1]


    def compute_best_gain(self, moves):
        best_gain = -1.0

        for i in range(len(moves)):
            for j in range(len(moves)):
                if best_gain < moves[i][j]:
                    best_gain = moves[i][j]
                    origin = i
                    dest = j

        return best_gain, origin, dest


    def perform_split(self, origin, dest, splits_communities):
        if dest > self.community_number:
            dest = self.community_number
        if dest == self.community_number:
            self.community_number += 1

        for i in range(self.n):
            if self.communities[i] == origin and splits_communities[i]:
                self.communities[i] = dest

        return dest


    def run(self):
        self.init_modularity_matrix()
        self.set_communities(self.n * [0])
        current_modularity = self.modularity()

        moves = 2 * [None]
        splits_communities = 2 * [None]

        for i in range(2):
            moves[i] = 2 * [0]
            splits_communities[i] = self.n * [False]

        for origin in range(self.community_number):
            dest = 0
            while dest < (self.community_number + int(self.community_number < self.max_communities)):
                self.re_calc(moves, splits_communities, origin, dest)
                dest += 1

        self.best_gain, origin, dest = self.compute_best_gain(moves)

        while self.best_gain > self.threshold:
            comunity_added = dest >= self.community_number

            dest = self.perform_split(origin, dest, splits_communities[dest])

            if comunity_added and dest < self.max_communities - 1:
                if dest >= len(moves) - 1:
                    for move in moves:
                        move.append(0)

                    moves.append((len(moves) + 1) * [0])
                    splits_communities.append(self.n * [False])

                for i in range(dest):
                    moves[i][dest + 1] = moves[i][dest]
                    splits_communities[dest + 1] = splits_communities[dest]

            i = 0

            while i < (self.community_number + int(self.community_number < self.max_communities)):
                self.re_calc(moves, splits_communities, origin, i)
                self.re_calc(moves, splits_communities, dest, i)

                if i != dest and i < self.community_number:
                    self.re_calc(moves, splits_communities, i, origin)
                if i != origin and i < self.community_number:
                    self.re_calc(moves, splits_communities, i, dest)

                i += 1

            self.delete_empty_communities(moves, splits_communities, origin)
            self.best_gain, origin, dest = self.compute_best_gain(moves)

        return self.communities
