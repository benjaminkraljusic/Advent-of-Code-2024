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

    for(auto list1Num : lists.at(0)) {
        // number of occurences of list1Num in the second list
        unsigned int n(0);

        for(auto list2Num : lists.at(1))
            if(list2Num == list1Num)
                n++;

        sum += list1Num*n;
    }

    std::cout << "Result: " << sum << std::endl;
    
    input.close();

    return 0;
}