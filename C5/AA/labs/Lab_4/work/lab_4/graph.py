def print_latex(scale, res):
    for i in range(0, len(res)):
        res_str = str(scale[i])
        for elem in res[i]:
            res_str += ' & ' + str(int(elem / 100))
        res_str += '\\\\'
        print(res_str)
    print()

scale = []
results = []

resfile = open("D:/Storage/Andrew/BMSTU/BMSTU/C5/AA/labs/Lab_4/work/lab_4/results.txt")
for line in resfile:
    temp_arr = line.split(' ')
    new_temp_arr = list(map(int, temp_arr[0:-1]))
    scale.append(int(new_temp_arr[0]))
    results.append(new_temp_arr[1:])

print_latex(scale, results)
'''
#print_latex(scale, results)

import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

results_unpacked = []

for i in range(0, 8):
    temp = []
    for res in results:
        temp.append(res[i])
    results_unpacked.append(temp)
    
time_vals = []
for res in results_unpacked:
    time_vals.extend(res)

algos = []
count = 1
algos.extend(['Свёртка'] * len(results_unpacked[0]))
i = 1
while i <= 64:
    name = 'Параллельная свертка, ' + str(i) + ' потоков'
    algos.extend([name] * len(results_unpacked[0]))
    i *= 2
    count += 1

length = scale * count


df = pd.DataFrame()
df["Время"] = time_vals
df["Алгоритмы"] = algos
df["Размерность"] = length
 
#with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
#    print(df)

sns.lineplot(data=df, y='Время', x='Размерность', hue='Алгоритмы')
plt.show()
'''