#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>

// returns the sum of valid mul instructions in a string
int getMulInstructionsSum(std::string str) {
    // pattern to match
    std::regex pattern("mul\\((\\d+,\\d+)\\)");

    int mulInstructionsSum(0);

    std::smatch match;

    while (std::regex_search(str, match, pattern)) {
        std::stringstream ss(match[1].str());
        
        // extract the two integers separated by comma
        int x, y;
        ss >> x;
        ss.ignore();
        ss >> y;
        
        // perform the mul instruction
        mulInstructionsSum += x*y;

        str = match.suffix().str();
    }

    return mulInstructionsSum;
}

int main() {
    std::ifstream input("input.txt");

    std::string line;
    int mulInstructionsSum(0);
    std::smatch match;

    std::string program("");

    while(!input.eof()) {
        std::getline(input, line);

        program += line;
    }
    
    // regular matching pattern
    std::regex pattern("do\\(\\)(.*?)don't\\(\\)");

    // match the first enabled mul functions (before the first don't())
    std::regex_search(program, match, std::regex("(.*?)don't\\(\\)"));
    mulInstructionsSum += getMulInstructionsSum(match[1].str());

    program = match.suffix().str();

    while(std::regex_search(program, match, pattern)) {
        
        mulInstructionsSum += getMulInstructionsSum(match[1].str());

        program = match.suffix().str();
    }
    
    // add the last mul function results
    std::regex_search(program, match, std::regex(".*do\\(\\)(.*?)"));
    mulInstructionsSum += getMulInstructionsSum(match[1].str());

    std::cout << "Sum of mul instructions in the memory: " << mulInstructionsSum << std::endl;

    input.close();

    return 0;
}