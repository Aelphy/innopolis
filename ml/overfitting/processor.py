import matplotlib.pyplot as plt
import numpy as np

x_c = []
y_c = []

with open('x.dat') as f:
    for line in f:
        x_c.append(float(line))

with open('y.dat') as f:
    for line in f:
        y_c.append(float(line))

# plt.plot(x, y)
# plt.show()

x = np.zeros(shape=(len(x_c), 6))
y = np.zeros(shape=len(x_c))

for i in range(len(x_c)):
    x[i][0] = 1
    y[i] = y_c[i]
    for j in range(1, 6):
        x[i][j] = x_c[i] ** j

l = 10
weights = np.dot(np.dot(np.linalg.inv(np.dot(x.T, x) + l * np.identity(6)), x.T), y)

y_1 = np.dot(x, weights)
plt.plot(x_c, y_1)
plt.show()
