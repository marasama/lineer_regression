#include "lineer_regression.hpp"

int read_weight_bias(double &weight, double &bias)
{
    std::ifstream file("specs");
    if (!file.is_open())    
    {
        std::cerr << "Couldn't open the spec file!" << std::endl;
        return (1);
    }

    std::string line;
    if (!std::getline(file, line))
    {
        std::cerr << "Empty spec file!" << std::endl;
        return (1);
    }

    std::stringstream ss(line);
    std::string weight_str, bias_str;

    if (!std::getline(ss, weight_str, ',') || !std::getline(ss, bias_str))
    {
        std::cerr << "Wrong file format! Expected format: weight,bias" << std::endl;
        return (1);
    }

    try
    {
        weight = std::stod(weight_str);
        bias = std::stod(bias_str);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Conversion error: " << e.what() << std::endl;
        return (1);
    }
    std::cout << "Weight at start: " << weight << " Bias at start: " << bias << std::endl;
    return (0);
};

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage:" << std::endl;
        std::cout << "./predict <number_of_mileage>" << std::endl;
        return (1);
    }
    double mileage;
    try
    {
        mileage = std::stod(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Invalid mileage input: " << argv[1] << std::endl;
        return (1);
    }
    
    double weight, bias;
    if (read_weight_bias(weight, bias))
    {
        return (1);
    }
    std::cout << "Prediction: " << lineer_regression::predict(mileage, weight, bias) << std::endl;
    return (0);
}