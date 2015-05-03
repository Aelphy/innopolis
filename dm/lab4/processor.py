from sklearn.tree import DecisionTreeClassifier
from sklearn.naive_bayes import GaussianNB
from sklearn import preprocessing
from sklearn import cross_validation
from deap import creator, base, tools, algorithms
import pandas as pd
import numpy as np
import random

g1 = []
g2 = []
g3 = []
dictionary = {}
features = []

def weighted_score(classifier, features, weights, answers):
    scores = cross_validation.cross_val_score(classifier, np.array(features) * np.array(weights) , answers, cv=5)
    print np.mean(scores)
    return np.mean(scores)

def fitness_value(individual):
    global features
    weights = [i for i in individual]
    return weighted_score(GaussianNB(), features, weights, g3)

def preprocess_data(dictionary, g1, g2, g3):
    features = []

    with open('student-mat.csv') as f:
        for index, line in enumerate(f):
            params = line.strip().split(';')

            if index == 0:
                for i in range(len(params)):
                    dictionary[i] = {'colname' : params[i], 'current_index' : 0}

            for i in range(len(params)):
                if params[i].isdigit():
                    params[i] = int(params[i])
                else:
                    if params[i] not in dictionary[i]:
                        dictionary[i]['current_index'] += 1
                        dictionary[i][params[i]] = dictionary[i]['current_index']

                    params[i] = dictionary[i][params[i]]

            g3.append(params[-1])
            g2.append(params[-2])
            g1.append(params[-3])

            features.append(params[0:-3])

        output_file = open('student-mat-pre.csv', 'w')

        output_file.write(';'.join([attrs['colname'] for attrs in  dictionary.values()]) + '\n')

        for i in range(len(features)):
            output_file.write(';'.join([str(feature) for feature in features[i] + [g1[i], g2[i], g3[i]]]) + '\n')

        output_file.close()


def main(dictionary, g1, g2, g3):
    global features
    preprocess_data(dictionary, g1, g2, g3)
    data = pd.read_csv('student-mat-pre.csv', delimiter = ';')
    cols = list(data.columns)
    cols.remove('G1')
    cols.remove('G2')
    cols.remove('G3')

    for col in cols:
        data[col] = (data[col] - data[col].mean()) / data[col].std(ddof=0)

    data.to_csv('temp')
    features = []

    with open('temp') as f:
        for index, line in enumerate(f):
            params = line.strip().split(',')

            if index != 0:
                for i in range(len(params)):
                    params[i] = float(params[i])

            features.append(params[1:-3])

    features = features[1:len(features)]

    tree_c = DecisionTreeClassifier(criterion='entropy')
    gnb_c = GaussianNB()

    creator.create('FitnessMax', base.Fitness, weights=(1.0,))
    creator.create("Individual", list, fitness=creator.FitnessMax)

    toolbox = base.Toolbox()
    toolbox.register('bit', random.random)
    toolbox.register('individual', tools.initRepeat, creator.Individual, toolbox.bit, n=30)
    toolbox.register('population',tools.initRepeat, list, toolbox.individual, n=200)
    toolbox.register('evaluate', fitness_value)
    toolbox.register('mate', tools.cxUniform, indpb=0.1)
    toolbox.register('mutate', tools.mutFlipBit, indpb=0.05)
    toolbox.register('select', tools.selNSGA2)

    population = toolbox.population()
    fits = toolbox.map(toolbox.evaluate, population)

    for fit, ind in zip(fits, population):
        ind.fitness.values = (fit,)

    for gen in range(100):
        offspring = algorithms.varOr(population, toolbox, lambda_ = 10, cxpb=0.5, mutpb=0.1)
        fits = toolbox.map(toolbox.evaluate, offspring)
        for fit, ind in zip(fits, offspring):
            ind.fitness.values = (fit,)
        population = toolbox.select(offspring+population, k=20)

    individual = tools.selBest(population, k=1)

if __name__ == '__main__':
    main(dictionary, g1, g2, g3)

