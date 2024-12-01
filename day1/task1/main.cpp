#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

int main() {
    std::ifstream input("input.txt");
    unsigned int listIdx(0), sum(0); 
    int x;

    std::vector<std::vector<int>> lists(2);
    
    // storing the input in two vectors (lists)
    while(input >> x) {
        lists.at(listIdx).push_back(x);

        // calculate the index of a list in which the next number is stored
        listIdx = (listIdx + 1)%2;
    }

    // sorting of the lists
    std::stable_sort(lists.at(0).begin(), lists.at(0).end());
    std::stable_sort(lists.at(1).begin(), lists.at(1).end());

    // sum up all the differences
    for(unsigned int i = 0; i < lists.at(0).size(); i++)
        sum += std::abs(lists.at(1).at(i) - lists.at(0).at(i));

    std::cout << "Result: " << sum << std::endl;
    
    input.close();

    return 0;
}