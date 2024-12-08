#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
    std::string inputFile = argv[1];
    std::ifstream InputFile(inputFile);
    
    std::string strLine;
    while (std::getline(InputFile, strLine))
    {
        std::cout << strLine << std::endl;
    }
    InputFile.close();
    
    return 0;
}