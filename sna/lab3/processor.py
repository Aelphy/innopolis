from datetime import datetime as dt

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

        if u_list[2].strip() not in people.values():
            people[u] = u_list[2].strip()

        n_list = process_next_line()
        n = int(n_list[1])

        if n_list[2].strip() not in people.values():
            people[n] = n_list[2].strip()

        network_list[u] = {n : 1}

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
    if start in visited:
        return []

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


def process():
    visited = set()
    supernodes = []

    global network
    global people

    for u_id, name in people.items():
        candidate = dfs(network, u_id, visited)

        if candidate:
            supernodes.append(dfs(network, u_id, visited))

    supernodes = [x for x in supernodes if x]

    return supernodes
