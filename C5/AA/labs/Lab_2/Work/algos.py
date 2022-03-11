import random as rd
import time

def matrix_gen(n, k, m):
    a = [[rd.randint(-100, 100) for j in range(0, k)] for i in range(0, n)]
    b = [[rd.randint(-100, 100) for j in range(0, m)] for i in range(0, k)]
    res = [[0 for j in range(0, m)] for i in range(0, n)]
    return a, b, res

def matrix_gen_val(n, k, m, val):
    a = [[val for j in range(0, k)] for i in range(0, n)]
    b = [[val for j in range(0, m)] for i in range(0, k)]
    res = [[0 for j in range(0, m)] for i in range(0, n)]
    return a, b, res

def print_mat(mat):
    for row in mat:
        print(row)
    print()

def classic_mat_mult(result, mat_a, mat_b, n, k, m):
    i = 0
    while i < n:
        j = 0
        while j < m:
            l = 0
            while l < k:
                result[i][j] += mat_a[i][l] * mat_b[l][j]
                l += 1
            j += 1
        i += 1
    return result

def vinograd_mat_mult(result, mat_a, mat_b, n, k, m):
    row_vec = [0] * n
    col_vec = [0] * m
    
    i = 0
    while i < n:
        j = 0
        while j < k // 2:
            row_vec[i] = row_vec[i] + mat_a[i][j * 2] * mat_a[i][j * 2 + 1]
            j += 1
        i += 1

    i = 0
    while i < m:
        j = 0
        while j < k // 2:
            col_vec[i] = col_vec[i] + mat_b[j * 2][i] * mat_b[j * 2 + 1][i]
            j += 1
        i += 1

    i = 0
    while i < n:
        j = 0
        while j < m:
            result[i][j] = -row_vec[i] - col_vec[j]
            l = 0
            while l < k // 2:
                result[i][j] = result[i][j] + (mat_a[i][2 * l + 1] + mat_b[2 * l][j]) *\
                    (mat_a[i][2 * l] + mat_b[2 * l + 1][j])
                l += 1
            j += 1
        i += 1
        
    if k % 2 == 1:
        i = 0
        while i < n:
            j = 0
            while j < m:
                result[i][j] = result[i][j] + mat_a[i][k - 1] * mat_b[k - 1][j]
                j += 1
            i += 1
            
    return result

def vinograd_mat_optimized(result, mat_a, mat_b, n, k, m):
    row_vec = [0] * n
    col_vec = [0] * m
    k_mod = k - k % 2
    i = 0
    while i < n:
        j = 0
        while j < k_mod:
            row_vec[i] += mat_a[i][j] * mat_a[i][j + 1]
            j += 2
        i += 1
        
    i = 0
    while i < m:
        j = 0
        while j < k_mod:
            col_vec[i] += mat_b[j][i] * mat_b[j + 1][i]
            j += 2
        i += 1
        
    i = 0
    temp = 0
    while i < n:
        j = 0
        while j < m:
            # optimization temp buffer
            temp = -row_vec[i] - col_vec[j]
            l = 0
            while l < k_mod:
                temp += (mat_a[i][l + 1] + mat_b[l][j]) *\
                    (mat_a[i][l] + mat_b[l + 1][j])
                l += 2
            result[i][j] = temp
            j += 1
        i += 1
        
    if k % 2 == 1:
        i = 0
        k_min = k - 1
        while i < n:
            j = 0
            while j < m:
                result[i][j] += mat_a[i][k_min] * mat_b[k_min][j]
                j += 1
            i += 1
    return result