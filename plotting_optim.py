import matplotlib.pyplot as plt

numNodes = []
durations0 = []
durations1 = []

with open("opt_test_dur0.txt", "r") as file:

    for line in file:
        # Splitting each line by comma
        data = line.split(", ")
        # Extracting numNodes and duration
        numNodes.append(int(data[0].split(": ")[1]))
        durations0.append(float(data[1].split(": ")[1].split()[0]))

with open("opt_test_dur1.txt", "r") as file:
    for line in file:
        # Splitting each line by comma
        data = line.split(", ")
        # Extracting numNodes and duration
        # numNodes.append(int(data[0].split(": ")[1]))
        durations1.append(float(data[1].split(": ")[1].split()[0]))

plt.rcParams['font.size'] = 22
lw = 6

# Plotting the graph
plt.plot(numNodes, durations0, label="Unoptimized Dynamic Tree", linestyle='solid', linewidth=lw)
plt.plot(numNodes, durations1, label="Optimized Dynamic Tree", linestyle='dotted', linewidth=lw)
plt.legend()


# Adding labels and title
plt.xlabel("Nodes")
plt.ylabel("Time (s)")
plt.title(f"Optimized vs Unoptimized Dynamic Tree Performance Comparison")

# Displaying the plot
plt.show()
