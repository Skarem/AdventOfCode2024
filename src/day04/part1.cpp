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
        line.push_back('0');
        array_2d.push_back(line);
        // std::cout << line << std::endl;
        height++;
    }
    std::string padded_line(width + 3, '0');
    array_2d.push_back(padded_line);
    array_2d.push_back(padded_line);
    array_2d.push_back(padded_line);
    inputFile.close();
}

int Horizontal(const std::vector<std::string>& array_2d, std::string word, int i, int j)
{
    if (array_2d[i][j] == word[0] &&
        array_2d[i][j + 1] == word[1] &&
        array_2d[i][j + 2] == word[2] &&
        array_2d[i][j + 3] == word[3])
        return 1;
    return 0;
}

int Vertical(const std::vector<std::string>& array_2d, std::string word, int i, int j)
{
    if (array_2d[i][j] == word[0] &&
        array_2d[i + 1][j] == word[1] &&
        array_2d[i + 2][j] == word[2] &&
        array_2d[i + 3][j] == word[3])
        return 1;
    return 0;
}

int DiagonalLeft(const std::vector<std::string>& array_2d, std::string word, int i, int j)
{
    if (array_2d[i][j] == word[0] &&
        array_2d[i + 1][j + 1] == word[1] &&
        array_2d[i + 2][j + 2] == word[2] &&
        array_2d[i + 3][j + 3] == word[3])
        return 1;
    return 0;
}

int DiagonalRight(const std::vector<std::string>& array_2d, std::string word, int i, int j)
{
    if (array_2d[i][j + 3] == word[0] &&
        array_2d[i + 1][j + 2] == word[1] &&
        array_2d[i + 2][j + 1] == word[2] &&
        array_2d[i + 3][j] == word[3])
        return 1;
    return 0;
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
            words += Horizontal(array_2d, "XMAS", i, j);
            words += Horizontal(array_2d, "SAMX", i, j);
            words += Vertical(array_2d, "XMAS", i, j);
            words += Vertical(array_2d, "SAMX", i, j);
            words += DiagonalLeft(array_2d, "XMAS", i, j);
            words += DiagonalLeft(array_2d, "SAMX", i, j);
            words += DiagonalRight(array_2d, "XMAS", i, j);
            words += DiagonalRight(array_2d, "SAMX", i, j);
        }
    }

    std::cout << "Words found : " << words << std::endl;

    return 0;
}