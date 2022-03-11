import matplotlib.pyplot as plt
import numpy as np
import newton as nwt

def DisplayOriginalTalbe(table):
    x = np.arange(0, 5, 1)
    y = np.arange(0, 5, 1)

    X, Y = plt.np.meshgrid(x, y)
    Z = table

    fig = plt.figure(num=1, clear=True)
    ax = fig.add_subplot(1, 1, 1, projection='3d')
    ax.plot_surface(X, Y, Z)
    ax.set(xlabel='x', ylabel='y', zlabel='z')

    plt.show()

def ConvertVecXToTable(x, y):
    table = []
    for i in range(0, len(x)):
        table.append({"x": x[i], "y": y[i]})
    return table

def InterpolXY(nx, ny, x, y, table):
    vector_x = []
    for i in range(0, len(table["x"])):
        x_table = ConvertVecXToTable(table["x"], table["z"][i])
        vector_x.append(nwt.NewtonApprox(x, nx, x_table))
    y_table = ConvertVecXToTable(table["y"], vector_x)
    return nwt.NewtonApprox(y, ny, y_table)