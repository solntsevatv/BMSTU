scale = [20, 40, 80, 160, 320, 720, 1280]
results = [
[99968300,
88567200,
81991800,
92933100,
38998400],
[89637300,
67028300,
88039500,
46998600,
91060600],
[47000100,
48998900,
138047500,
75996800,
50955700],
[66994700,
91992700,
43998800,
74998300,
42996900],
[107035400,
44999700,
62003300,
45999100,
45998500],
[48997000,
49999600,
49998700,
61999100,
50998000],
[55047400,
40992800,
47998900,
47999900,
50000700]
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

length = [20, 40, 80, 160, 320, 720, 1280]


print(scale)
print(time_vals)

df = pd.DataFrame()
df["Время"] = time_vals
df["Кол-во полигонов в модели"] = length
 
#with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
#    print(df)

sns.lineplot(data=df, y='Время', x="Кол-во полигонов в модели")
plt.show()