#include <iostream>
#include <fstream>
#include <string>

#include <vector>

void ReadDataFromFile(const std::string& filename, std::vector<std::string>& program)
{
    std::ifstream inputFile(filename);
    std::string line;

    while (std::getline(inputFile, line))
    {
        program.push_back(line);
    }
    inputFile.close();
}

int ExtractNum(const std::string& memory, int& index)
{
    std::string firstNum;
    while (memory[index] >= '0' && memory[index] <= '9')
    {
        firstNum.push_back(memory[index]);
        index++;
    }
    return stoi(firstNum);
}

int ParseMemory(const std::string& memory)
{
    int mul = 0;
    
    for (size_t i = 0; i < memory.size(); i++)
    {
        if (memory.substr(i, 4) == "mul(")
        {
            int firstIndex = i + 4;
            int firstNum = ExtractNum(memory, firstIndex);

            if (memory[firstIndex] == ',')
            {
                int secondIndex = firstIndex + 1;
                int secondNum = ExtractNum(memory, secondIndex);

                if (memory[secondIndex] == ')')
                {
                    mul += firstNum * secondNum;
                }
            }
        }
    }

    return mul;
}

int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    std::vector<std::string> program;
    ReadDataFromFile(filename, program);

    int mulInstructions = 0;

    for (const auto& memory : program)
    {
        mulInstructions += ParseMemory(memory);
    }

    std::cout << "Multiplication Instructions Sum : " << mulInstructions << std::endl;

    return 0;
}