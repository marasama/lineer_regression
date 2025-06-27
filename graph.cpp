#include "./A-Plot/A_Plot.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>

bool read_dataset(const std::string &filePath, std::vector<double> &mileages, std::vector<double> &prices)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Couldn't open dataset file." << std::endl;
        return (false);
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        double mileage, price;
        char comma;
        ss >> mileage >> comma >> price;

        mileages.push_back(mileage);
        prices.push_back(price);
    }

    return (true);
}

bool read_specs(double &weight, double &bias)
{
    std::ifstream file("specs");
    if (!file.is_open())
    {
        std::cerr << "Couldn't open specs file." << std::endl;
        return (false);
    }

    std::string line;
    if (!std::getline(file, line))
    {
        std::cerr << "Specs file is empty." << std::endl;
        return (false);
    }

    std::stringstream ss(line);
    std::string wStr, bStr;
    if (!std::getline(ss, wStr, ',') || !std::getline(ss, bStr))
    {
        std::cerr << "Invalid format in specs file." << std::endl;
        return (false);
    }

    try
    {
        weight = std::stod(wStr);
        bias = std::stod(bStr);
    }
    catch (...)
    {
        std::cerr << "Failed to parse weight/bias from specs file." << std::endl;
        return (false);
    }

    return (true);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "Usage: ./graph <option> <dataset_file>" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "    -d = Plot the dataset points" << std::endl;
        std::cout << "    -l = Plot the linear regression line" << std::endl;
        std::cout << "    -b = Plot both dataset points and linear regression line" << std::endl;
        return (1);
    }

    std::string option = argv[1];
    std::string dataset_file = argv[2];

    std::vector<double> mileages;
    std::vector<double> prices;

    if (!read_dataset(dataset_file, mileages, prices))
    {
        return (1);
    }

    double weight = 0;
    double bias = 0;

    if ((option == "-l" || option == "-b") && !read_specs(weight, bias))
    {
        return (1);
    }

    A_Plot plot;
    plot.setTitle("Linear Regression Visualization");
    plot.setLabel(X_LABEL, "Mileage");
    plot.setLabel(Y_LABEL, "Price");

    std::vector<Plot> plots;

    if (option == "-d" || option == "-b")
    {
        Plot dataPlot(mileages, prices, SCATTER_PLOT, "Dataset", "#FF8800", 1);
        plots.push_back(dataPlot);
    }

    if (option == "-l" || option == "-b")
    {
        double xMin = *std::min_element(mileages.begin(), mileages.end());
        double xMax = *std::max_element(mileages.begin(), mileages.end());

        Plot regLine = plot.createLinePlotX(weight, bias, xMin, xMax, "Regression", "#0000FF", 2);
        plots.push_back(regLine);
    }

    plot.plotMultiple(plots);

    return (0);
}
