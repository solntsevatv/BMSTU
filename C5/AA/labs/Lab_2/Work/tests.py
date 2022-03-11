from algos import *

def check_mat(mat_a, mat_b):
    res = True
    for i in range(0, len(mat_a)):
        for j in range(0, len(mat_a[0])):
            if mat_a[i][j] != mat_b[i][j]:
                res = False
    return res
        
def test_case(n, k, m, case_name):
    print(case_name)
    print('Параметры матрицы: ', n, k, m)
    a, b, res = matrix_gen(n, k, m)

    res_classic = classic_mat_mult(res.copy(), a, b, n, k, m)
    res_vinograd = res.copy()
    res_vinograd_opt = res.copy()

    print('Результат умножения: ')
    print_mat(a)
    print_mat(b)
    print_mat(res_classic)
    print_mat(res_vinograd)
    print_mat(res_vinograd_opt)

    print("Проверка совпадения результатов: ")
    print(check_mat(res_classic, res_vinograd) == check_mat(res_classic, res_vinograd_opt) == check_mat(res_vinograd_opt, res_vinograd))
    print('===\n')

def test_case_null(n, k, m, case_name):
    print(case_name)
    print('Параметры матрицы: ', n, k, m)
    a = [[0 for j in range(0, k)] for i in range(0, n)]
    b = [[rd.randint(-100, 100) for j in range(0, m)] for i in range(0, k)]
    res = [[0 for j in range(0, m)] for i in range(0, n)]

    res_classic = classic_mat_mult(res.copy(), a, b, n, k, m)
    res_vinograd = res.copy()
    res_vinograd_opt = res.copy()

    print('Результат умножения: ')
    print_mat(a)
    print_mat(b)
    print_mat(res_classic)
    print_mat(res_vinograd)
    print_mat(res_vinograd_opt)

    print("Проверка совпадения результатов: ")
    print(check_mat(res_classic, res_vinograd) == check_mat(res_classic, res_vinograd_opt) == check_mat(res_vinograd_opt, res_vinograd))
    print('===\n')

def test_case_ones(n, k, m, case_name):
    print(case_name)
    print('Параметры матрицы: ', n, k, m)
    a = [[rd.randint(-100, 100) for j in range(0, k)] for i in range(0, n)]
    b = [[0 for j in range(0, m)] for i in range(0, k)]
    for i in range(0, len(b)):
        b[i][i] = 1
    res = [[0 for j in range(0, m)] for i in range(0, n)]

    res_classic = classic_mat_mult(res.copy(), a, b, n, k, m)
    res_vinograd = res.copy()
    res_vinograd_opt = res.copy()

    print('Результат умножения: ')
    print_mat(a)
    print_mat(b)
    print_mat(res_classic)
    print_mat(res_vinograd)
    print_mat(res_vinograd_opt)

    print("Проверка совпадения результатов: ")
    print(check_mat(res_classic, res_vinograd) == check_mat(res_classic, res_vinograd_opt) == check_mat(res_vinograd_opt, res_vinograd))
    print('===\n')     


test_case(3, 3, 4, 'Обычные матрицы')
test_case(1, 3, 4, 'Проверка на векторах')
test_case(4, 3, 1, 'Проверка на векторах')
test_case_null(3, 3, 4, 'Проверка нулевой матрицы')
test_case_ones(3, 3, 4, 'Проверка единичной матрицы')