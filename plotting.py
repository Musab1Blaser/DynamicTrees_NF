import matplotlib.pyplot as plt

numNodes = []
durations1 = []
durations2 = []
durations3 = []

with open("duration.txt", "r") as file:

    for line in file:
        # Splitting each line by comma
        data = line.split(", ")
        # Extracting numNodes and duration
        numNodes.append(int(data[0].split(": ")[1]))
        durations1.append(float(data[1].split(": ")[1].split()[0]))

with open("duration2.txt", "r") as file:
    for line in file:
        # Splitting each line by comma
        data = line.split(", ")
        # Extracting numNodes and duration
        # numNodes.append(int(data[0].split(": ")[1]))
        durations2.append(float(data[1].split(": ")[1].split()[0]))

with open("duration3.txt", "r") as file:
    for line in file:
        # Splitting each line by comma
        data = line.split(", ")
        # Extracting numNodes and duration
        # numNodes.append(int(data[0].split(": ")[1]))
        durations3.append(float(data[1].split(": ")[1].split()[0]))


# Plotting the graph
plt.plot(numNodes, durations1, label="Ford Fulkerson")
plt.plot(numNodes, durations2, label="Dinic's Algorithm with Dynamic Trees Unoptimised")
plt.plot(numNodes, durations3, label="Dinic's Algorithm with Dynamic Trees Optimised")
plt.legend()


# Adding labels and title
plt.xlabel("nodes")
plt.ylabel("time")
plt.title("Ford Fulkerson vs Dinic's Algorithm with Dynamic Trees")

# Displaying the plot
plt.show()

# numNodes = []
# durations = []

# with open("duration2.txt", "r") as file:
#     for line in file:
#         # Splitting each line by comma
#         data = line.split(", ")
#         # Extracting numNodes and duration
#         numNodes.append(int(data[0].split(": ")[1]))
#         durations.append(float(data[1].split(": ")[1].split()[0]))


# # Plotting the graph
# plt.plot(numNodes, durations)

# # Adding labels and title
# plt.xlabel("nodes")
# plt.ylabel("time")
# plt.title("Dinic's Algorithm with Dynamic Trees")

# # Displaying the plot
# plt.show()
