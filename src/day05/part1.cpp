#include <iostream>
#include <fstream>
#include <string>

#include <unordered_map>
#include <vector>
#include <sstream>
#include <cmath>

void ReadDataFromFile(const std::string& filename,
                      std::unordered_map<int, std::vector<int>>& map_order,
                      std::vector<std::vector<int>>& updates)
{
    std::ifstream inputFile(filename);
    std::string line;

    bool change_section = false;

    while (std::getline(inputFile, line))
    {
        // std::cout << line << std::endl;
        if (line.empty())
            change_section = true;
        
        if (!change_section)
        {
            size_t len = line.find('|');
            int key = stoi(line.substr(0, len));
            int value = stoi(line.substr(len + 1));
            // std::cout << i << ", " << j << std::endl;
            map_order[key].push_back(value);
        }
        else if (!line.empty())
        {
            // std::cout << "UPDATES" << std::endl;
            std::vector<int> tmp_vec;
            bool loop = true;
            while (loop)
            {
                size_t pos = line.find_first_of(',');
                // std::cout << line.substr(0, pos) << " ";
                // std::cout << line.substr(0, pos).size() << std::endl;

                tmp_vec.push_back(stoi(line.substr(0, pos)));
                if (line[pos] == ',')
                {
                    line = line.substr(pos + 1);
                }
                else
                {
                    loop = false;
                }
            }
            // std::cout << std::endl;
            updates.push_back(tmp_vec);
        }
    }
    inputFile.close();
}

int main(int argc, char* argv[])
{
    std::string filename = argv[1];

    std::unordered_map<int, std::vector<int>> map_order;
    std::vector<std::vector<int>> updates;
    ReadDataFromFile(filename, map_order, updates);
    
   int sum = 0;

    for (const auto& update : updates)
    {
        bool isSafe = true;

        for (int i = 1; i < update.size(); i++)
        {
            int cur_value = update[i];
            
            if (map_order.find(cur_value) != map_order.end())
            {
                for (int value_to_check : map_order[cur_value])
                {
                    for (int j = 0; j < i; j++)
                    {
                        int old_value = update[j];
                        if (value_to_check == old_value)
                            isSafe = false;
                    }
                }
            }
        }
        if (isSafe)
        {
            int middle_value = update[update.size() / 2];
            std::cout << middle_value << std::endl;
            sum += middle_value;
        }
    }

    std::cout << "Sum : " << sum << std::endl;

    return 0;
}