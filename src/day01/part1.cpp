#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <algorithm>
#include <cstdlib>

int main(int argc, char* argv[])
{
    std::string inputFile = argv[1];
    std::ifstream InputFile(inputFile);
    
    std::vector<int> list1;
    std::vector<int> list2;
    int distance = 0;

    std::string strLine;
    while (std::getline(InputFile, strLine))
    {
        size_t len = strLine.find(' ');
        list1.push_back(stoi(strLine.substr(0, len))); 
        list2.push_back(stoi(strLine.substr(len + 1)));
    }

    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    for (size_t i = 0; i < list1.size(); i++)
    {
        distance += std::abs(list1[i] - list2[i]);
    }

    std::cout << "Distance : " << distance << std::endl;

    InputFile.close();
    return 0;
}