from typing import Callable
from numpy import e
from math import isnan
from cmath import exp, inf, nan
import seaborn as sns
import matplotlib.pyplot as plt

c = 3 * 10e+10
k_0 = 0.0008
m = 0.786
R = 0.35 #m
T_w = 2000 #K
T_0 = 10000 #K
p = 4 # от 4 до 15

def T(Z: float) -> float:
    return (T_w - T_0) * ((Z)**p) + T_0

def k(Z: float) -> float:
    return k_0 * ((T(Z)/300)**2)

def u_p(Z: float):
    return (3.084e-4)/(e**(4.709e+4/T(Z)) - 1)

def F_z(Z: float, F: Callable, u: float) -> float: # F_z(u)
    if Z == 0:
        return ((c * R)/2) * k(Z) * (u_p(Z) - u)
    else:
        return c * R * k(Z) * (u_p(Z) - u) - (F / Z)

def u_z(Z: float, F: float): # u_z(F)
    return -(3 * R * F * k(Z)) / c

def runge_kutt_4(h_0: float, z_0: float, f_0: float, u_0: float, z_max: float, F: Callable, Phi: Callable):
    z_n = z_0
    h = h_0

    u_n = u_0
    f_n = f_0

    z_res = [z_0]
    u_res = [u_0]
    f_res = [f_0]

    while z_n < z_max:
        q_1 = h * Phi(z_n, f_n)
        k_1 = h * F(z_n, f_n, u_n)

        q_2 = h * Phi(z_n + h / 2, f_n + k_1 / 2)
        k_2 = h * F(z_n + h / 2, f_n + k_1 / 2, u_n + q_1 / 2)

        q_3 = h * Phi(z_n + h / 2, f_n + k_2 / 2)
        k_3 = h * F(z_n + h / 2, f_n + k_2 / 2, u_n + q_2 / 2)

        q_4 = h * Phi(z_n + h, f_n + k_3)
        k_4 = h * F(z_n + h, f_n + k_3, u_n + q_3)

        u_n = u_n + (q_1 + 2 * q_2 + 2 * q_3 + q_4) / 6
        f_n = f_n + (k_1 + 2 * k_2 + 2 * k_3 + k_4) / 6
        z_n += h

        #if abs(u_n) == inf or isnan(u_n):
        #    break
        #if abs(f_n) == inf or isnan(f_n):
        #    break
        z_res.append(z_n)
        u_res.append(u_n)
        f_res.append(f_n)
    return z_res, u_res, f_res

if __name__ == '__main__':
    # Z_0 = 0, F(0) = 0
    xi = 0.036
    z_res, u_res, f_res = runge_kutt_4(0.01, 0, 0, xi * u_p(0), 1, F_z, u_z)

    import graph as gh
    print(z_res)
    print(u_res)
    print(f_res)
    x_list = []
    y_list = []
    algos = []

    fig, axs = plt.subplots(ncols=2)
    sns.lineplot(x=z_res, y=u_res, hue=['u(z)'] * len(u_res), ax=axs[0])
    sns.lineplot(x=z_res, y=f_res, hue=['F(z)'] * len(f_res), ax=axs[1])
    plt.show()
    #x_list.extend(z_res)
    #y_list.extend(u_res)
    #algos.extend(['u(z)'] * len(u_res))

    #x_list.extend(z_res)
    #y_list.extend(f_res)
    #algos.extend(['F(z)'] * len(f_res))

    #gh.plot_results(x_list, y_list, algos)