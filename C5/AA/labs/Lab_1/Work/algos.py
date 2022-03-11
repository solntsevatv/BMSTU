import numpy as np

def levenstain_table(a, b):
    n, m = len(a), len(b)
    cash_str_1 = [*range(n + 1)]
    cash_str_2 = [*range(n + 1)]

    for i in range(1, m + 1):
        cash_str_2 = cash_str_1
        cash_str_1 = [i] + [0] * n
        for j in range(1, n + 1):
            I = cash_str_2[j] + 1
            D = cash_str_1[j - 1] + 1
            R = cash_str_2[j - 1]
            if a[j - 1] != b[i - 1]:
                R += 1
            cash_str_1[j] = min(I, D, R)
    return cash_str_1[n]

def levenstain_rec(a, b):
    result = 0
    if len(a) == 0 and len(b) == 0:
        result = 0
    elif len(a) == 0 and len(b) != 0:
        result = len(b)
    elif len(b) == 0 and len(a) != 0:
        result = len(a)
    else:
        result = min(
            levenstain_rec(a, b[1:]) + 1,
            levenstain_rec(a[1:], b) + 1,
            levenstain_rec(a[1:], b[1:]) + (a[0] != b[0])
        )
    return result

def levenstain_rec_matrix(a, b, i, j, mat):
    result = 0
    if len(a) == 0 and len(b) == 0:
        result = 0
    elif i == 0:
        mat[i][j] = j
        result = j
    elif j == 0:
        mat[i][j] = i
        result = i
    else:
        R = 1
        if a[j - 1] == b[i - 1]:
            R = 0

        if mat[i][j] == -1:
            mat[i][j] = min(
                levenstain_rec_matrix(a, b, i - 1, j - 1, mat) + R, # R
                levenstain_rec_matrix(a, b, i - 1, j, mat) + 1, # D
                levenstain_rec_matrix(a, b, i, j - 1, mat) + 1 # I
                )
        result = int(mat[i][j])
    return result

def damerau_levenstain_table(a, b):
    n = len(a) + 1
    m = len(b) + 1
    mat = np.zeros([n, m]).astype(int)
    
    for i in range(0, n):
        mat[i, 0] = i
    for i in range(0, m):
        mat[0, i] = i

    for i in range(1, n):
        for j in range(1, m):
            R = 0
            if a[i - 1] != b[j - 1]:
                R = 1
            mat[i][j] = min(
                mat[i][j - 1] + 1, # I
                mat[i - 1][j] + 1, # D
                mat[i - 1][j - 1] + R # R
            )
            if (i > 1 and j > 1) and a[i - 1] == b[j - 2] and a[i - 2] == b[j - 1]:
                mat[i][j] = min(mat[i][j], mat[i - 2][j - 2] + R) # T
    return mat[n - 1][m - 1]