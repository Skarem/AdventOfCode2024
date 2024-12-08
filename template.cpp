#include <iostream>
#include <fstream>
#include <string>

void ReadDataFromFile(std::string filename)
{
    std::ifstream inputFile(filename);
    std::string line;

    while (std::getline(inputFile, line))
    {
        std::cout << line << std::endl;
    }
    inputFile.close();
}

int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    ReadDataFromFile(filename);
    return 0;
}