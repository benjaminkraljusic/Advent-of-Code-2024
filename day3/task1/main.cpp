#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>

int main() {
    std::ifstream input("input.txt");
   
    // pattern to match
    std::regex pattern("mul\\((\\d+,\\d+)\\)");

    std::smatch match;

    int mulInstructionsSum(0);

    std::string line;

    while(!input.eof()) {
        std::getline(input, line);

        while (std::regex_search(line, match, pattern)) {
            std::stringstream ss(match[1].str());
            
            // extract the two integers separated by comma
            int x, y;
            ss >> x;
            ss.ignore();
            ss >> y;
            
            // perform the mul instruction
            mulInstructionsSum += x*y;

            line = match.suffix().str();
        }
    }

    std::cout << "Sum of mul instructions in the memory: " << mulInstructionsSum << std::endl;

    input.close();

    return 0;
}