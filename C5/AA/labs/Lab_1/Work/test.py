from algos import *

import string
import random
import numpy as np

def str_gen(str_len):
    src_str = string.ascii_lowercase
    return ''.join(random.choice(src_str) for i in range(str_len))


def test_empty():
    a = ''
    b = ''
    mat_lrm = np.zeros([len(b) + 1, len(a) + 1]).astype(int)
    mat_lrm.fill(-1)
    return levenstain_table(a, b) == 0 and levenstain_rec(a, b) == 0\
         and levenstain_rec_matrix(a, b, len(b), len(a), mat_lrm) == 0 and\
              damerau_levenstain_table(a, b) == 0

def test_first(test_len):
    a = ''
    b = str_gen(test_len)
    mat_lrm = np.zeros([len(b) + 1, len(a) + 1]).astype(int)
    mat_lrm.fill(-1)
    return levenstain_table(a, b) == len(b) and levenstain_rec(a, b) == len(b)\
         and levenstain_rec_matrix(a, b, len(b), len(a), mat_lrm) == len(b) and\
              damerau_levenstain_table(a, b) == len(b)

def test_second(test_len):
    a = str_gen(test_len)
    b = ''
    mat_lrm = np.zeros([len(b) + 1, len(a) + 1]).astype(int)
    mat_lrm.fill(-1)
    return levenstain_table(a, b) == len(a) and levenstain_rec(a, b) == len(a)\
         and levenstain_rec_matrix(a, b, len(b), len(a), mat_lrm) == len(a) and\
              damerau_levenstain_table(a, b) == len(a)

def test_equal(test_len):
    a = str_gen(test_len)
    b = a
    mat_lrm = np.zeros([len(b) + 1, len(a) + 1]).astype(int)
    mat_lrm.fill(-1)
    return levenstain_table(a, b) == 0 and levenstain_rec(a, b) == 0\
         and levenstain_rec_matrix(a, b, len(b), len(a), mat_lrm) == 0 and\
              damerau_levenstain_table(a, b) == 0

def test_diff(test_len, diff_len):
    a = str_gen(test_len)
    b = str_gen(test_len + diff_len)
    mat_lrm = np.zeros([len(b) + 1, len(a) + 1]).astype(int)
    mat_lrm.fill(-1)
    return levenstain_table(a, b) == levenstain_rec(a, b) == \
        levenstain_rec_matrix(a, b, len(b), len(a), mat_lrm) == damerau_levenstain_table(a, b)

if __name__ == "__main__":
    n = int(input('Enter test string length: '))
    n_diff = int(input('Enter second test string length: '))
    print('Test empty:', test_empty())
    print('Test first:', test_first(n))
    print('Test second:', test_second(n))
    print('Test equal:', test_equal(n))
    print('Test different:', test_diff(n, n_diff))