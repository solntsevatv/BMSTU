'''
scale = []
results = []

resfile = res.split(',')

for line in resfile:
    try:
        temp_arr = line.split(' ')
        new_temp_arr = list(map(float, temp_arr))
        scale.append(int(new_temp_arr[0]))
        results.append(new_temp_arr[1:])
    except:
        pass

print(scale)
print(results)

#print_latex(scale, results)

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
algos.extend(['Не параллельный'] * len(results_unpacked[0]))
algos.extend(['Параллельный'] * len(results_unpacked[0]))

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
100 0.0 1562500.0,
150 3125000.0 3125000.0,
200 14062500.0 1562500.0,
250 6250000.0 9375000.0,
300 12500000.0 10937500.0,
350 14062500.0 14062500.0,
400 17187500.0 23437500.0,
450 26562500.0 20312500.0,
500 29687500.0 20312500.0,
550 34375000.0 25000000.0,
600 40625000.0 37500000.0,
650 46875000.0 40625000.0,
700 54687500.0 42187500.0,
750 67187500.0 48437500.0,
800 76562500.0 50000000.0,
850 90625000.0 67187500.0,
900 93750000.0 78125000.0,
950 123437500.0 75000000.0,
1000 115625000.0 93750000.0,
1050 135937500.0 90625000.0,
1100 145312500.0 100000000.0,
1150 160937500.0 114062500.0,
1200 168750000.0 129687500.0,
1250 185937500.0 132812500.0,
1300 210937500.0 139062500.0,
1350 229687500.0 160937500.0,
1400 239062500.0 151562500.0,
1450 259375000.0 190625000.0,
1500 275000000.0 179687500.0,
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