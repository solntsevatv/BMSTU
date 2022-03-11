from algos import *
import time

iter = 1
test_sizes = [100, 250, 500, 750, 1000, 1250, 1500, 1750, 2000, 2250, 2500]

t_bubble = []
t_comb = []
t_insert = []

for test in test_sizes:
    time_bubble = 0
    time_comb = 0
    time_insert = 0
    for i in range(0, iter):
        arr = generate_random_test_array(test)
        t_start = time.process_time()
        bubble_sort(arr)
        time_insert += time.process_time() - t_start

        arr = generate_random_test_array(test)
        t_start = time.process_time()
        comb_sort(arr)
        time_comb += time.process_time() - t_start

        arr = generate_random_test_array(test)
        t_start = time.process_time()
        insert_sort(arr)
        time_bubble += time.process_time() - t_start
        
    time_bubble = time_bubble / iter
    time_comb = time_comb / iter
    time_insert = time_insert / iter
    t_bubble.append(time_bubble)
    t_comb.append(time_comb)
    t_insert.append(time_insert)

print(t_bubble, t_comb, t_insert)

import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

time_vals = []
time_vals.extend(t_bubble)
time_vals.extend(t_comb)
time_vals.extend(t_insert)

algos = []
algos.extend(['Пузырёк'] * len(t_bubble))
algos.extend(['Расчёска'] * len(t_comb))
algos.extend(['Вставки'] * len(t_insert))

length = test_sizes * 3

df = pd.DataFrame()
df["Время"] = time_vals
df["Алгоритмы"] = algos
df["Длина"] = length
 
sns.lineplot(data=df, y='Время', x='Длина', hue='Алгоритмы')
plt.show()