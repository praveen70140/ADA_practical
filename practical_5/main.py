import matplotlib.pyplot as plt
import numpy as np

plt.style.use('dark_background')

plt.figure(figsize=(12, 7))

n_f, time_f = [], []
try:
    with open("fractional_knapsack.txt") as f:
        for line in f:
            n, t = line.split()
            n_f.append(int(n))
            time_f.append(float(t))
    plt.plot(n_f, time_f, marker='o', color='#00ff00', linestyle='-', label='Fractional Knapsack (Greedy) O(n log n)')
except FileNotFoundError:
    print("Warning: fractional_knapsack.txt not found. Run the C code first.")

n_01, time_01 = [], []
try:
    with open("01_knapsack.txt") as f:
        for line in f:
            n, t = line.split()
            n_01.append(int(n))
            time_01.append(float(t))
    plt.plot(n_01, time_01, marker='x', color='#ff00ff', linestyle='--', label='0/1 Knapsack (DP) O(n*W)')
except FileNotFoundError:
    print("Warning: 01_knapsack.txt not found. Run the C code first.")


plt.xlabel("Number of Items (n)")
plt.ylabel("Time Taken (microseconds)")
plt.title("Time Complexity: Knapsack Algorithms")
plt.legend()
plt.grid(True, alpha=0.2)
plt.tight_layout()
plt.savefig("knapsack_time_comparison.png")
print("Time complexity plot saved as knapsack_time_comparison.png")

plt.figure(figsize=(12, 7))

n_range = np.array(n_01 if n_01 else [100, 2000])
W = 1000

space_f = n_range
space_01 = n_range * W

plt.plot(n_range, space_f, marker='o', color='#00aaff', linestyle='-', label='Fractional Knapsack O(n)')
plt.plot(n_range, space_01, marker='x', color='#ffa500', linestyle='--', label=f'0/1 Knapsack O(n*W) with W={W}')

plt.xlabel("Number of Items (n)")
plt.ylabel("Space Units (Relative)")
plt.title("Theoretical Space Complexity: Knapsack Algorithms")
plt.yscale('log')
plt.legend()
plt.grid(True, alpha=0.2)
plt.tight_layout()
plt.savefig("knapsack_space_comparison.png")
print("Space complexity plot saved as knapsack_space_comparison.png")


