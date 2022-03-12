from cProfile import run
from cmath import inf, nan
from logging import exception
import table as tb
import graph as gh
from math import isnan
from typing import Any, Callable
import pandas as pd

# Function du/dx f(x, u)
def f(x: float, u: float) -> float:
    return x*x  + u*u

# Euler explicit
def euler_explicit(h: float, y_0: float, x_0: float, x_max: float) -> tuple[list[int], list[int]]:
    y_res = [0]
    x_res = [0]
    
    x = x_0
    y = y_0

    while abs(x) <= abs(x_max):
        y += h * f(x, y)
        x += h
        if abs(y) == inf or isnan(y):
            break
        y_res.append(y)
        x_res.append(x)

    return x_res, y_res
            
# Runge-Cutt p = 2
def runge_cutt(a: float, h: float, y_0: float, x_0: float, x_max: float) -> tuple[list[int], list[int]]:
    y_res = [0]
    x_res = [0]
    
    x = x_0
    y = y_0

    while abs(x) <= abs(x_max):
        y += h * ((1 - a) * f(x, y) + a * f(x + h/(2 * a), y + h * f(x, y) / (a * 2)))
        x += h
        if abs(y) == inf or isnan(y):
            break
        y_res.append(y)
        x_res.append(x)

    return x_res, y_res

# Pikar 1
def f_p_1(x: float) -> float:
    return (x ** 3) / 3

# Pikar 2
def f_p_2(x: float) -> float:
    return (x ** 3) / 3 + (x ** 7) / 63

# Pikar 3
def f_p_3(x: float) -> float:
    return (x ** 3) / 3 + (x ** 7) / 63 + 2 * (x ** 11) / 2079 + (x ** 15) / 59535

# Pikar 4
def f_p_4(x: float) -> float:
    return (x ** 3) / 3 + (x ** 7) / 63 + 2 * (x ** 11) / 59535 + (x ** 15) / 93555 + 2 * (x ** 19) / 3393495 + \
     2 * (x ** 19) / 2488563 + 2 * (x ** 23) / 86266215 + (x ** 23) / 99411543 + 2 * (x ** 27) / 3341878155 + \
     (x ** 31) / 109876902975

def pikar(h: float, x_0: float, x_max: float, func: Callable[[float], float]):
    x = x_0
    res_x = [0]
    res_y = [0]
    while abs(x) <= abs(x_max):
        res_y.append(func(x))
        res_x.append(x)
        x += h
    return res_x, res_y

# Runge rule accuracy
# p = 1 - Euler
# p = 4 - Runge-Cutt fourth order of accuracy
def runge_accuracy(p: int, y_i: float, y_i_2: float):
    return abs(y_i - y_i_2)/(2 ** p - 1)

def find_x_max_euler(p: int, h: float, y_0: float, x_0: float, accuracy: float) -> tuple[float, float]:
    x_max = 0
    error = 0
    error_old = 0
    while error < accuracy:
        x_max += h
        error_old = error
        _, res_y_h = euler_explicit(h, y_0, x_0, x_max)
        _, res_y_h_2 = euler_explicit(h/2, y_0, x_0, x_max)
        error = runge_accuracy(p, res_y_h[-1], res_y_h_2[-1])

    return x_max, error_old

def find_x_max_runge_cutt(a: float, p: int, h: float, y_0: float, x_0: float, accuracy: float) -> tuple[float, float]:
    x_max = 0
    error = 0
    error_old = 0
    while error < accuracy:
        x_max += h
        error_old = error
        _, res_y_h = runge_cutt(a, h, y_0, x_0, x_max)
        _, res_y_h_2 = runge_cutt(a, h/2, y_0, x_0, x_max)
        error = runge_accuracy(p, res_y_h[-1], res_y_h_2[-1])

    return x_max, error_old

def count_euler(h: float, x_0: float, y_0: float, x_max: float) -> tuple[float, float]: #p: float, accuracy: float):
    x_r, y_r = euler_explicit(h, y_0, x_0, x_max)
    x_l, y_l = euler_explicit(-h, y_0, x_0, -x_max)
    x_l.reverse()
    y_l.reverse()

    x = x_l.copy()
    y = y_l.copy()
    x.extend(x_r[1:])
    y.extend(y_r[1:])

    return x, y

def count_runge_cutt(a: float, h: float, x_0: float, y_0: float, x_max: float) -> tuple[float, float]: # p: float, accuracy: float):
    x_r, y_r = runge_cutt(a, h, y_0, x_0, x_max)
    x_l, y_l = runge_cutt(a, -h, y_0, x_0, -x_max)
    x_l.reverse()
    y_l.reverse()

    x = x_l.copy()
    y = y_l.copy()
    x.extend(x_r[1:])
    y.extend(y_r[1:])

    return x, y

def count_pikar(h: float, x_0: float, x_max: float, func: Callable[[float], float]) -> tuple[float, float]:
    x_r, y_r = pikar(h, x_0, x_max, func)
    x_l, y_l = pikar(-h, x_0, -x_max, func)
    x_l.reverse()
    y_l.reverse()

    x = x_l.copy()
    y = y_l.copy()
    x.extend(x_r[1:])
    y.extend(y_r[1:])

    return x, y

if __name__ == '__main__':
    user_input = -1
    while user_input != 0:
        user_input = int(input('Выберите действие:\nВыйти (0)\nРассчитать значения (1)\n> '))
        if user_input == 1:
            a = float(input('Введите значение коэффициента a:\n> '))
            h = float(input('Введите значение шага h:\n> '))
            #a = 1
            #h = 0.1
            accuracy = 0.01
            #x_max = 2 #сходится к двойке, выявлено эмпирически
            x_0 = 0
            y_0 = 0

            x_max_euler, _ = find_x_max_euler(1, h, y_0, x_0, accuracy)
            x_max_runge, _ = find_x_max_runge_cutt(a, 2, h, y_0, x_0, accuracy)
            x_max = max(x_max_euler, x_max_runge)

            x_euler, y_euler = count_euler(h, x_0, y_0, x_max_euler)    
            x_runge_cutt, y_runge_cutt = count_runge_cutt(a, h, x_0, y_0, x_max_runge)
            x_pikar_1, y_pikar_1 = count_pikar(h, x_0, x_max, f_p_1)
            x_pikar_2, y_pikar_2 = count_pikar(h, x_0, x_max, f_p_2)
            x_pikar_3, y_pikar_3 = count_pikar(h, x_0, x_max, f_p_3)
            x_pikar_4, y_pikar_4 = count_pikar(h, x_0, x_max, f_p_4)

            i = 0
            while abs(y_pikar_1[i] - y_pikar_2[i]) > accuracy and i < int(len(y_pikar_1)/2):
                i += 1
            y_pikar_1 = y_pikar_1[i:int(len(y_pikar_1) - i)]
            x_pikar_1 = x_pikar_1[i:int(len(x_pikar_1) - i)]
            
            i = 0
            while abs(y_pikar_2[i] - y_pikar_3[i]) > accuracy and i < int(len(y_pikar_2)/2):
                i += 1
            y_pikar_2 = y_pikar_2[i:int(len(y_pikar_2) - i)]
            x_pikar_2 = x_pikar_2[i:int(len(x_pikar_2) - i)]

            i = 0
            while abs(y_pikar_3[i] - y_pikar_4[i]) > accuracy and i < int(len(y_pikar_3)/2):
                i += 1
            y_pikar_3 = y_pikar_3[i:int(len(y_pikar_3) - i)]
            x_pikar_3 = x_pikar_3[i:int(len(x_pikar_3) - i)]

            print('Количество шагов для каждого из методов:')
            print('Эйлер: ', len(y_euler))
            print('Рунге-Кутт: ', len(y_runge_cutt))
            print('Пикар, p=1', len(y_pikar_1))
            print('Пикар, p=2', len(y_pikar_2))
            print('Пикар, p=3', len(y_pikar_3))
            print('Пикар, p=4', len(y_pikar_4))
            print()
            
            algos = ['Эйлер'] * len(x_euler)
            algos.extend(['Рунге-Кутт'] * len(x_runge_cutt))
            algos.extend(['Пикар, p=1'] * len(x_pikar_1))
            algos.extend(['Пикар, p=2'] * len(x_pikar_2))
            algos.extend(['Пикар, p=3'] * len(x_pikar_3))
            algos.extend(['Пикар, p=4'] * len(x_pikar_4))
            
            df = pd.DataFrame()
            pd.options.display.expand_frame_repr = False
            df["x"] = x_euler[int(len(x_euler)/2):]
            df["Эйлер"] = y_euler[int(len(x_euler)/2):]
            y_runge_cutt_table = y_runge_cutt.copy()
            y_runge_cutt_table = y_runge_cutt_table[int(len(y_runge_cutt_table)/2):]
            while len(y_runge_cutt_table) < len(y_euler[int(len(x_euler)/2):]):
                y_runge_cutt_table.append('-')

            y_pikar_1_table = y_pikar_1.copy()
            y_pikar_1_table = y_pikar_1_table[int(len(y_pikar_1_table)/2):]
            while len(y_pikar_1_table) < len(y_euler[int(len(x_euler)/2):]):
                y_pikar_1_table.append('-')

            y_pikar_2_table = y_pikar_2.copy()
            y_pikar_2_table = y_pikar_2_table[int(len(y_pikar_2_table)/2):]
            while len(y_pikar_2_table) < len(y_euler[int(len(x_euler)/2):]):
                y_pikar_2_table.append('-')

            y_pikar_3_table = y_pikar_3.copy()
            y_pikar_3_table = y_pikar_3_table[int(len(y_pikar_3_table)/2):]
            while len(y_pikar_3_table) < len(y_euler[int(len(x_euler)/2):]):
                y_pikar_3_table.append('-')

            y_pikar_4_table = y_pikar_4.copy()
            y_pikar_4_table = y_pikar_4_table[int(len(y_pikar_4_table)/2):]
            while len(y_pikar_4_table) < len(y_euler[int(len(x_euler)/2):]):
                y_pikar_4_table.append('-')

            df["Рунге-Кутт"] = y_runge_cutt_table
            df["Пикар, p=1"] = y_pikar_1_table
            df["Пикар, p=2"] = y_pikar_2_table
            df["Пикар, p=3"] = y_pikar_3_table
            df["Пикар, p=4"] = y_pikar_4_table

            with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
                print(df)
            
            x = []
            x.extend(x_euler)
            x.extend(x_runge_cutt)
            x.extend(x_pikar_1)
            x.extend(x_pikar_2)
            x.extend(x_pikar_3)
            x.extend(x_pikar_4)
            y = []
            y.extend(y_euler)
            y.extend(y_runge_cutt)
            y.extend(y_pikar_1)
            y.extend(y_pikar_2)
            y.extend(y_pikar_3)
            y.extend(y_pikar_4)

            gh.plot_results(x, y, algos)

#tb.print_table(['x', 'y'], res_arr)
#gh.plot_results(x, y, algos=['Эйлер']*len(x))