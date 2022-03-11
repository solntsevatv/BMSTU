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

resfile = open("D:/Storage/Andrew/BMSTU/BMSTU/C5/AA/labs/Lab_5/work/lab_5/results.txt")
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
algos.extend(['Без конвейера'] * len(results_unpacked[0]))
algos.extend(['С конвейером'] * len(results_unpacked[0]))

length = scale * 2


df = pd.DataFrame()
df["Время"] = time_vals
df["Алгоритмы"] = algos
df["Кол-во элементов в одном массиве"] = length
 
#with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
#    print(df)

sns.lineplot(data=df, y='Время', x='Кол-во элементов в одном массиве', hue='Алгоритмы')
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


res = '''
1 1 2900 20141800,
2 1 30015400 35058300,
1 2 29820600 42582600,
3 1 51763000 59150500,
2 2 49758300 65423100,
1 3 49545000 71573200,
3 2 82941800 98629500,
2 3 79447700 104511900,
1 4 79232900 108953300,
3 3 111954600 114019500,
2 4 111278500 115988000,
1 5 111163000 118624000,
3 4 122693000 124279400,
2 5 120866100 126324900,
1 6 120666900 127200300,
3 5 128527000 130745200,
2 6 127979500 131521400,
1 7 127898000 132199000,
3 6 133430100 135606000,
2 7 132917000 136353900,
1 8 132869900 138477000,
3 7 140910700 143018500,
2 8 140807800 144370600,
3 8 145263500 146321500,
'''
res_arr = res.split(',')

for row in res_arr:
    row_arr = row.split(' ')
    res_str = row_arr[0]
    for elem in row_arr[1:]:
        res_str += ' & ' + str(int(elem))
    res_str += '\\\\'
    res_str = res_str[1:]
    print(res_str)