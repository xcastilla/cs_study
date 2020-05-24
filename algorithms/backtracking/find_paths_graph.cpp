#include <map>
#include "../../data_structures/graph/graph.h"

// Find and print all of the possible paths from node S to node T in a given graph

/* Example running with assets/graph.txt
    Graph: 
    0 to 2 : Weight 5
    1 to 3 : Weight 2
    2 to 0 : Weight 4
    2 to 1 : Weight 5
    3 to 4 : Weight 1
    3 to 5 : Weight 2
    4 to 3 : Weight 1
    4 to 5 : Weight 1
    5 to 1 : Weight 3
    -----------
    Paths from 0 to 5:
    Solution: 0 2 1 3 4 5 
    Solution: 0 2 1 3 5 
    # Solutions: 2 
*/

bool solutionState(std::vector<int>& a, int finalState) {
    return a[a.size() - 1] == finalState;
}

void processSolution(std::vector<int>& a) {
    std::cout << "Solution: ";
    for(int i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

std::vector<int> generateCandidates(Graph *g, std::vector<int>& a) {
    std::vector<int> candidates;
    std::map<int, bool> inPath;
    int currentNode = a[a.size() - 1];

    for(int i = 0; i < a.size(); i++) {
        inPath.insert(std::pair<int, bool>(a[i], true));
    }
    for(Edge ed: g->getAdjList(currentNode)) {
        if(inPath.find(ed.toIdx) == inPath.end()) {
            candidates.push_back(ed.toIdx);
        }
    }

    return candidates;
}

int backtrack(Graph* g, std::vector<int>& a, const int finalState) {
    int count = 0;
    if(solutionState(a, finalState)) {
        processSolution(a);
        return 1;
    }
    else {
        std::vector<int> candidates = generateCandidates(g, a);
        for(int &candidate: candidates) {
            a.push_back(candidate);
            count += backtrack(g, a, finalState);
            a.pop_back();
        }
    }

    return count;          
}


int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: paths [INPUT_FILE]" << std::endl;
        exit(1);
    } 
    Graph *g = Graph::fromFile(argv[1], true);
    std::cout << "Graph: " << std::endl << *g;
    std::cout << "-----------" << std::endl;

    int initialNode = 0;
    int finalNode = g->getNumberNodes() - 1;
    std::cout << "Paths from " << initialNode << " to " << finalNode <<  ":" << std::endl; 

    std::vector<int> a;
    a.push_back(initialNode);
    int sols = backtrack(g, a, finalNode);
    std::cout << "# Solutions: " << sols << std::endl;
    
    delete g;
}
