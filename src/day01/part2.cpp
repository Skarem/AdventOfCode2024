#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <set>
#include <unordered_map>

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

    std::unordered_map<int, int> map;
    std::vector<int> list1_copy = list1;

    std::set<int> uniqueNumbersInList1(list1.begin(), list1.end());
    list1.assign(uniqueNumbersInList1.begin(), uniqueNumbersInList1.end());

    for (int n : uniqueNumbersInList1) 
        map.insert({n, 0});
        
    for (int n : list2)
        if (auto search = map.find(n); search != map.end())
            search->second += 1;

    int similarity = 0;

    for (int n : list1_copy)
        similarity += n * map.find(n)->second;

    std::cout << "Similarity score : " << similarity << std::endl;

    return 0;
}