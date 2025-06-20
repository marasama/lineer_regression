import sys
import math
import matplotlib.pyplot as plt

class WeightAndBias:
    def __init__(self, weight=0.0, bias=0.0):
        self.weight = weight
        self.bias = bias

def read_weight_and_bias_file():
    try:
        with open("specs", "r") as file:
            line = file.readline().strip()
            parts = line.split(',')
            if len(parts) != 2:
                raise ValueError("Wrong file format!")
            weight = float(parts[0])
            bias = float(parts[1])
            return WeightAndBias(weight, bias)
    except Exception as e:
        print(f"Error reading specs file: {e}")
        sys.exit(1)

def read_dataset(filename):
    data = {}
    try:
        with open(filename, "r") as file:
            header = file.readline()  # skip header
            for line in file:
                line = line.strip()
                if not line:
                    continue
                parts = line.split(',')
                if len(parts) != 2:
                    continue
                mileage = float(parts[0])
                price = float(parts[1])
                data[mileage] = price
        return data
    except Exception as e:
        print(f"Error reading dataset file: {e}")
        sys.exit(1)

def predict(value, weight, bias):
    return weight * value + bias

def calculate_cost(dataset, weight, bias):
    total_cost = 0.0
    n = len(dataset)
    for x, y in dataset.items():
        total_cost += (predict(x, weight, bias) - y) ** 2
    return total_cost / n if n > 0 else float('inf')

def calculate_weight_gd(dataset, weight, bias):
    d_weight = 0.0
    n = len(dataset)
    for x, y in dataset.items():
        d_weight += (predict(x, weight, bias) - y) * x
    return d_weight / n if n > 0 else 0.0

def calculate_bias_gd(dataset, weight, bias):
    d_bias = 0.0
    n = len(dataset)
    for x, y in dataset.items():
        d_bias += (predict(x, weight, bias) - y)
    return d_bias / n if n > 0 else 0.0

def main():

    try:
        learning_rate = 0.001
        maximum_iteration = 1000
        dataset_file = "data.csv"
    except ValueError:
        print("Invalid input for learning rate or maximum iteration.")
        sys.exit(1)

    dataset = read_dataset(dataset_file)
    specs = read_weight_and_bias_file()

    print(f"Learning Rate: {learning_rate}")
    print(f"Max Iteration: {maximum_iteration}")
    print(f"Dataset File: {dataset_file}")
    print(f"Weight: {specs.weight}")
    print(f"Bias: {specs.bias}")

    cost = 0.0
    costs = []

    for i in range(maximum_iteration):
        dW = calculate_weight_gd(dataset, specs.weight, specs.bias)
        dB = calculate_bias_gd(dataset, specs.weight, specs.bias)

        specs.weight -= learning_rate * dW
        specs.bias -= learning_rate * dB

        cost = calculate_cost(dataset, specs.weight, specs.bias)
        costs.append(cost)

        if i % 10 == 0 or i == maximum_iteration - 1:
            print(f"Iteration: {i} Cost: {cost}")

    # Save final weights and bias to "specs" file
    try:
        with open("specs", "w") as out_file:
            out_file.write(f"{specs.weight},{specs.bias}\n")
    except Exception as e:
        print(f"Failed to write specs file: {e}")
        sys.exit(1)

    # Plot cost over iterations
    plt.figure(figsize=(12, 5))

    plt.subplot(1, 2, 1)
    plt.plot(range(len(costs)), costs, label="Cost")
    plt.xlabel("Iteration")
    plt.ylabel("Cost")
    plt.title("Cost over Iterations")
    plt.legend()
    plt.grid(True)

    # Plot dataset and fitted line
    plt.subplot(1, 2, 2)
    x_vals = sorted(dataset.keys())
    y_vals = [dataset[x] for x in x_vals]
    plt.scatter(x_vals, y_vals, color='blue', label='Data points')

    fitted_y = [predict(x, specs.weight, specs.bias) for x in x_vals]
    plt.plot(x_vals, fitted_y, color='red', label='Fitted line')

    plt.xlabel("Mileage")
    plt.ylabel("Price")
    plt.title("Dataset and Fitted Line")
    plt.legend()
    plt.grid(True)

    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    main()
