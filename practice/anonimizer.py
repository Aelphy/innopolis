import random

class Anonimizer():
    def __init__(self, graph):
        self.graph = graph

    def greedy_examination(self, v, i, k):
        min_degree = v[i]
        is_found = False
        n = len(v)

        for j in range(i, len(v)):
            if v[j] < min_degree:
                is_found = True

                if v[i] == (v[i - 1] if i != 0 else n):
                    if n - j + 1 < k:
                            return n - i + 1
                        else:
                            j - i
                    else:
                        if n - i + 1 < 2 * k or n - j + 1 < k:
                            return n - i + 1
                        else:
                            return max([k, j - i])

        if not is_found:
            return n - i + 1


    def relaxed edge creation(self, v, i, j):
        l = len(v)

        while l >= 1:
            l -= 1

            if not self.graph.has_edge(l, j):
                self.graph.add_edge(l, j)

                if self.graph.degree()[i] == self.graph.degree()[j]:
                    return l


    def multi_edge_creation(self, v, i, na):
        for j in range(i + 1, i + na - 1):
            while v[j] < d[i]:



    def single_edge_creation(self, v, i, na):
        for j in range(i + 1, i + na - 1):
            while self.graph.degree()[j] < self.graph.degree()[i]:
                candidates = []

                for l in range(j, len(v)):
                    if not self.graph.has_edge(l, j) and self.graph.degree()[l] < self.graph.degree()[i]:
                        candidates.append((l, j))

                if candidates:
                    edge = random.choice(candidates)
                    self.graph.add_edge(edge[0], edge[1])
                else:
                    return j
        return j


    def fkda(self):
        pass


    def run(self):
        degree = self.graph.degree()
