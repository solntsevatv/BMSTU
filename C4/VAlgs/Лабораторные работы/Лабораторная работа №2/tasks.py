import pandas as pd
import functions as fc

table = {'x': [0, 1, 2, 3, 4, 5],
         'y': [0, 1, 2, 3, 4, 5],
         'z': [[0,  1,  4,  9, 16, 25],
            [ 1,  2,  5, 10, 17, 26], 
            [ 4,  5,  8, 13, 20, 29], 
            [ 9, 10, 13, 18, 25, 34], 
            [16, 17, 20, 25, 32, 41], 
            [25, 26, 29, 34, 41, 50]]}

def Func(x, y):
    return  x*x + y*y

def CountTable(table):
    for i in range(0, len(table["x"])):
        for j in range(0, len(table["y"])):
            table["z"][i][j] = Func(table["x"][i], table["y"][j])
    return table

def FormResultApproxTable(x, y, table, out_name):
    results = {"nx": [], "ny": [], "z": []}
    
    for n in range(1, 4):
        results["nx"].append(n)
        results["ny"].append(n)
        results["z"].append(round(fc.InterpolXY(n, n, x, y, table), 5))
    df = pd.DataFrame(results)
    df.to_csv(out_name + ".csv", index=False)

table = CountTable(table)
print(table)