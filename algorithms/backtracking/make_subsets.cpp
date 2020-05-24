#include <iostream>
#include "backtracking.h"

// Find and print all of the possible subsets from a given set

bool solutionState(std::vector<int>& data, std::vector<int>& a) {
    return a.size() == data.size();
}

void processSolution(std::vector<int>& data, std::vector<int>& a) {
    std::cout << "Solution: ";
    for(int i = 0; i < a.size(); i++) {
        if(a[i])
            std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

std::vector<int> generateCandidates(std::vector<int>& data, std::vector<int>& a) {
    std::vector<int> candidates(2, 0);
    candidates[1] = 1;
    return candidates;
}

int main() {
    std::vector<int> set = {1, 2, 3 , 4, 5};
    int sols = backtrack(solutionState, processSolution, generateCandidates, set);
    std::cout << "# Solutions: " << sols << std::endl;
    
}