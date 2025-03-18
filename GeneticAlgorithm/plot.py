import matplotlib.pyplot as plt

# Load the data from the text file
with open("results.txt", "r") as file:
    lines = file.readlines()

# Convert the rows into lists of floats
best_results = list(map(float, lines[0].split()))
worst_results = list(map(float, lines[1].split()))

# Plot the data
plt.figure(figsize=(10, 5))
plt.plot(best_results, label="Best Results", marker="o", linestyle="-", color="blue")
plt.plot(worst_results, label="Worst Results", marker="s", linestyle="--", color="red")

# Labels and title
plt.xlabel("Iteration")
plt.ylabel("Value")
plt.title("Best vs. Worst Results per Iteration")
plt.legend()
plt.grid(True)

# Show the plot
plt.show()
