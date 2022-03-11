from datetime import time
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

time_vals = [0.0040625, 0.01625, 0.0353125, 0.06875, 0.115625, 0.03375, 0.114375, 0.2653125, 0.4675, 0.7459375, 0.01625, 0.064375, 0.14875, 0.271875, 0.45]
algos = ['lev_table', 'lev_table', 'lev_table', 'lev_table', 'lev_table', 'lev_rec_mat', 'lev_rec_mat', 'lev_rec_mat', 'lev_rec_mat', 'lev_rec_mat', 'dam_lev', 'dam_lev', 'dam_lev', 'dam_lev', 'dam_lev']
length = [100, 200, 300, 400, 500, 100, 200, 300, 400, 500, 100, 200, 300, 400, 500]

df = pd.DataFrame()
df["time"] = time_vals
df["algos"] = algos
df["length"] = length
 
sns.lineplot(data=df, y='time', x='length', hue='algos')
plt.show()

'''
time_vals = [0, 0, 0, 0.0003125, 0.0009375, 0.005625, 0.0303125, 0.16625, 0.89375]
length = [1, 2, 3, 4, 5, 6, 7, 8, 9]

df = pd.DataFrame()
df["time"] = time_vals
df["length"] = length
 
sns.lineplot(data=df, y='time', x='length')
plt.show()
'''