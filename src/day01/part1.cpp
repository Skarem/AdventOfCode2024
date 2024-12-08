#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <algorithm>
#include <cstdlib>

void ReadDataFromFile(const std::string filename, 
                      std::vector<int>& list1, 
                      std::vector<int>& list2)
{
    std::ifstream inputFile(filename);
    std::string line;

    while (std::getline(inputFile, line))
    {
        size_t len = line.find(' ');
        list1.push_back(stoi(line.substr(0, len))); 
        list2.push_back(stoi(line.substr(len + 1)));
    }
    inputFile.close();
}

int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    std::vector<int> list1;
    std::vector<int> list2;
    ReadDataFromFile(filename, list1, list2);
    
    int distance = 0;

    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    for (size_t i = 0; i < list1.size(); i++)
    {
        distance += std::abs(list1[i] - list2[i]);
    }

    std::cout << "Distance : " << distance << std::endl;

    return 0;
}