import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.csv")

for category in df['array_type'].unique():
    subset = df[df['array_type'] == category]
    subset = subset.sort_values('size')

    merge_data = subset[subset['algorithm'] == 'merge']
    hybrid_data = subset[subset['algorithm'] == 'hybrid']

    plt.figure(figsize=(12, 7), dpi=150) 
    plt.plot(merge_data['size'], merge_data['time_ms'], label='Merge Sort', marker='o')
    plt.plot(hybrid_data['size'], hybrid_data['time_ms'], label='Hybrid Sort', marker='o')

    plt.title(f'Время сортировки vs размер массива ({category})')
    plt.xlabel('Размер массива')
    plt.ylabel('Время (мс)')
    plt.legend()
    plt.grid(True)

    plt.savefig(f"{category}_sort.png")
    plt.show()

