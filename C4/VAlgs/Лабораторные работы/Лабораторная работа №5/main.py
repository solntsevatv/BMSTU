from typing import List, Callable as func
from math import exp, sin, cos, pi
import numpy as np
from numpy import linspace, array
from numpy.linalg import solve
from matplotlib import pyplot as plt
from math import cos, pi

def leg_polym(n, x):
    if n < 2: return [1, x][n]
    P1, P2 = leg_polym(n - 1, x), leg_polym(n - 2, x)
    return ((2 * n - 1) * x * P1 - (n - 1) * P2) / n

def leg_polym_proz(n, x):
    P1, P2 = leg_polym(n - 1, x), leg_polym(n, x)
    return n / (1 - x * x) * (P1 - x * P2)

def leg_roots(n: int, eps: float = 1e-12) -> List[float]:
    roots = [cos(pi * (4 * i + 3) / (4 * n + 2)) for i in range(n)]
    for i, root in enumerate(roots):
        root_val = leg_polym(n, root)
        while abs(root_val) > eps:
            root -= root_val / leg_polym_proz(n, root)
            root_val = leg_polym(n, root)
        roots[i] = root
    return roots

def norm_gauss_integ(f, n):
    t = leg_roots(n)
    T = array([[t_i**k for t_i in t] for k in range(n)])
    int_tk = lambda k: 2 / (k + 1) if k % 2 == 0 else 0
    b = array([int_tk(k) for k in range(n)])
    A = solve(T, b)
    return sum(A_i * f(t_i) for A_i, t_i in zip(A, t))

def gauss_integ(f, a, b, n):
    mean, diff = (a + b) / 2, (b - a) / 2
    g = lambda t: f(mean + diff * t)
    return diff * norm_gauss_integ(g, n)

def simp_integ(f, a, b, n):
    h, res = (b - a) / n, 0
    for i in range(0, n, 2):
        x1, x2, x3 = i * h, (i + 1) * h, (i + 2) * h
        f1, f2, f3 = f(x1), f(x2), f(x3)
        res += f1 + 4 * f2 + f3
    return h / 3 * res

def compose_integ(f, a1, b1, a2, b2, method_1, method_2, n1, n2):
    F = lambda y: method_1(lambda x: f(x, y), a1, b1, n1)
    return method_2(F, a2, b2, n2)

def function_integ(f, a, b, c, d, n, m):
    return compose_integ(f, a, b, c, d, gauss_integ, simp_integ, n, m)

def function(t, n, m):
    L_R = lambda theta, phi: 2 * cos(theta) / (1 - sin(theta)**2 * cos(phi)**2)
    f = lambda theta, phi: (1 - exp(-t * L_R(theta, phi))) * cos(theta) * sin(theta)
    return 4 / pi * function_integ(f, 0, pi / 2, 0, pi / 2, n, m)

tao = linspace(0.05, 10, 100)
eps = [function(t, 3, 4) for t in tao]

plt.plot(tao, eps)
plt.grid()
plt.show()
