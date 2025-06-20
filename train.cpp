#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <math.h>

typedef struct weight_and_bias
{
    double weight;
    double bias;
}   weight_and_bias;

weight_and_bias read_weight_and_bias_file(void)
{
    std::ifstream file("specs");
    double weight = 0;
    double bias = 0;
    char comma;
    if (!file.is_open())    
    {
        std::cerr << "Couldn't open the spec file!" << std::endl;
        exit(1);
    }

    file >> weight >> comma >> bias;
    file.close();

    if (comma == ',' && file)
        return ((weight_and_bias){weight, bias});
    else
    {
        std::cerr << "Wrong file format!" << std::endl;
        exit(1);
    }
}

void read_dataset(std::string filename, std::map<double, double> &data)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Couldn't open the dataset file" << std::endl;
        exit(1);
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        double price, mileage;
        char comma;
        ss >> mileage >> comma >> price;
        data[mileage] = price;
    }
}

double predict(const double &value, const double &weight, const double &bias)
{
    return (weight * value + bias);
}

double calculate_cost(const std::map<double, double> &dataset, const double &weight, const double &bias)
{
    double total_cost = 0;
    double m = dataset.size();
    for (std::map<double, double>::const_iterator it = dataset.begin(); it != dataset.end(); ++it)
    {
        total_cost += pow(predict(it->first, weight, bias) - it->second, 2) / m; 
    }
    return (total_cost);
}

double calculate_weight_gd(const std::map<double, double> &dataset, const double &weight, const double &bias)
{
    double d_Weight = 0;
    int n = dataset.size();
    for (std::map<double, double>::const_iterator it = dataset.begin(); it != dataset.end(); it++)
    {
        d_Weight += (predict(it->first, weight, bias) - it->second) * it->first;
    }
    return d_Weight / n;
}

double calculate_bias_gd(const std::map<double, double> &dataset, const double &weight, const double &bias)
{
    double d_bias = 0;
    int n = dataset.size();
    for (std::map<double, double>::const_iterator it = dataset.begin(); it != dataset.end(); it++)
    {
        d_bias += (predict(it->first, weight, bias) - it->second);
    }
    return d_bias / n;
}

int main(int argc, char **argv)
{ 
    if (argc != 4)
    {
        std::cout \
        << "Wrong number of arguments!\n" \
        << "Usage: ./train <learning_rate> <maximum_iteration> <dataset_file>" \
        << std::endl;
        return (1);
    }
    
    double cost = 0;
    double learning_rate = 0;
    int maximum_iteration = 1000;
    std::string dataset_file;
    std::stringstream ss;
    ss.str(argv[1]);
    ss.clear();
    if (!(ss >> learning_rate))
    {
        std::cerr << "Invalid learning rate.\n";
        return (1);
    }
    
    ss.str(argv[2]);
    ss.clear();
    if (!(ss >> maximum_iteration))
    {
        std::cerr << "Invalid maximum iteration.\n";
        return (1);
    }
    
    dataset_file = argv[3];

    std::map<double, double> dataset;

    read_dataset(dataset_file, dataset);

    weight_and_bias specs = read_weight_and_bias_file();

    std::cout << "Learning Rate: " << learning_rate << std::endl;
    std::cout << "Max Iteration: " << maximum_iteration << std::endl;
    std::cout << "Dataset File: " << dataset_file << std::endl;
    std::cout << "Weight: " << specs.weight << std::endl;
    std::cout << "Bias: " << specs.bias << std::endl;

    for (int i = 0; i < maximum_iteration; i++)
    {
        std::cout << "Iteration: " << i << " Weight: " << specs.weight << " Bias: " << specs.bias <<  " Cost: " << cost << std::endl;

        double dW = calculate_weight_gd(dataset, specs.weight, specs.bias);

        double dB = calculate_bias_gd(dataset, specs.weight, specs.bias);

        specs.weight -= learning_rate * dW;
        specs.bias -= learning_rate * dB;
        //cost = calculate_cost(dataset, specs.weight, specs.bias);
    }

    std::ofstream out("specs");
    if (out.is_open())
    {
        out << specs.weight << "," << specs.bias << std::endl;
        out.close();
    }
    else
    {
        std::cerr << "Failed to open specs file for writing." << std::endl;
        return (1);
    }

    return (0);
}