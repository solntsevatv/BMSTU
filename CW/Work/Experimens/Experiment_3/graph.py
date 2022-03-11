scale = [1, 2, 3, 4, 5, 6, 7, 8]
results = [
[4999500,
4998700,
4999500,
4999500,
4968300],
[5994300,
6960600,
5999600,
6002200,
6036300],
[8000400,
8963400,
7998200,
9000000,
8002200],
[10998700,
11999300,
10998900,
10999000,
10999500],
[14999400,
14965600,
14999900,
15962700,
14997300],
[20004500,
19997000,
18997700,
18999700,
19036500],
[23999200,
24035500,
24000100,
23973100,
24030800],
[29999400,
30000400,
31025900,
30000200,
30000200]
]

#print_latex(scale, results)

import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
    
time_vals = []

for res in results:
    avg = 0
    for subres in res:
        avg += subres
    avg /= 5
    time_vals.append(avg)

length = ['0.5%', '2.0%', '4.5%', '8.0%', '12.5%', '18.0%', '24.5%', '32.0%']


print(scale)
print(time_vals)

df = pd.DataFrame()
df["Время отрисовки"] = time_vals
df["Размер полигона относительно размера экрана"] = length
 
#with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
#    print(df)

sns.lineplot(data=df, y='Время отрисовки', x="Размер полигона относительно размера экрана")
plt.show()