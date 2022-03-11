import pandas as pd
import functions as fc

table = {
    "x": [0, 1, 2, 3, 4],
    "y": [0, 1, 2, 3, 4],
    "z": 
    [[0, 1, 4, 9, 16],
    [1, 2, 5, 10, 17],
    [4, 5, 8, 13, 20],
    [9, 10, 13, 18, 25],
    [16, 17, 20, 25, 32]]
}

def FormResultApproxTable(x, y, table, out_name):
    results = {"nx": [], "ny": [], "z": []}
    
    for n in range(1, 4):
        results["nx"].append(n)
        results["ny"].append(n)
        results["z"].append(round(fc.InterpolXY(n, n, x, y, table), 5))
    df = pd.DataFrame(results)
    df.to_csv(out_name + ".csv", index=False)

FormResultApproxTable(1.5, 1.5, table, "out")