#include <vector>
#include <functional>

/* Generic schema for backtracking problems */

// For readability sake
typedef std::vector<int> vec;

// Helper recursive function:
// If we are at a final state, process it
// Otherwise:
// 1st: increment our current position in the solution space
// For each possible candidate movement in the current space and position, apply the movement and backtrack
int backtrack_(std::function<bool(vec&, vec&)> isSolution,
               std::function<void(vec&, vec&)> processSolution,
               std::function<vec(vec&, vec&)> generateCandidates, 
               vec& data,
               vec& a) {
    int count = 0;
    if(isSolution(data, a)) {
        processSolution(data, a);
        return 1;
    }
    else {
        vec candidates = generateCandidates(data, a);
        for(int &candidate: candidates) {
            a.push_back(candidate);
            count += backtrack_(isSolution, processSolution, generateCandidates, 
                                data, a);
            a.pop_back();
        }
    }         
    return count;          
}

int backtrack(std::function<bool(vec&, vec&)> isSolution,
              std::function<void(vec&, vec&)> processSolution,
              std::function<vec(vec&, vec&)> generateCandidates,
              vec& data) {
    vec a;
    return backtrack_(isSolution, processSolution, generateCandidates, data, a);
}