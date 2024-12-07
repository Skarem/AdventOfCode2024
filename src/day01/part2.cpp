#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <set>
#include <unordered_map>

int main(int argc, char* argv[])
{
    std::string inputFile = argv[1];
    std::ifstream InputFile(inputFile);

    std::vector<int> list1;
    std::vector<int> list2;

    std::string strLine;
    while (std::getline(InputFile, strLine))
    {
        size_t len = strLine.find(' ');
        list1.push_back(stoi(strLine.substr(0, len))); 
        list2.push_back(stoi(strLine.substr(len + 1)));
    }

    std::vector<int> list1_copy = list1;

    std::set<int> uniqueNumbersInList1(list1.begin(), list1.end());
    list1.assign(uniqueNumbersInList1.begin(), uniqueNumbersInList1.end());

    std::unordered_map<int, int> map;

    for (int n : uniqueNumbersInList1)
    {
        map.insert({n, 0});
    }

    for (int n : list2)
    {
        if (auto search = map.find(n); search != map.end())
        {
            search->second += 1;
        }
    }

    int similarity = 0;

    for (int n : list1_copy)
    {
        similarity += n * map.find(n)->second;
    }
    
    std::cout << "Similarity score : " << similarity << std::endl;

    return 0;
}