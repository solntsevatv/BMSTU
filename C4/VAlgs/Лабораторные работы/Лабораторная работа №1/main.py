import math as m
import pandas as pd

table = [
    {"x": 0.00, "y": 1.000000, "y'": -1.000000},
    {"x": 0.15, "y": 0.838771, "y'": -1.14944},
    {"x": 0.30, "y": 0.655336, "y'": -1.29552},
    {"x": 0.45, "y": 0.450447, "y'": -1.43497},
    {"x": 0.60, "y": 0.225336, "y'": -1.56464},
    {"x": 0.75, "y": -0.018310, "y'": -1.68164},
    {"x": 0.90, "y": -0.278390, "y'": -1.78333},
    {"x": 1.05, "y": -0.552430, "y'": -1.86742}]

def Divided_diff(x, y):
    new_y = []
    n = len(x) - len(y)
    for i in range(0, len(y) - 1):
        new_y.append((y[i] - y[i + 1]) / (x[i] - x[i + n + 1]))
    return new_y

def SortTableNewton(table, x, n):
    table = sorted(table, key=lambda d: abs(d["x"] - x))
    table = sorted(table[:n+1], key=lambda t: t["x"])
    return table

def FormXYNewton(table):
    X = []
    Y = []
    for row in table:
        X.append(row["x"])
        Y.append(row["y"])
    return X, Y

def CountDiffDivNewton(X, Y):
    Y_arr = [Y]
    while len(Y_arr[-1]) != 1:
        Y = Divided_diff(X, Y)
        Y_arr.append(Y)
    return Y_arr

def CountPolynomNewton(Y_arr):
    polym = []
    for Y in Y_arr:
        polym.append(Y[0])
    return polym

def GetValApproxNewton(polym, X, x):
    x_mult = 1
    result = 0
    for i in range(0, len(polym)):
        result += x_mult * polym[i]
        x_mult = x_mult * (x - X[i])
    return result

def NewtonApprox(x, n, table):

    table = SortTableNewton(table, x, n)
    X, Y = FormXYNewton(table)

    Y_arr = CountDiffDivNewton(X, Y)
    polym = CountPolynomNewton(Y_arr)
    
    return GetValApproxNewton(polym, X, x)

#==================================================================================================

def SortTableErmit(table, x, n):
    table = sorted(table, key=lambda d: abs(d["x"] - x))
    table = sorted(table[:m.floor(n/2) + 1], key=lambda t: t["x"])
    return table

def FormXYY_Ermit(table):
    X = []
    Y = []
    Y_ = []
    for row in table:
        X.append(row["x"])
        Y.append(row["y"])
        Y_.append(row["y'"])
    return X, Y, Y_

def Divided_diff_ermit(x, y, n):
    new_y = []
    n = n + 1 - len(y)
    for i in range(0, len(y) - 1):
        new_y.append((y[i] - y[i + 1]) / (x[int(i/2)] - x[int((i + n + 1)/2)]))
    return new_y

def FormY_arr(n, X, Y, Y_):
    Y_arr = [Y]
    new_Y = []
    j = 0
    k = 0
    Y = Divided_diff(X, Y)
    for i in range(0, n):
        if i % 2 == 0:
            new_Y.append(Y_[j])
            j += 1
        else:
            new_Y.append(Y[k])
            k += 1
    if len(new_Y) != 0:
        Y_arr.append(new_Y)
    return Y_arr

def CountDiffDivErmit(X, Y, Y_, n):
    Y_arr = FormY_arr(n, X, Y, Y_)
    if len(Y_arr) != 1:
        Y = Y_arr[-1]
    while len(Y_arr[-1]) != 1:
        Y = Divided_diff_ermit(X, Y, n)
        Y_arr.append(Y)
    return Y_arr

def CountPolynomErmit(Y_arr):
    polym = []
    for Y in Y_arr:
        polym.append(Y[0])
    return polym

def GetValApproxErmit(polym, X, x):
    x_mult = 1
    result = 0
    for i in range(0, len(polym)):
        result += x_mult * polym[i]
        x_mult = x_mult * (x - X[int(i/2)])
    return result

def ErmitApprox(x, n, table):
    table = SortTableErmit(table, x, n)
    X, Y, Y_ = FormXYY_Ermit(table)

    Y_arr = CountDiffDivErmit(X, Y, Y_, n)
    polym = CountPolynomErmit(Y_arr)

    return GetValApproxErmit(polym, X, x)

#==================================================================================================

def SortTableNewtonRoot(table, y, n):
    table = sorted(table, key=lambda d: abs(d["y"] - y))
    table = sorted(table[:n+1], key=lambda t: t["y"])
    return table

def NewtonRootApprox(n, table):
    y = 0
    table = SortTableNewtonRoot(table, y, n)
    Y, X = FormXYNewton(table)

    Y_arr = CountDiffDivNewton(X, Y)
    polym = CountPolynomNewton(Y_arr)
    
    return GetValApproxNewton(polym, X, y)

#================================================================================================== 

def FormResultApproxTable(x, table, out_name):
    results = {"n": [], "y for Newton": [], "y for Ermit": []}
    for n in range(0, 5):
        results["n"].append(n)
        results["y for Newton"].append(round(NewtonApprox(x, n, table), 5))
        results["y for Ermit"].append(round(ErmitApprox(x, n, table), 5))
    df = pd.DataFrame(results)
    df.to_csv(out_name + ".csv")

def FormRootApproxTable(table, out_name):
    results = {"n": [], "x for Newton": []}
    for n in range(0, 5):
        results["n"].append(n)
        results["x for Newton"].append(round(NewtonRootApprox(n, table), 5))
    df = pd.DataFrame(results)
    df.to_csv(out_name + ".csv")

FormResultApproxTable(0.525, table, "out_1")
FormResultApproxTable(0.55, table, "out_2")
FormResultApproxTable(0.575, table, "out_3")
FormRootApproxTable(table, "out_root")




