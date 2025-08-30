import matplotlib.pyplot as plt

# Read data for all sorting algorithms
algorithms = ['merge', 'quick', 'insertion', 'selection', 'bubble']
colors = ['blue', 'red', 'green', 'orange', 'purple']
markers = ['o', 's', '^', 'D', 'v']

plt.figure(figsize=(12, 8))

for i, algo in enumerate(algorithms):
    n_values, time_values = [], []
    try:
        with open(f"{algo}.txt") as f:
            for line in f:
                n, t = line.split()
                n_values.append(int(n))
                time_values.append(float(t))
        
        plt.plot(n_values, time_values, marker=markers[i], 
                color=colors[i], label=f"{algo.capitalize()} Sort", linewidth=2)
    except FileNotFoundError:
        print(f"Warning: {algo}.txt not found")

plt.xlabel("Number of elements (n)")
plt.ylabel("Time taken (seconds)")
plt.title("Time Complexity Comparison: Sorting Algorithms")
plt.legend()
plt.grid(True, alpha=0.3)
plt.yscale('log')  # Log scale for better visualization

plt.tight_layout()
plt.savefig("sorting_comparison.png", dpi=300, bbox_inches='tight')
print("Plot saved as sorting_comparison.png")

