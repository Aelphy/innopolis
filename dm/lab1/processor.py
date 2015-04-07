from itertools import combinations
import sys
import getopt
import time
import copy


def generate_new_itemsets(itemsets):
    if len(itemsets) == 0:
        return []

    gen_size = len(itemsets[0]) + 1

    candidates = []
    current_items = set()

    for itemset in itemsets:
        for item in itemset:
            current_items.add(item)

    for itemset in itemsets:
        for item in current_items - itemset:
            for combination in combinations(itemset, gen_size - 1):
                candidate = set(combination)
                candidate.add(item)

                if candidate not in itemsets:
                    break

            if candidate not in candidates:
                candidates.append(candidate)

    return candidates


def count(itemset):
    global items

    l_itemset = list(itemset)
    i_transactions = items[l_itemset[0]]

    for index in range(1, len(l_itemset)):
        i_transactions = i_transactions.intersection(items[l_itemset[index]])

    return len(i_transactions)


def produce_rules(itemset):
    if len(itemset) < 2:
        return []

    result = []

    support = count(itemset) / float(transaction_number)

    if support >= min_sup:
        k = len(itemset)

        while k > 1:
            for combination in combinations(itemset, k - 1):
                confidence = count(itemset) / float(count(set(combination)))

                if confidence >= min_conf:
                    result.append({'condition' : combination,
                                   'element' : itemset - set(combination),
                                   'support' : support,
                                   'confidence' : confidence})

            k = k - 1

    return result


def look_for_itemsets(frequent_itemsets):
    global transaction_number

    frequent_candidates_number = 0
    candidates_number = 0

    while True:
        total = 0

        next_itemset_size = max(frequent_itemsets.keys()) + 1

        previous_itemsets = frequent_itemsets[next_itemset_size - 1]

        candidates = generate_new_itemsets(previous_itemsets)

        for candidate in candidates:
            if count(candidate) >= min_sup * transaction_number:
                total = total + 1
                frequent_candidates_number = frequent_candidates_number + 1

                if next_itemset_size in frequent_itemsets:
                    frequent_itemsets[next_itemset_size].append(candidate)
                else:
                    frequent_itemsets[next_itemset_size] = [candidate]

        if total == 0:
            break

        print('level {0}: {1} itemsets, {2} frequent itemsets'.format(next_itemset_size, len(candidates), len(frequent_itemsets[next_itemset_size])))

    print(frequent_itemsets)


def initialize(frequent_itemsets, min_sup, file_name):
    global items
    global transaction_number

    frequent_candidates_number = 0
    candidates_number = 0

    with open(file_name) as f:
        for t_string in f:
            for item in t_string.strip().split(' '):
                i_item = int(item)

                if i_item in items:
                    items[i_item].add(transaction_number)
                else:
                    items[i_item] = {transaction_number}

            transaction_number = transaction_number + 1

    frequent_itemsets[1] = []

    for item, i_transactions in items.items():
        candidates_number = candidates_number + 1

        if len(i_transactions) >= min_sup * transaction_number:
            frequent_itemsets[1].append({item})

    frequent_candidates_number = frequent_candidates_number + len(frequent_itemsets[1])

    print('level {0}: {1} itemsets, {2} frequent itemsets'.format(1, candidates_number, frequent_candidates_number))


def output(frequent_itemsets):
    rules = []

    for level, itemsets in frequent_itemsets.items():
        for itemset in itemsets:
            for rule in produce_rules(itemset):
                if rule not in rules:
                    rules.append(rule)

    # printer = pprint.PrettyPrinter(indent = 4)
    # printer.pprint(rules)

    print('rules count: {0}\n'.format(len(rules)))


def start_apriory(min_sup, min_conf, file_name):
    global frequent_itemsets

    initialize(frequent_itemsets, min_sup, file_name)
    look_for_itemsets(frequent_itemsets)
    output(frequent_itemsets)


if __name__ == '__main__':
    frequent_candidates_number = 0
    min_sup = 0.6
    min_conf = 0.6
    file_name = 'retail.dat'

    try:
        opts, args = getopt.getopt(sys.argv[1:], 's:c:f:', ['min_sup=', 'min_conf=', 'file='])
    except getopt.GetoptError:
        print('process.py -s <min_sup> -c <min_conf> -f <file_name>')
        sys.exit(2)

    for opt, arg in opts:
        if opt == '-h':
            print('process.py -s <min_sup> -c <min_conf>')
            sys.exit()
        elif opt in ('-s', '--support'):
            min_sup = float(arg)
        elif opt in ('-c', '--conf'):
            min_conf = float(arg)
        elif opt in ('-f', '--file'):
            file_name = arg

    print('min support is {0} persent \nmin confidence is {1} percent'.format(min_sup * 100, min_conf * 100))

    start_time = time.time()
    transaction_number = 0
    items = {}
    frequent_itemsets = {}

    start_apriory(min_sup, min_conf, file_name)

    end_time = time.time()

    print('{0} seconds have gone'.format(end_time - start_time))
