from test import *
from algos import * 
import time

iter = 50
len_list_lr = [1, 2, 3, 4, 5, 6, 7, 8, 9]
len_list = [100, 200, 300, 400, 500]

for strlen in len_list:
    lt_time = 0
    for i in range(0, iter):
        a = str_gen(strlen)
        b = str_gen(strlen)

        t_start = time.process_time()
        levenstain_table(a, b)
        lt_time += time.process_time() - t_start
    lt_time = lt_time / iter
    print("===")
    print("String len:", strlen)
    print('Leventsein table:', lt_time)
    print("===")

for strlen in len_list:
    lrm_time = 0
    for i in range(0, iter):
        a = str_gen(strlen)
        b = str_gen(strlen)

        mat_lrm = np.zeros([len(b) + 1, len(a) + 1]).astype(int)
        mat_lrm.fill(-1)

        t_start = time.process_time()
        levenstain_rec_matrix(a, b, len(b), len(a), mat_lrm)
        lrm_time += time.process_time() - t_start
    lrm_time = lrm_time / iter

    print("===")
    print("String len:", strlen)
    print('Leventsein recursive matrix:', lrm_time)
    print("===")

for strlen in len_list:
    dlt_time = 0
    for i in range(0, iter):
        a = str_gen(strlen)
        b = str_gen(strlen)

        t_start = time.process_time()
        damerau_levenstain_table(a, b)
        dlt_time += time.process_time() - t_start
    dlt_time = dlt_time / iter

    print("===")
    print("String len:", strlen)
    print('Damerau-Leventsein table:', dlt_time)
    print("===")

for strlen in len_list_lr:
    lr_time = 0
    for i in range(0, iter):
        a = str_gen(strlen)
        b = str_gen(strlen)

        t_start = time.process_time()
        levenstain_rec(a, b)
        lr_time += time.process_time() - t_start
    lr_time = lr_time / iter

    print("===")
    print("String len:", strlen)
    print('Leventsein recursive:', lr_time)
    print("===")
