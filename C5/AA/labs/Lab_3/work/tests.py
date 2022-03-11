from algos import *

def check_arr(arr_a, arr_b):
    res = True
    l = len(arr_a)
    for i in range(0, l):
        if arr_a[i] != arr_b[i]:
            res = False
    return res
        
def test_case(arr_a, arr_true, case_name):
    print(case_name)
    print('Параметры массива: N = ', len(arr_a))

    res_bubble = bubble_sort(arr_a)
    res_comb = comb_sort(arr_a)
    res_insert = insert_sort(arr_a)

    print('Результат сортировки: ')
    print(arr_a)
    print(res_bubble)
    print(res_comb)
    print(res_insert)

    print("Проверка совпадения результатов: ")
    print(check_arr(arr_true, res_bubble))
    print(check_arr(arr_true, res_comb))
    print(check_arr(arr_true, res_insert))
    print('===\n')

arr_a = generate_random_test_array(5)
arr_true = arr_a.copy()
arr_true.sort()
test_case([], [], 'Нулевой массив')
test_case(arr_a, arr_true, 'Общий случай')