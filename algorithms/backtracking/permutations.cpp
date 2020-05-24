#include <iostream>
#include <map>
#include "backtracking.h"

// Find and print all of the possible permutations of the elements in a given set

bool solutionState(std::vector<int>& data, std::vector<int>& a) {
    return a.size() == data.size();
}

void processSolution(std::vector<int>& data, std::vector<int>& a) {
    std::cout << "Solution: ";
    for(int i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

std::vector<int> generateCandidates(std::vector<int>& data, std::vector<int>& a) {
    std::map<int, bool> inPermutation;
    std::vector<int> candidates;

    for(int i = 0; i < a.size(); i++) {
        inPermutation.insert(std::pair<int, bool>(a[i], true));
    }
    for(int i = 0; i < data.size(); i++) {
        if(inPermutation.find(data[i]) == inPermutation.end()) {
            candidates.push_back(data[i]);
        }
    }

    return candidates;
}

int main() {
    std::vector<int> set = {1, 3, 100, 8, 5};
    int sols = backtrack(solutionState, processSolution, generateCandidates, set);
    std::cout << "# Solutions: " << sols << std::endl;
    
}