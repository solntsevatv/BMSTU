import time
from source_data_files import gen_data as gd
from algos import *

size = 5000000

record = gd.generate_vals(size)

keys = list(record)
key_start = keys[0]
key_end = keys[-1]

list_keys = sorted(list(record.keys()))
t_start = time.process_time_ns()
#bin_search_presort(record, key_start, list_keys)
print(time.process_time_ns())
seq_search(record, key_end)
print(time.process_time_ns())
t_result = time.process_time_ns() - t_start
print(t_start)
print(t_result)