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

void DisplayMap(std::vector<std::string>& map)
{
    int distinctPos = 0;
    for (const auto& line : map)
    {
        std::cout << line << std::endl;
    }
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

bool Move(std::vector<std::string>& map, int posHeight, int posWidth)
{
    bool out_of_border = false;
    Direction cur_dir = Direction::Top;

    std::vector<std::pair<int, int>> moves;

    while (!out_of_border)
    {
        // Check borders
        if (posHeight + direction_map[cur_dir].first >= 0 && 
            posHeight + direction_map[cur_dir].first < map.size() &&
            posWidth + direction_map[cur_dir].second >= 0 &&
            posWidth + direction_map[cur_dir].second < map[0].size())
        {
            if (map[posHeight + direction_map[cur_dir].first][posWidth + direction_map[cur_dir].second] != '#' &&
                map[posHeight + direction_map[cur_dir].first][posWidth + direction_map[cur_dir].second] != 'O')
            {
                map[posHeight][posWidth] = 'X';

                moves.push_back({ posHeight, posWidth });
                std::size_t const half_size = moves.size() / 2;
                if (half_size % 2 == 0)
                {
                    std::vector<std::pair<int, int>> split_lo(moves.begin(), moves.begin() + half_size);
                    std::vector<std::pair<int, int>> split_hi(moves.begin() + half_size, moves.end());
                    if (split_lo == split_hi)
                        return true;
                }

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
    return false;
}

int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    std::vector<std::string> map;
    int posWidth = 0, posHeight = 0;
    ReadDataFromFile(filename, map, posHeight, posWidth);

    int loops = 0;

    int counter = 0;
    
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (map[i][j] != '#')
            {
                if (!(i == posHeight && j == posWidth))
                {
                    std::cout << "[" << i << "][" << j << "]" << std::endl;
                    std::vector<std::string> tmp_vec = map;
                    tmp_vec[i][j] = 'O';
                    if (Move(tmp_vec, posHeight, posWidth))
                    {
                        DisplayMap(tmp_vec);
                        loops++;
                    }
                }
            }
        }
    }

    // std::vector<std::string> tmp_vec = map;
    // tmp_vec[6][3] = 'O';
    // std::cout << Move(tmp_vec, posHeight, posWidth) << std::endl;
    // DisplayMap(tmp_vec);

    std::cout << "Number of positions creating loops : " << loops << std::endl;

    
    return 0;
}