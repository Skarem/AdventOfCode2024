#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <sstream>

void ReadDataFromFile(const std::string& filename, std::vector<std::vector<int>>& array_2d)
{
    std::ifstream inputFile(filename);
    std::string line;
    int number;
    
    while (std::getline(inputFile, line))
    {
        std::vector<int> tmp_vec;
        std::istringstream ss(line);
        
        while (ss >> number)
        {
            tmp_vec.push_back(number);
        }
        array_2d.push_back(tmp_vec);
    }
    inputFile.close();
}

bool IsSafe(const std::vector<int>& array)
{
    bool increasing = true;
    bool decreasing = true;

    for (size_t i = 1; i < array.size(); i++)
    {
        int diff = abs(array[i] - array[i - 1]);
        if (diff < 1 || diff > 3) return false;
        if (array[i - 1] > array[i]) decreasing = false;
        if (array[i - 1] < array[i]) increasing = false;
    }
    return increasing || decreasing;
}

bool IsSafePar2(const std::vector<int>& array)
{
    if (IsSafe(array)) return true;

    for (size_t i = 0; i < array.size(); i++)
    {
        std::vector<int> modified;
        for (size_t j = 0; j < array.size(); j++)
        {
            if (i != j) modified.push_back(array[j]);
        }
        if (IsSafe(modified)) return true;
    }
    return false;
}

int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    std::vector<std::vector<int>> array_2d;
    ReadDataFromFile(filename, array_2d);
    
    int safeNumber = 0;

    for (const auto& array : array_2d)
    {
        // if (IsSafe(array)) safeNumber++;
        if (IsSafePar2(array)) safeNumber++;
    }
    std::cout << "Safe : " << safeNumber << std::endl;
}



