
import matplotlib.pyplot as plt
import numpy as np

algorithms = ['recursive', 'iterative', 'top_down', 'bottom_up']
colors = ['red', 'blue', 'green', 'orange']
markers = ['o', 's', '^', 'D']
labels = ['Recursive O(2^n)', 'Iterative O(n)', 'Top-Down DP O(n)', 'Bottom-Up DP O(n)']

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))

# Time complexity plots
for i, algo in enumerate(algorithms):
    n_values, time_values = [], []
    try:
        with open(f"{algo}.txt") as f:
            for line in f:
                n, t = line.split()
                n_values.append(int(n))
                time_values.append(float(t))
        ax1.plot(n_values, time_values, marker=markers[i],
                 color=colors[i], label=labels[i], linewidth=2, markersize=6)
    except FileNotFoundError:
        print(f"[!] Missing {algo}.txt")

ax1.set_xlabel("n")
ax1.set_ylabel("Time (s)")
ax1.set_title("All Fibonacci Algorithms")
ax1.legend()
ax1.set_yscale('log')
ax1.grid(True, alpha=0.3)

efficient_algos = ['iterative', 'top_down', 'bottom_up']
efficient_colors = ['blue', 'green', 'orange']
efficient_markers = ['s', '^', 'D']
efficient_labels = ['Iterative O(n)', 'Top-Down DP O(n)', 'Bottom-Up DP O(n)']

for i, algo in enumerate(efficient_algos):
    n_values, time_values = [], []
    with open(f"{algo}.txt") as f:
        for line in f:
            n, t = line.split()
            n_values.append(int(n))
            time_values.append(float(t))
    ax2.plot(n_values, time_values, marker=efficient_markers[i],
             color=efficient_colors[i], label=efficient_labels[i],
             linewidth=2, markersize=6)

ax2.set_xlabel("n")
ax2.set_ylabel("Time (s)")
ax2.set_title("Efficient Fibonacci Algorithms")
ax2.legend()
ax2.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig("fibonacci_comparison.png", dpi=300)

# Space complexity plots
plt.figure(figsize=(10, 6))
n_range = np.arange(10, 101, 10)
plt.plot(n_range, n_range, 'r-o', label='Recursive O(n)')
plt.plot(n_range, np.ones_like(n_range), 'b-s', label='Iterative O(1)')
plt.plot(n_range, n_range, 'g-^', label='Top-Down DP O(n)')
plt.plot(n_range, n_range, 'm-D', label='Bottom-Up DP O(n)')  # fixed marker issue

plt.xlabel("n")
plt.ylabel("Space (relative)")
plt.title("Space Complexity: Fibonacci Algorithms")
plt.legend()
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.savefig("fibonacci_space_comparison.png", dpi=300)

print("[*] Plots generated")

