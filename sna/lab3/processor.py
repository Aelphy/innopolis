from datetime import datetime as dt

data_file = open('data.txt', 'rb')

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

    network[u] = [{n : 1}]

    is_votings_finished = False
    is_v = False

    while not is_votings_finished:
        v_list = process_next_line()

        if v_list[0] == 'V':
            is_v = True

            vote = int(v_list[1])
            user = int(v_list[2])

            network[u].append({user : vote})
        elif is_v:
            is_votings_finished = True


