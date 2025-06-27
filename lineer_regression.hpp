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
        
        
        double mean_mileage = 0;
        double std_mileage = 1;
        double mean_price = 0;
        double std_price = 1;
    public:
        std::map<double, double> dataset;
        lineer_regression()
        {
            _learning_rate = 0;
            _max_iteration = 0;
            _dataset_file = "";
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
        };
        void set_learning_rate(const double &lr)
        {
            _learning_rate = lr;
        };
        double get_max_iteration(void)
        {
            return (_learning_rate);
        };
        void set_max_iteration(const int64_t &max_it)
        {
            if (max_it < 0)
            {
                std::cout << "Cant set the iteration value under zero!";
                return;
            }
            _max_iteration = max_it;
        };
        void set_weight(const double &weight)
        {
            _weight = weight;
        };
        double get_weight(void)
        {
            return (_weight);
        };
        double get_denormalize_weight(void)
        {
            return (_weight * (std_price / std_mileage));
        };
        double get_denormalize_bias(void)
        {
            return (mean_price - get_denormalize_weight() * mean_mileage + (_bias * std_price));
        };
        void set_bias(const double &bias)
        {
            _bias = bias;
        };
        double get_bias(void)
        {
            return (_bias);
        };
        std::string get_dataset_file(void)
        {
            return (_dataset_file);
        };
        void set_dataset_file(const std::string &data_file)
        {
            _dataset_file = data_file;
        };
        static double predict(const double &value, const double &weight, const double &bias)
        {
            return (weight * value + bias);
        };
        static double normalize(double value, double mean, double std)
        {
            return (value - mean) / std;
        };
        static double denormalize(double value, double mean, double std)
        {
            return value * std + mean;
        };
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
            int count = 0;
            while (std::getline(file, line))
            {
                std::stringstream ss(line);
                double price, mileage;
                char comma;
                ss >> mileage >> comma >> price;
                tmpData.push_back({mileage, price});

                sum_mileage += mileage;
                sum_price += price;
                count++;
            }

            mean_mileage = sum_mileage / count;
            mean_price = sum_price / count;

            double variance_mileage = 0, variance_price = 0;
            for (std::vector<std::pair<double, double>>::iterator it = tmpData.begin(); it != tmpData.end(); ++it)
            {
                variance_mileage += pow(it->first - mean_mileage, 2);
                variance_price += pow(it->second - mean_price, 2);
            }

            std_mileage = sqrt(variance_mileage / count);
            std_price = sqrt(variance_price / count);
            
            for (std::vector<std::pair<double, double>>::iterator it = tmpData.begin(); it != tmpData.end(); ++it)
            {
                double norm_mileage = normalize(it->first, mean_mileage, std_mileage);
                double norm_price = normalize(it->second, mean_price, std_price);
                dataset[norm_mileage] = norm_price;
            }
            return (0);
        };
        int read_weight_bias(void)
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
                _weight = std::stod(weight_str);
                _bias = std::stod(bias_str);
            }
            catch (const std::exception& e)
            {
                std::cerr << "Conversion error: " << e.what() << std::endl;
                return (1);
            }
            std::cout << "Weight at start: " << _weight << " Bias at start: " << _bias << std::endl;
            return (0);
        };
        static double calculate_cost(const std::map<double, double> &dataset, const double &weight, const double &bias)
        {
            double total_cost = 0;
            double m = dataset.size();
            for (std::map<double, double>::const_iterator it = dataset.begin(); it != dataset.end(); ++it)
            {
                total_cost += pow(predict(it->first, weight, bias) - it->second, 2); 
            }
            return (total_cost / m);
        };
        static double calculate_weight_gd(const std::map<double, double> &dataset, const double &weight, const double &bias)
        {
            double d_Weight = 0;
            int n = dataset.size();
            for (std::map<double, double>::const_iterator it = dataset.begin(); it != dataset.end(); it++)
            {
                d_Weight += (predict(it->first, weight, bias) - it->second) * it->first;
            }
            return d_Weight / n;
        };
        static double calculate_bias_gd(const std::map<double, double> &dataset, const double &weight, const double &bias)
        {
            double d_bias = 0;
            int n = dataset.size();
            for (std::map<double, double>::const_iterator it = dataset.begin(); it != dataset.end(); it++)
            {
                d_bias += (predict(it->first, weight, bias) - it->second);
            }
            return d_bias / n;
        };
        void train(void)
        {
            int i = 0;
            while (i < _max_iteration)
            {
                _weight -= _learning_rate * calculate_weight_gd(dataset, _weight, _bias);
                _bias -= _learning_rate * calculate_bias_gd(dataset, _weight, _bias);
                double cost = calculate_cost(dataset, _weight, _bias);
                std::cout << "| Iteration: " << i + 1 << " | Cost: " << cost << " | Weight: " << _weight << " | Bias: " << _bias << " |" << std::endl; 
                i++;
            }
        };
        void write_specs(void)
        {
            std::ofstream out("specs");
            if (out.is_open())
            {
                out << get_denormalize_weight() << "," << get_denormalize_bias() << std::endl;
                out.close();
            }
            else
            {
                std::cerr << "Failed to open specs file for writing." << std::endl;
                exit(1);
            }
        }
};