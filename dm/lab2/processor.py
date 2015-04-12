import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from sklearn import cross_validation
from sklearn.tree import DecisionTreeClassifier
from sklearn.naive_bayes import GaussianNB

g1 = []
g2 = []
g3 = []
features = []
dictionary = {}

with open('student/student-por.csv') as f:
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


names = ['Decision Tree']

features_train, features_test, g1_train, g1_test, g2_train, g2_test, g3_train, g3_test = cross_validation.train_test_split(features, g1, g2, g3, test_size=0.1, random_state=0)

classifier_g1 = DecisionTreeClassifier(criterion='entropy')
classifier_g2 = DecisionTreeClassifier(criterion='entropy')
classifier_g3 = DecisionTreeClassifier(criterion='entropy')

classifier_g1.fit(features_train, g1_train)
classifier_g2.fit(features_train, g2_train)
classifier_g3.fit(features_train, g3_train)

print classifier_g1.score(features_test, g1_test)
print classifier_g2.score(features_test, g2_test)
print classifier_g3.score(features_test, g3_test)

gnb_g1 = GaussianNB()
gnb_g2 = GaussianNB()
gnb_g3 = GaussianNB()

gnb_g1.fit(features_train, g1_train)
gnb_g2.fit(features_train, g2_train)
gnb_g3.fit(features_train, g3_train)

print gnb_g1.score(features_test, g1_test)
print gnb_g2.score(features_test, g2_test)
print gnb_g3.score(features_test, g3_test)
