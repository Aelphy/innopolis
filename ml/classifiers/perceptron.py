import os
import math
import random

emails_root = 'Emails'

answers = {'spam-train' : 1, 'nonspam-train' : -1}

words = set()
weights = {}
features = {}
b = 0
examples_count = 1
error_rate = 0.1

files = {'nonspam-train' : os.listdir(os.path.join(emails_root, 'nonspam-train')),
         'spam-train' : os.listdir(os.path.join(emails_root, 'spam-train'))}

def add_word_from_class(classname, words):
    for filename in files[classname]:
        with open(os.path.join(emails_root, classname, filename)) as f:
            for string in f:
                for word in string.strip().split(' '):
                    words.add(word)


def predict_class(filename, weights, b):
    vector = {}

    with open(filename) as f:
        for string in f:
            for word in string.strip().split(' '):
                if word not in vector:
                    vector[word] = 0

                vector[word] += 1

    a = 0

    for feature, value in vector.items():
        if feature in weights:
            a += weights[feature] * value

    a += b

    print([filename, a])



for classname in files.keys():
    add_word_from_class(classname, words)


for word in words:
    weights[word] = 0

errors = 0
max_iter = len(files['nonspam-train']) + len(files['spam-train'])

while True:
    classname = random.choice(files.keys())
    filename = random.choice(files[classname])

    with open(os.path.join(emails_root, classname, filename)) as f:
        for string in f:
                for word in string.strip().split(' '):
                    if word not in features:
                        features[word] = 0

                    features[word] += 1

    a = 0

    for feature, value in features.items():
        a += value * weights[feature]

    a += b

    if answers[classname] * a <= 0:
        errors += 1

        for feature, value in features.items():
            weights[feature] += value * answers[classname]

        b = b + answers[classname]

    if errors / float(examples_count) <= error_rate:
        break

    examples_count += 1

    print errors / float(examples_count)

# with open('weights.dat', 'rb') as f:
#     for string in f:
#         feature, value = string.strip().split('###')
#         weights[feature] = int(value)


for classname in ['spam-test', 'nonspam-test']:
    for filename in os.listdir(os.path.join(emails_root, classname)):
        predictcted_class = predict_class(os.path.join(emails_root, classname, filename), weights, b)
