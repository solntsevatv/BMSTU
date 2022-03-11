'''
def print_latex(scale, res):
    for i in range(0, len(res)):
        res_str = str(scale[i])
        for elem in res[i]:
            res_str += ' & ' + str(int(elem))
        res_str += '\\\\'
        print(res_str)
    print()

scale = []
results = []

resfile = open("D:/Storage/Andrew/BMSTU/BMSTU/C5/AA/labs/Lab_6/work/lab_6/results.txt")
for line in resfile:
    temp_arr = line.split(' ')
    new_temp_arr = list(map(int, temp_arr[0:-1]))
    scale.append(int(new_temp_arr[0]))
    results.append(new_temp_arr[1:])

print_latex(scale, results)

import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

results_unpacked = []

for i in range(0, 2):
    temp = []
    for res in results:
        temp.append(res[i])
    results_unpacked.append(temp)
    
time_vals = []
for res in results_unpacked:
    time_vals.extend(res)

algos = []
algos.extend(['Полный перебор'] * len(results_unpacked[0]))
algos.extend(['Муравьиный'] * len(results_unpacked[0]))

length = scale * 2


df = pd.DataFrame()
df["Время"] = time_vals
df["Алгоритмы"] = algos
df["Кол-во узлов в графе"] = length
 
#with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
#    print(df)

sns.lineplot(data=df, y='Время', x="Кол-во узлов в графе", hue='Алгоритмы')
plt.show()

'''
def print_latex(scale, res):
    for i in range(0, len(res)):
        res_str = str(scale[i])
        for elem in res[i]:
            res_str += ' & ' + str(int(elem))
        res_str += '\\\\'
        print(res_str)
    print()


res = """
150 5 0 1 0 10 34.6 28,
150 5 0 1 0.2 40 33.8 28,
200 5 0.4 0.6 0.4 20 34.8 28,
250 5 0 1 0.4 40 34.2 28,
250 5 0 1 0.8 10 34.8 28,
250 5 0 1 0.8 40 33.8 28,
250 5 0.2 0.8 0.8 20 34.6 28,
300 5 0 1 0 10 34 28,
300 5 0 1 0.2 10 34.6 28,
300 5 0 1 0.4 10 33.8 28,
300 5 0 1 0.6 10 34.8 28,
300 5 0.4 0.6 0.4 10 34.8 28,
300 5 0.6 0.4 0.6 40 34.4 28,
300 5 0.6 0.4 0.8 10 33.6 28,
350 5 0 1 0 20 34.4 28,
350 5 0 1 0 30 33.8 28,
350 5 0 1 0.8 10 33.8 28,
350 5 0 1 0.8 30 34.8 28,
350 5 0.2 0.8 0.2 20 34.8 28,
350 5 0.2 0.8 0.4 20 34.8 28,
350 5 0.2 0.8 0.8 40 34.8 28,
350 5 0.4 0.6 0.8 20 34.8 28,
350 5 0.6 0.4 0 30 34.6 28,
400 5 0 1 0 20 34.6 28,
400 5 0 1 0 30 34.6 28,
400 5 0 1 0.4 20 34.2 28,
400 5 0 1 0.8 20 34.8 28,
400 5 0 1 0.8 30 34.4 28,
400 5 0.2 0.8 0 30 34.2 28,
400 5 0.2 0.8 0.6 30 34.8 28,
400 5 0.2 0.8 0.6 40 34 28,
400 5 0.2 0.8 0.8 30 34.4 28,
400 5 0.4 0.6 0.4 10 34.8 28,
400 5 0.4 0.6 0.6 10 34.4 28,
400 5 0.6 0.4 0 10 34.8 28,
450 5 0 1 0 30 34.6 28,
450 5 0 1 0.2 10 34.4 28,
450 5 0 1 0.4 20 34.4 28,
450 5 0 1 0.4 30 34 28,
450 5 0 1 0.4 40 34.6 28,
450 5 0 1 0.8 10 34.4 28,
450 5 0 1 0.8 20 34.2 28,
450 5 0.2 0.8 0.6 10 34 28,
450 5 0.2 0.8 0.6 40 34.8 28,
450 5 0.4 0.6 0 20 34.8 28,
450 5 0.4 0.6 0.8 30 34.2 28,
450 5 0.6 0.4 0 20 34.6 28,
450 5 0.6 0.4 0.4 10 34.8 28,
450 5 0.8 0.2 0.2 30 34.8 28,
450 5 0.8 0.2 0.4 10 34.8 28,
500 5 0 1 0 30 34.2 28,
500 5 0 1 0.4 40 34.8 28,
500 5 0 1 0.6 20 34.4 28,
500 5 0 1 0.6 30 34.8 28,
500 5 0 1 0.8 10 34.8 28,
500 5 0 1 0.8 30 34.4 28,
500 5 0 1 0.8 40 34.4 28,
500 5 0.2 0.8 0.2 10 34.6 28,
500 5 0.2 0.8 0.4 40 34.6 28,
500 5 0.2 0.8 0.8 20 34.8 28,
500 5 0.2 0.8 0.8 30 34 28,
500 5 0.4 0.6 0.6 40 34.6 28,
500 5 0.4 0.6 0.8 10 34.2 28,
500 5 0.6 0.4 0.4 30 34.8 28,
500 5 0.6 0.4 0.6 40 33.8 28
"""
res_arr = res.split(',')

for row in res_arr:
    row_arr = row.split(' ')
    res_str = row_arr[0]
    for elem in row_arr[1:]:
        res_str += ' & ' + elem
    res_str += '\\\\'
    res_str = res_str[1:]
    print(res_str)