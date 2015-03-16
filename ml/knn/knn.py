import getopt
import sys

def euclidean_distance(vect1, vect2):
    total = 0

    if len(vect1) != len(vect2):
        print('Wrong feature vectors')
        exit(2)

    for i in range(len(vect1)):
        total = total + (vect1[i] - vect2[i]) ** 2

    return total ** 0.5


def run_test(test_file):
    global labeled_data
    errors = 0
    ok = 0

    with open(test_file) as f:
        for line in f:
            params = line.strip().split(',')
            features = []

            for i in range(1, len(params)):
                features.append(float(params[i]))

            minimal_distance = float('inf')
            current_class = None

            for class_name, examples in labeled_data.items():
                for example in examples:
                    if minimal_distance > euclidean_distance(features, example):
                        minimal_distance = euclidean_distance(features, example)
                        current_class = class_name

            if current_class == params[0]:
                ok = ok + 1
            else:
                errors = errors + 1
                print('Wrong test {0}\nclass name: {1}\nrecognized class: {2}'.format(features, params[0], current_class))

    print('accuracy: {0}'.format(ok / float(ok + errors)))


def initialize(training_file, test_file):
    global labeled_data

    with open(training_file) as f:
        for line in f:
            params = line.strip().split(',')

            if params[0] not in labeled_data:
                labeled_data[params[0]] = []

            buffer = []

            for i in range(1, len(params)):
                buffer.append(float(params[i]))

            labeled_data[params[0]].append(buffer)

    run_test(test_file)


if __name__ == '__main__':
    labeled_data = {}

    try:
        opts, args = getopt.getopt(sys.argv[1:], 'r:e:', ['training_file=', 'test_file='])
    except getopt.GetoptError:
        print('knn.py -tr <training_file> -te <test_file>')
        sys.exit(2)

    for opt, arg in opts:
        if opt == '-h':
            print('knn.py -tr <training_file> -te <test_file>')
            sys.exit()
        elif opt in ('-r', '--training_file'):
            training_file = arg
        elif opt in ('-e', '--test_file'):
            test_file = arg

    initialize(training_file, test_file)
