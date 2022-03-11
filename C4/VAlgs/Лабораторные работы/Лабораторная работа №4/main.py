import math as m
import numpy as np
import random as rd
from numpy import linalg as lg

def countNPowerPolym(a, x):
    y = 0
    for i in range(0, len(a)):
        y += a[i] * x ** i
    return y

def funcScalarMult(phi, fi, k, m, P):
    scalarMult = 0
    for i in range(0, len(P)):
        scalarMult += P[i] * (phi[i] ** k) * (fi[i] ** m)
    return scalarMult

def formA(X, P, N):
    A = np.zeros([N, N])
    for i in range(0, N):
        for j in range(0, N):
            A[i][j] = funcScalarMult(X, X, i, j, P)
    return A

def formB(X, Y, P, N):
    B = np.zeros([N, 1])
    for i in range(0, N):
            B[i][0] = funcScalarMult(Y, X, 1, i, P)
    return B

def bestRmsApproximation(X, Y, P, n):
    N = n + 1
    A = formA(X, P, N)
    B = formB(X, Y, P, N)
    koefArr = np.dot(lg.inv(A), B)
    return koefArr

def generateValues(N, y_interval):
    i = 0
    P = []
    X = []
    Y = []
    while i < N:
        P.append(rd.uniform(1, 1))
        X.append(rd.uniform(i, i + 1) * 10)
        Y.append(rd.uniform(y_interval[0], y_interval[1]))
        i += 1
    return X, Y, P

from numpy import linspace
from matplotlib import pyplot as plt

def plotGraph(X, Y, P):

    P_1 = [1.0, 0.0, 1.0, 2.0, 0.0]
    
    a_1 = bestRmsApproximation(X, Y, P, 1)
    a_2 = bestRmsApproximation(X, Y, P_1, 1)
    a_3 = bestRmsApproximation(X, Y, P, 3)
    a_4 = bestRmsApproximation(X, Y, P, 4)

    X_1 = linspace(min(X), max(X), 100)
    Y_1 = [countNPowerPolym(a_1, x) for x in X_1]

    X_2 = linspace(min(X), max(X), 100)
    Y_2 = [countNPowerPolym(a_2, x) for x in X_2]

    X_3 = linspace(min(X), max(X), 100)
    Y_3 = [countNPowerPolym(a_3, x) for x in X_3]

    X_4 = linspace(min(X), max(X), 100)
    Y_4 = [countNPowerPolym(a_4, x) for x in X_4]

    plt.plot(X, Y, 'bo')
    plt.plot(X_1, Y_1, 'r', label="1")
    plt.plot(X_2, Y_2, 'g', label="2")
    #plt.plot(X_3, Y_3, 'b', label="3")
    #plt.plot(X_4, Y_4, 'y', label="4")
    plt.legend()
    plt.show()

import tkinter as tk

def updateGraph():
    P = []
    for i in range(1, 6):
        P.append(float(cols[i][2].get()))
    plt.close()
    X, Y, P_ = generateValues(5, [0, 10])
    plotGraph(X, Y, P)
    
def generate():
    X, Y, P = generateValues(5, [0, 10])
    for i in range(1, 6):
        cols[i][0].delete(0, tk.END)
        cols[i][0].insert(0, str(X[i - 1]))
        cols[i][1].delete(0, tk.END)
        cols[i][1].insert(0, str(Y[i - 1]))
        cols[i][2].delete(0, tk.END)
        cols[i][2].insert(0, str(P[i - 1]))
    plt.close()
    plotGraph(X, Y, P)

root = tk.Tk()

cols = []
for i in range(6):
    rows = []
    for j in range(3):
        e = tk.Entry(root, relief=tk.GROOVE)
        e.grid(row=i, column=j, sticky=tk.NSEW)
        rows.append(e)
    cols.append(rows)

cols[0][0].insert(0, str("X"))
cols[0][1].insert(0, str("Y"))
cols[0][2].insert(0, str("P"))

update = tk.Button(root, text="Обновить", command=updateGraph)
generate = tk.Button(root, text="Генерировать", command=generate)
update.grid()
generate.grid()
tk.mainloop()