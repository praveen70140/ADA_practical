import matplotlib.pyplot as plt

# Read data for all matrix multiplication algorithms
algorithms = ['iterative', 'recursive', 'strassen']
colors = ['blue', 'red', 'green']
markers = ['o', 's', '^']

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
                color=colors[i], label=f"{algo.capitalize()} Matrix Multiplication", 
                linewidth=2, markersize=8)
    except FileNotFoundError:
        print(f"Warning: {algo}.txt not found")

plt.xlabel("Matrix Size (n x n)")
plt.ylabel("Time taken (seconds)")
plt.title("Time Complexity Comparison: Matrix Multiplication Algorithms")
plt.legend()
plt.grid(True, alpha=0.3)
plt.yscale('log')  # Log scale for better visualization
plt.xscale('log')  # Log scale for matrix sizes

# Add theoretical complexity lines
n_theoretical = [64, 128, 256, 512]
n3_line = [n**3 / 64**3 * 0.001 for n in n_theoretical]  # O(n^3) for iterative
n_log7_line = [n**2.807 / 64**2.807 * 0.0005 for n in n_theoretical]  # O(n^log7) for Strassen

plt.plot(n_theoretical, n3_line, '--', color='gray', alpha=0.7, label='O(n³) theoretical')
plt.plot(n_theoretical, n_log7_line, ':', color='purple', alpha=0.7, label='O(n^2.807) theoretical')

plt.legend()
plt.tight_layout()
plt.savefig("matrix_multiplication_comparison.png", dpi=300, bbox_inches='tight')
print("Plot saved as matrix_multiplication_comparison.png")

