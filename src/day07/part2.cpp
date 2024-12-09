#include <iostream>
#include <fstream>
#include <string>

#include <cmath>
#include <vector>
#include <sstream>

void ReadDataFromFile(const std::string& filename,
                      std::vector<long long>& test_values,
                      std::vector<std::vector<int>>& numbers)
{
    std::ifstream inputFile(filename);
    std::string line;
    int number;

    while (std::getline(inputFile, line))
    {
        size_t len = line.find(':');
        test_values.push_back(stoll(line.substr(0, len)));

        std::vector<int> tmp_vec;
        std::istringstream ss(line.substr(len + 1));

        while (ss >> number)
        {
            tmp_vec.push_back(number);
        }
        numbers.push_back(tmp_vec);
    }
    inputFile.close();
}

void GenerateMasks(int size, std::vector<std::string>& masks)
{
    int totalCombinations = pow(3, size);

    for (int i = 0; i < totalCombinations; i++)
    {
        std::string mask;
        int temp = i;
        for (int j = 0; j < size; j++)
        {
            int mod = temp % 3;
            char oper;
            switch (mod)
            {
                case 0: oper = '+'; break;
                case 1: oper = '*'; break;
                case 2: oper = '|'; break;
            }
            mask.push_back(oper);
            temp /= 3;
        }
        // std::cout << mask << std::endl;
        masks.push_back(mask);
    }
}

std::vector<int> ApplyCombineOperator(const std::vector<int>& numbers, const std::string& mask)
{
    std::vector<int> combined;
    int current = numbers[0];

    for (int i = 0; i < mask.size(); i++)
    {
        if (mask[i] == '|')
        {
            current = std::stoi(std::to_string(current) + std::to_string(numbers[i + 1]));
        }
        else
        {
            combined.push_back(current);
            current = numbers[i + 1];
        }
    }
    combined.push_back(current);
    return combined;
}

void Display(std::vector<int>& vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    std::string filename = argv[1];

    std::vector<long long> test_values;
    std::vector<std::vector<int>> numbers;
    ReadDataFromFile(filename, test_values, numbers);

    long long total_calibration_result = 0;


    std::cout << "TEST" << std::endl;
    Display(numbers[0]);
    std::cout << "TEST" << std::endl;

    // Create all the masks
    std::vector<std::string> masks;
    GenerateMasks(numbers[0].size(), masks);

    // Apply combine operator
    for (const auto& mask : masks)
    {
        std::vector<int> mod_vec = ApplyCombineOperator(numbers[0], mask);
        Display(mod_vec);
    }
    

    std::cout << "Total calibration results : " << total_calibration_result << std::endl;
    
    return 0;
}