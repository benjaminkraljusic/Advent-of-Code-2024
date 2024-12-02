#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<cstdlib>
#include<iterator>

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

int main() {
    std::ifstream input("input.txt");
    
    std::vector<int> report;
    std::string reportStr;
    int numSafeReports(0);

    while(!input.eof()) {
        std::getline(input, reportStr);

        report = getLevelsFromReportStr(reportStr);

        bool skip(false);

        std::vector<int>::iterator it; 

        for(it = report.begin() + 1; it < report.end() - 1; it++) {            
            // product of differences between two successive level pairs is positive if both pairs are increasing/decreasing 
            if(!((*it - *(it - 1))*(*(it + 1) - *it) > 0 && std::abs((*it) - *(it - 1)) >= LEVEL_DIFF_MIN && std::abs((*it) - *(it - 1)) <= LEVEL_DIFF_MAX)) {
                // report unsafe
                skip = true;
                break;
            }
        }

        // check for the last 2 levels in report if all others follow the rules
        // increasing/decreasing was checked earlier even for the last 2
        if(!skip)
            if(!(std::abs((*it) - *(it - 1)) >= LEVEL_DIFF_MIN && std::abs((*it) - *(it - 1)) <= LEVEL_DIFF_MAX))
                skip = true;

        // report unsafe - continue to next report
        if(skip)
            continue;

        // report safe - increase the number of safe reports
        numSafeReports++;
    }

    std::cout << "Number of safe reports: " << numSafeReports << std::endl;

    input.close();

    return 0;
}