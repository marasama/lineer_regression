#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <vector>
#include <math.h>
#include <limits>
#include "lineer_regression.hpp"


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

    lineer_regression zort(learning_rate, maximum_iteration, dataset_file);

    zort.read_dataset();

    zort.train();

    zort.write_specs();

    return (0);
}