import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

def plot_results(x_list: list[float], y_list: list[float], algos: list[str]) -> None:
    df = pd.DataFrame()
    df["x"] = x_list
    df["y"] = y_list
    df["алгоритмы"] = algos

    #with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
    #    print(df)

    sns.lineplot(data=df, y='y', x="x", hue='алгоритмы')
    plt.show()