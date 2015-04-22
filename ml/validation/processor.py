from sklearn import svm
from sklearn import cross_validation

y = []
x = []
x_test = []
y_test = []

with open('validation/Dog_Cat.train') as f:
    for line in f:
        features_vector = []

        for index, param in enumerate(line.strip().split()):
            if index == 0:
                y.append(int(param))
            else:
                features_vector.append(float(param.split(':')[1]))

        x.append(features_vector)

with open('validation/Dog_Cat.test') as f:
    for line in f:
        features_vector = []

        for index, param in enumerate(line.strip().split()):
            if index == 0:
                y_test.append(int(param))
            else:
                features_vector.append(float(param.split(':')[1]))

        x_test.append(features_vector)


linear_clf = svm.SVC(kernel='linear')
clf_5 = svm.SVC(kernel='poly', degree = 5)
linear_clf_cv = svm.SVC(kernel='linear')
clf_5_cv = svm.SVC(kernel='poly', degree = 5)

linear_clf.fit(x, y)
clf_5.fit(x, y)

scores_clf_5_cv = cross_validation.cross_val_score(clf_5_cv, x, y, cv=10)
scores_linear_clf_cv = cross_validation.cross_val_score(linear_clf_cv, x, y, cv=10)
