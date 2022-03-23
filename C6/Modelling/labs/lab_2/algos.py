from typing import Callable
from numpy import e

c = 3 * (10**10)

def T(r: float, T_w: float, T_0: float, R: float, p: int) -> float:
    return (T_w - T_0) * ((r/R)**p) + T_0

def k(k_0: float, T):
    return k_0 * ((T/300)**2)

def u_p(T: float):
    return (3.084 * (10**(-4)))/(e**((4.709 * (10**(-4)))/T - 1))

k_0 = 0.0008
m = 0.786
R = 0.35 #sm
T_w = 2000 #K
T_0 = 10**4 #K

