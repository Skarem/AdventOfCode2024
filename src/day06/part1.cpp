#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <unordered_map>

void ReadDataFromFile(const std::string& filename, std::vector<std::string>& map, int& posHeight, int& posWidth)
{
    std::ifstream inputFile(filename);
    std::string line;

    int counter = 0;
    while (std::getline(inputFile, line))
    {
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '^')
            {
                line[i] = '.';
                posHeight = counter;
                posWidth = i;
            }
        }
        counter++;
        map.push_back(line);
    }
    inputFile.close();
}

int CountDistinctPositions(std::vector<std::string>& map)
{
    int distinctPos = 0;
    for (const auto& line : map)
    {
        for (const char c : line)
        {
            if (c == 'X')
                distinctPos++;
        }
        // std::cout << line << std::endl;
    }
    return distinctPos;
}

enum class Direction
{
    Top,
    Down,
    Left,
    Right
};

std::unordered_map<Direction, std::pair<int, int>> direction_map = 
{
    { Direction::Top,   { -1,  0 } },
    { Direction::Down,  {  1,  0 } },
    { Direction::Left,  {  0, -1 } },
    { Direction::Right, {  0,  1 } },
};

void Move(std::vector<std::string>& map, int posHeight, int posWidth)
{
    bool out_of_border = false;
    Direction cur_dir = Direction::Top;

    while (!out_of_border)
    {
        // Check borders
        if (posHeight + direction_map[cur_dir].first >= 0 && 
            posHeight + direction_map[cur_dir].first < map.size() &&
            posWidth + direction_map[cur_dir].second >= 0 &&
            posWidth + direction_map[cur_dir].second < map[0].size())
        {
            if (map[posHeight + direction_map[cur_dir].first][posWidth + direction_map[cur_dir].second] != '#')
            {
                map[posHeight][posWidth] = 'X';
                // std::cout << posHeight << ", " << posWidth << std::endl;
                posHeight += direction_map[cur_dir].first;
                posWidth += direction_map[cur_dir].second;
            }
            else
            {
                switch (cur_dir)
                {
                    case Direction::Top:    cur_dir = Direction::Right; break;
                    case Direction::Right:  cur_dir = Direction::Down;  break;
                    case Direction::Down:   cur_dir = Direction::Left;  break;
                    case Direction::Left:   cur_dir = Direction::Top;   break;
                }
            }
        }
        else
        {
            map[posHeight][posWidth] = 'X';
            out_of_border = true;
        }
    }
}

int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    std::vector<std::string> map;
    int posWidth = 0, posHeight = 0;
    ReadDataFromFile(filename, map, posHeight, posWidth);

    Move(map, posHeight, posWidth);

    std::cout << "Distinct positions reached : " << CountDistinctPositions(map) << std::endl;

    
    return 0;
}