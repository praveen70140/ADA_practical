import matplotlib.pyplot as plt

linear_n, linear_t = [], []
with open("linear.txt") as f:
    for line in f:
        n, t = line.split()
        linear_n.append(int(n))
        linear_t.append(float(t))

binary_n, binary_t = [], []
with open("binary.txt") as f:
    for line in f:
        n, t = line.split()
        binary_n.append(int(n))
        binary_t.append(float(t))

plt.plot(linear_n, linear_t, marker='o', label="Linear Search")
plt.plot(binary_n, binary_t, marker='s', label="Binary Search")

plt.xlabel("Number of elements (n)")
plt.ylabel("Time taken (seconds)")
plt.title("Time Complexity: Linear vs Binary Search")
plt.legend()
plt.grid(True)

plt.savefig("search_comparison.png")

