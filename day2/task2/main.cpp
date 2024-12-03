#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iterator>

#define LEVEL_DIFF_MIN 1
#define LEVEL_DIFF_MAX 3

// get vector of levels (int) from string containing integers
std::vector<int> getLevelsFromReportStr(std::string &reportStr) {
    std::stringstream ss(reportStr);
    std::vector<int> levels;
    int level;

    while(ss >> level)
        levels.push_back(level);

    return levels;
}

bool reportSafeCheck(std::vector<int> &report) {
    std::vector<int>::iterator it; 

    for(it = report.begin() + 1; it < report.end() - 1; it++)            
        // product of differences between two successive level pairs is positive if both pairs are increasing/decreasing 
        if(!((*it - *(it - 1))*(*(it + 1) - *it) > 0 && std::abs((*it) - *(it - 1)) >= LEVEL_DIFF_MIN && std::abs((*it) - *(it - 1)) <= LEVEL_DIFF_MAX)) 
            // report unsafe
            return false;

    // check for the last 2 levels in report if all others follow the rules
    // increasing/decreasing was checked earlier even for the last 2
    if(!(std::abs((*it) - *(it - 1)) >= LEVEL_DIFF_MIN && std::abs((*it) - *(it - 1)) <= LEVEL_DIFF_MAX))
        return false;

    return true;
}

int main() {
    std::ifstream input("input.txt");
    
    std::vector<int> report;
    std::string reportStr;
    int numSafeReports(0);

    while(!input.eof()) {
        std::getline(input, reportStr);

        report = getLevelsFromReportStr(reportStr);

        // check the initial report
        if(reportSafeCheck(report)) {
            numSafeReports++;

            // initial report safe - check the next report
            continue;
        }

        bool skip(false);

        // initial report not safe
        for(int i = 0; i < report.size(); i++) {
            auto reportTmp = report;
            reportTmp.erase(reportTmp.begin() + i);

            if(reportSafeCheck(reportTmp)){
                skip = true;
                break;
            }
        }

        if(skip) 
            numSafeReports++;

    }

    std::cout << "Number of safe reports: " << numSafeReports << std::endl;

    input.close();

    return 0;
}