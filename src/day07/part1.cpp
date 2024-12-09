#include <iostream>
#include <fstream>
#include <string>

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

bool Recursive(std::vector<int> numbers, int index, int cur_value, int target_value)
{
    if (numbers.size() == index)
    {
        return target_value == cur_value;
    }
    return (Recursive(numbers, index + 1, cur_value + numbers[index], target_value) ||
            Recursive(numbers, index + 1, cur_value * numbers[index], target_value));
}

int main(int argc, char* argv[])
{
    std::string filename = argv[1];

    std::vector<long long> test_values;
    std::vector<std::vector<int>> numbers;
    ReadDataFromFile(filename, test_values, numbers);

    long long total_calibration_result = 0;
    for (int i = 0; i < test_values.size(); i++)
    {
        if (Recursive(numbers[i], 0, 0, test_values[i]))
            total_calibration_result += test_values[i];
    }

    std::cout << "Total calibration results : " << total_calibration_result << std::endl;
    
    return 0;
}