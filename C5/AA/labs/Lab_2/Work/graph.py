import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

test_sizes = [10, 25, 50, 75, 100, 125, 150]

t_class = [0.0, 0.0, 0.015625, 0.078125, 0.15625, 0.328125, 0.515625]
t_vin = [0.0, 0.0, 0.015625, 0.0625, 0.171875, 0.375, 0.609375]
t_vin_opt = [0.0, 0.015625, 0.015625, 0.0625, 0.125, 0.234375, 0.375]

time_vals = []
time_vals.extend(t_class)
time_vals.extend(t_vin)
time_vals.extend(t_vin_opt)

algos = []
algos.extend(['Классический'] * len(t_class))
algos.extend(['Виноградова'] * len(t_vin))
algos.extend(['Виноградова с оптимизацией'] * len(t_vin_opt))

length = test_sizes * 3

df = pd.DataFrame()
df["time"] = time_vals
df["algos"] = algos
df["length"] = length
 
sns.lineplot(data=df, y='time', x='length', hue='algos')
plt.show()
'''
time_vals = []
time_vals.extend(t_vin)
time_vals.extend(t_vin_opt)

algos = []
algos.extend(['Виноградова'] * len(t_vin))
algos.extend(['Виноградова с оптимизацией'] * len(t_vin_opt))

length = test_sizes * 2

df = pd.DataFrame()
df["time"] = time_vals
df["algos"] = algos
df["length"] = length
 
sns.lineplot(data=df, y='time', x='length', hue='algos')
plt.show()
'''