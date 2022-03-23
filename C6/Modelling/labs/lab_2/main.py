from algos import *
from cProfile import run
from cmath import inf, nan
from logging import exception
import table as tb
import graph as gh
from math import isnan
from typing import Any, Callable
import pandas as pd

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

        #x_max_euler, x_max_runge = 2, 2

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