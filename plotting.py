import matplotlib.pyplot as plt

numNodes = []
durations = []

with open("duration.txt", "r") as file:
    for line in file:
        # Splitting each line by comma
        data = line.split(", ")
        # Extracting numNodes and duration
        numNodes.append(int(data[0].split(": ")[1]))
        durations.append(float(data[1].split(": ")[1].split()[0]))


# Plotting the graph
plt.plot(numNodes, durations)

# Adding labels and title
plt.xlabel('nodes')
plt.ylabel('time')
plt.title('Ford Fulkerson')

# Displaying the plot
plt.show()
