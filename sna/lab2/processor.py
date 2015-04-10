from datetime import datetime as dt
import itertools

data_file = open('data.txt', 'rb')

network_list = {}
network = {}
people = {}

def process_next_line():
    line = data_file.readline()

    if not line:
        return None
    elif line.startswith('#'):
        return process_next_line()
    else:
        return line.split('\t')


def initialize():
    global network_list
    global network

    is_processed_tuple = False

    while not is_processed_tuple:
        e_list = process_next_line()

        if e_list:
            e = int(e_list[1])
        else:
            is_processed_tuple = True
            continue

        t_list = process_next_line()
        t = dt.strptime(t_list[1], '%Y-%m-%d %H:%M:%S\t')

        u_list = process_next_line()
        u = int(u_list[1])

        if u_list[2].strip() and u > 0 not in people.values():
            people[u] = u_list[2].strip()

        n_list = process_next_line()
        n = int(n_list[1])

        people[n] = n_list[2].strip()

        if n > 0:
            network_list[u] = {n : 1}
        else:
            network_list[u] = {}

        is_votings_finished = False
        is_v = False

        while not is_votings_finished:
            v_list = process_next_line()

            if v_list[0] == 'V':
                is_v = True

                vote = int(v_list[1])
                user = int(v_list[2])

                if user not in network_list[u]:
                    network_list[u][user] = vote
                    people[user] = v_list[4].strip()
            elif is_v:
                is_votings_finished = True

    for user, votes in network_list.items():
        for voter, vote in votes.items():
            if vote != 0 and (voter not in network_list or user not in network_list[voter] or network_list[voter][user] != - vote):
                if  user not in network:
                    network[user] = {}

                if  voter not in network:
                    network[voter] = {}

                if  voter not in network[user]:
                    network[user][voter] = vote

                if  user not in network[voter]:
                    network[voter][user] = vote



def dfs(graph, start, visited):
    stack = [start]
    current = set()

    while stack:
        vertex = stack.pop()

        if vertex not in visited:
            visited.add(vertex)
            current.add(vertex)

            candidates = set()

            if vertex in graph:
                for u_id, vote in graph[vertex].items():
                    if vote == 1:
                        candidates.add(u_id)
            stack.extend(candidates - visited)

    return current


def is_balanced(supernode):
    for c1 in itertools.combinations(supernode, 3):
        total = 0
        next_c1 = False

        for c2 in itertools.combinations(c1, 2):
            if c2[0] in network and c2[1] in network[c2[0]]:
                total = total + network[c2[0]][c2[1]]
            else:
                next_c1 = True
                break

        if not next_c1:
            if total not in [3, -1]:
                return False

    return True


def delete_negative(supernode):
    for c1 in itertools.combinations(supernode, 3):
        total = 0
        next_c1 = False

        for c2 in itertools.combinations(c1, 2):
            if c2[0] in network and c2[1] in network[c2[0]]:
                total = total + network[c2[0]][c2[1]]
            else:
                next_c1 = True
                break

        if not next_c1:
            if total not in [3, -1]:
                for c2 in itertools.combinations(c1, 2):
                    if c2[0] in network and c2[1] in network[c2[0]] and network[c2[0]][c2[1]] == -1:
                        supernode.remove(c2[0])
                        break

                break

    return supernode


def process():
    visited = set()
    supernodes = []

    global network
    global people

    for u_id, name in people.items():
        if u_id in visited:
            continue

        candidate = dfs(network, u_id, visited)

        if candidate:
            supernodes.append(candidate)

    supernodes = [x for x in supernodes if x]

    return supernodes
