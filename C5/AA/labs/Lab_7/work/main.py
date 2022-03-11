from source_data_files import gen_data as gd
from algos import *
import random as rd
import time

size = int(input('Enter size for dictionary generation: '))

records = gd.generate_vals(size)

print(records)

key = input('Enter key for searching: ')

print('Results:')

res = ''
t_start = time.process_time_ns()
res = seq_search(records, key)
t_res = time.process_time_ns() - t_start
print('== Brute force ==')
print(' Result: ', res)
print(' Time: ', t_res)

list_keys = sorted(list(records.keys()))
t_start = time.process_time_ns()
res = bin_search_presort(records, key, list_keys)
t_res = time.process_time_ns() - t_start
print('== Binary search ==')
print(' Result: ', res)
print(' Time: ', t_res)

new_arr = gen_dict_for_seg(records)
t_start = time.process_time_ns()
res = seg_search(new_arr, key)
t_res = time.process_time_ns() - t_start
print('== Segment search ==')
print(' Result: ', res)
print(' Time: ', t_res)