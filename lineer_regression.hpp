#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <vector>
#include <math.h>
#include <limits>


class lineer_regression
{
    private:
        double _learning_rate;
        int64_t _max_iteration;
        std::string _dataset_file;
        
        double _weight = 0;
        double _bias = 0;
        
        std::map<double, double> dataset;

        

    public:
        lineer_regression()
        {
            _learning_rate = 0;
            _max_iteration = 0;
            _dataset_file = nullptr;
        };
        lineer_regression(const double &learning_rate, const double &max_iteration, const std::string &dataset_file)
        {
            _learning_rate = learning_rate;
            _max_iteration = max_iteration;
            _dataset_file = dataset_file;
        };
        double get_learning_rate(void)
        {
            return (_learning_rate);
        }
        void set_learning_rate(const double &lr)
        {
            _learning_rate = lr;
        }
        double get_max_iteration(void)
        {
            return (_learning_rate);
        }
        void set_max_iteration(const int64_t &max_it)
        {
            if (max_it < 0)
            {
                std::cout << "Cant set the iteration value under zero!";
                return;
            }
            _max_iteration = max_it;
        }
        std::string get_dataset_file(void)
        {
            return (_dataset_file);
        }
        void set_dataset_file(const std::string &data_file)
        {
            _dataset_file = data_file;
        }
        static double predict(const double &value, const double &weight, const double &bias)
        {
            return (weight * value + bias);
        }
        int read_dataset(void)
        {
            std::ifstream file(_dataset_file);

            if (!file.is_open())
            {
                std::cerr << "Couldn't open the dataset file" << std::endl;
                return (1);
            }
            std::vector<std::pair<double, double>> tmpData;
            std::string line;
            std::getline(file, line);
            double sum_mileage = 0;
            double sum_price = 0;
            while (std::getline(file, line))
            {
                std::stringstream ss(line);
                double price, mileage;
                char comma;
                ss >> mileage >> comma >> price;
                tmpData.push_back({mileage, price});

                sum_mileage += mileage;
                sum_price += price;
            }

            for (std::vector<std::pair<double, double>>::iterator it = tmpData.begin(); it != tmpData.end(); ++it)
            {

            }
        };
}