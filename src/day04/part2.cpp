#include <iostream>
#include <fstream>
#include <string>

#include <vector>

void ReadDataFromFile(const std::string& filename, std::vector<std::string>& array_2d, int& width, int& height)
{
    std::ifstream inputFile(filename);
    std::string line;

    while (std::getline(inputFile, line))
    {
        width = line.size();
        line.push_back('0');
        line.push_back('0');
        array_2d.push_back(line);
        // std::cout << line << std::endl;
        height++;
    }
    std::string padded_line(width + 2, '0');
    array_2d.push_back(padded_line);
    array_2d.push_back(padded_line);
    inputFile.close();
}

bool Cross(const std::vector<std::string>& array_2d, std::string cross, int i, int j)
{
    // std::cout << cross[0] << " . " << cross[1] << std::endl;
    // std::cout << ". " << cross[2] << " ." << std::endl;
    // std::cout << cross[3] << " . " << cross[4] << std::endl;
    // std::cout << std::endl;

    if (array_2d[  i  ][  j  ] == cross[0] &&
        array_2d[  i  ][j + 2] == cross[1] &&
        array_2d[i + 1][j + 1] == cross[2] &&
        array_2d[i + 2][  j  ] == cross[3] &&
        array_2d[i + 2][j + 2] == cross[4])
        return true;
    return false;
}

bool IsSafe(const std::vector<std::string>& array_2d, int i, int j)
{
    if (Cross(array_2d, "MMASS", i, j) ||
        Cross(array_2d, "MSAMS", i, j) ||
        Cross(array_2d, "SMASM", i, j) ||
        Cross(array_2d, "SSAMM", i, j))
        return true;
    return false;
}

int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    std::vector<std::string> array_2d;
    int width = 0, height = 0;
    ReadDataFromFile(filename, array_2d, width, height);
    
    int words = 0;

    

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (IsSafe(array_2d, i, j))
                words++;
        }
    }

    std::cout << "Words found : " << words << std::endl;

    return 0;
}