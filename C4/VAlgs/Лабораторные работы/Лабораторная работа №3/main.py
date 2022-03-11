import numpy as np
import matplotlib as mp
import math as m
import newton as nw

def func(x):
    return x*x

# Retunrs table x - first col, y - second col
def createTable(tabLen):
    returnTable = []
    x = np.arange(0, tabLen, 1)
    y = np.array([func(xi) for xi in x])
    table = np.array([x, y])
    table = np.array(table.T)
    for i in range(0, tabLen):
        returnTable.append({"x": table[i][0], "y": table[i][1]})
    table = np.array(returnTable)
    return table

def interpolateQubic(table):
    N = len(table)
    
    e = [0, 0]
    n = [0, 0]
    # count e, n
    for i in range(2, N):
        h_i = table[i]["x"] - table[i - 1]["x"]
        h_im = table[i - 1]["x"] - table[i - 2]["x"]

        f_i = 3 * ((table[i]["y"] - table[i - 1]["y"]) / h_i - (table[i - 1]["y"] - table[i - 2]["y"]) / h_im)

        e.append(- h_i / (h_im * e[i - 1] + 2 * (h_im + h_i)))

        n.append((f_i - h_i * n[i - 1]) / (h_im * e[i - 1] + 2 * (h_im + h_i)))
    
    c = [0] * (N - 1)
    c[N - 2] = n[-1]

    for i in range(N - 2, 0, -1):
        c[i - 1] = e[i] * c[i] + n[i]

    a = []
    b = []
    d = []

    for i in range(1, N):
        a.append(table[i - 1]["y"])

    for i in range(1, N - 1):
        h_i = table[i]["x"] - table[i - 1]["x"]
        
        b.append((table[i]["y"] - table[i - 1]["y"]) / h_i - h_i * (c[i] + 2 * c[i - 1]) / 3)
        d.append((c[i] - c[i - 1]) / (3 * h_i))

    h_N = table[-1]["x"] - table[-2]["x"]
    b.append((table[-1]["y"] - table[-2]["y"]) / h_N - h_N * 2 * c[-1] / 3)
    d.append(-c[-1] / (3 * h_N))

    koefs = [a, b, c, d]

    return koefs

def countX(x, table, koefs):
    for i in range(1, len(table)):
        if x >= table[i - 1]["x"] and x <= table[i]["x"]:
            dx = x - table[i - 1]["x"]
            return koefs[0][i - 1] + koefs[1][i - 1] * dx + koefs[2][i - 1] * dx * dx + koefs[3][i - 1] * dx * dx * dx

table = createTable(11)

koefs = interpolateQubic(table)

x_1 = 0.5
y_1 = func(x_1)
y_interp_1 = countX(x_1, table, koefs)
y_newton_1 = nw.NewtonApprox(x_1, 3, table)

x_2 = 5.5
y_2 = func(x_2) 
y_interp_2 = countX(x_2, table, koefs)
y_newton_2 = nw.NewtonApprox(x_2, 3, table)

print(x_1, y_1, y_interp_1, y_newton_1)
print(x_2, y_2, y_interp_2, y_newton_2)

from numpy import linspace
from matplotlib import pyplot as plt
X = np.arange(0, 11, 1)
Y = np.array([func(xi) for xi in X])
X_ext = linspace(min(X), max(X), 100)
Y_ext = X_ext ** 2
Y_newton = [nw.NewtonApprox(x, 3, table) for x in X_ext]
Y_interp = [countX(x, table, koefs) for x in X_ext]
plt.plot(X_ext, Y_ext, 'r--', label="x^2")
plt.plot(X_ext, Y_newton, 'g-.', label="newton 3")
plt.plot(X_ext, Y_interp, 'b-', label="splain 3")
plt.plot(X, Y, 'bo')
plt.legend()
plt.show()