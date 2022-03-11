import time
from source_data_files import gen_data as gd
from algos import *

test_sizes = [1000000] #[300000, 350000, 400000, 450000, 500000] #[100000, 150000, 200000, 250000, 300000, 350000, 400000, 450000, 500000]

t_seq_start = []
t_bin_start = []
t_seg_start = []

t_seq_center = []
t_bin_center = []
t_seg_center = []

t_seq_end = []
t_bin_end = []
t_seg_end = []

t_seq_none = []
t_bin_none = []
t_seg_none = []

test_records = []

for size in test_sizes:
    test_records.append(gd.generate_vals(size))

iters = 1

for record in test_records:
    keys = list(record)
    key_start = keys[0]
    key_center = keys[int(len(keys)/2)]
    key_end = keys[-1]
    key_none = 'aboba'

    t_result = 0
    for i in range(0, iters):
        t_start = time.process_time_ns()
        seq_search(record, key_start)
        t_result += time.process_time_ns() - t_start
    #t_result /= iters
    t_seq_start.append(t_result)

    t_result = 0
    for i in range(0, iters):
        list_keys = sorted(list(record.keys()))
        t_start = time.process_time_ns()
        res = bin_search_presort(record, key_start, list_keys)
        t_result += time.process_time_ns() - t_start
        print(res)
    #t_result /= iters
    t_bin_start.append(t_result)
    print(t_result)

    t_result = 0
    for i in range(0, iters):
        new_record = gen_dict_for_seg(record)
        t_start = time.process_time_ns()
        seg_search(new_record, key_start)
        t_result += time.process_time_ns() - t_start
    #t_result /= iters
    t_seg_start.append(t_result)


    t_result = 0
    for i in range(0, iters):
        t_start = time.process_time_ns()
        seq_search(record, key_center)
        t_result += time.process_time_ns() - t_start
    #t_result /= iters
    t_seq_center.append(t_result)

    t_result = 0
    for i in range(0, iters):
        list_keys = sorted(list(record.keys()))
        t_start = time.process_time_ns()
        bin_search_presort(record, key_center, list_keys)
        t_result += time.process_time_ns() - t_start
    #t_result /= iters
    t_bin_center.append(t_result)

    t_result = 0
    for i in range(0, iters):
        new_record = gen_dict_for_seg(record)
        t_start = time.process_time_ns()
        seg_search(new_record, key_center)
        t_result += time.process_time_ns() - t_start
    #t_result /= iters
    t_seg_center.append(t_result)


    t_result = 0
    for i in range(0, iters):
        t_start = time.process_time_ns()
        seq_search(record, key_end)
        t_result += time.process_time_ns() - t_start
    #t_result /= iters
    t_seq_end.append(t_result)

    t_result = 0
    for i in range(0, iters):
        list_keys = sorted(list(record.keys()))
        t_start = time.process_time_ns()
        bin_search_presort(record, key_end, list_keys)
        t_result += time.process_time_ns() - t_start
    #t_result /= iters
    t_bin_end.append(t_result)

    t_result = 0
    for i in range(0, iters):
        new_record = gen_dict_for_seg(record)
        t_start = time.process_time_ns()
        seg_search(new_record, key_end)
        t_result += time.process_time_ns() - t_start
    #t_result /= iters
    t_seg_end.append(t_result)


    t_result = 0
    for i in range(0, iters):
        t_start = time.process_time_ns()
        seq_search(record, key_none)
        t_result += time.process_time_ns() - t_start
    #t_result /= iters
    t_seq_none.append(t_result)

    t_result = 0
    for i in range(0, iters):
        list_keys = sorted(list(record.keys()))
        t_start = time.process_time_ns()
        bin_search_presort(record, key_none, list_keys)
        t_result += time.process_time_ns() - t_start
    #t_result /= iters
    t_bin_none.append(t_result)

    t_result = 0
    for i in range(0, iters):
        new_record = gen_dict_for_seg(record)
        t_start = time.process_time_ns()
        seg_search(new_record, key_none)
        t_result += time.process_time_ns() - t_start
    #t_result /= iters
    t_seg_none.append(t_result)

def print_latex(scale, res):
    for i in range(0, len(res)):
        res_str = str(scale[i])
        for elem in res[i]:
            res_str += ' & ' + str(int(elem))
        res_str += '\\\\'
        print(res_str)
    print()


scale = test_sizes
results_start = []

results_center = []

results_end = []

results_none = []

for i in range(0, len(scale)):
    results_start.append([t_seq_start[i], t_bin_start[i], t_seg_start[i]])

for i in range(0, len(scale)):
    results_center.append([t_seq_center[i], t_bin_center[i], t_seg_center[i]])

for i in range(0, len(scale)):
    results_end.append([t_seq_end[i], t_bin_end[i], t_seg_end[i]])

for i in range(0, len(scale)):
    results_none.append([t_seq_none[i], t_bin_none[i], t_seg_none[i]])

'''
print_latex(scale, results_start)
print()
print_latex(scale, results_center)
print()
print_latex(scale, results_end)
print()
print_latex(scale, results_none)
print()
'''

import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd


time_vals_start = []
time_vals_center = []
time_vals_end = []
time_vals_none = []

for elem in [t_seq_start, t_bin_start, t_seg_start]:
    time_vals_start.extend(elem)

for elem in [t_seq_center, t_bin_center, t_seg_center]:
    time_vals_center.extend(elem)

for elem in [t_seq_end, t_bin_end, t_seg_end]:
    time_vals_end.extend(elem)

for elem in [t_seq_none, t_bin_none, t_seg_none]:
    time_vals_none.extend(elem)

algos_start = []
algos_start.extend(['Полный перебор'] * len(scale))
algos_start.extend(['Бинарный'] * len(scale))
algos_start.extend(['Частичный анализ'] * len(scale))

length = scale * 3


df = pd.DataFrame()
df["Время"] = time_vals_start
df["Алгоритмы"] = algos_start
df["Кол-во элементов в словаре"] = length
 
#with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
#    print(df)

sns.lineplot(data=df, y='Время', x="Кол-во элементов в словаре", hue='Алгоритмы').set_title("Ключ в начале")
plt.show()

algos_center= []
algos_center.extend(['Полный перебор'] * len(scale))
algos_center.extend(['Бинарный'] * len(scale))
algos_center.extend(['Частичный анализ'] * len(scale))

length = scale * 3


df = pd.DataFrame()
df["Время"] = time_vals_center
df["Алгоритмы"] = algos_center
df["Кол-во элементов в словаре"] = length
 
#with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
#    print(df)

sns.lineplot(data=df, y='Время', x="Кол-во элементов в словаре", hue='Алгоритмы').set_title("Ключ в центре")
plt.show()

algos_end = []
algos_end.extend(['Полный перебор'] * len(scale))
algos_end.extend(['Бинарный'] * len(scale))
algos_end.extend(['Частичный анализ'] * len(scale))

length = scale * 3


df = pd.DataFrame()
df["Время"] = time_vals_end
df["Алгоритмы"] = algos_end
df["Кол-во элементов в словаре"] = length
 
#with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
#    print(df)

sns.lineplot(data=df, y='Время', x="Кол-во элементов в словаре", hue='Алгоритмы').set_title("Ключ в конце")
plt.show()

algos_none = []
algos_none.extend(['Полный перебор'] * len(scale))
algos_none.extend(['Бинарный'] * len(scale))
algos_none.extend(['Частичный анализ'] * len(scale))

length = scale * 3

print(time_vals_none)

df = pd.DataFrame()
df["Время"] = time_vals_none
df["Алгоритмы"] = algos_none
df["Кол-во элементов в словаре"] = length
 
#with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
#    print(df)

sns.lineplot(data=df, y='Время', x="Кол-во элементов в словаре", hue='Алгоритмы').set_title("Ключ не из словаря")
plt.show()