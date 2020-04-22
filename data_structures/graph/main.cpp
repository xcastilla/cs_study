#include <iostream>
#include <string>
#include "graph.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: graph [INPUT_FILE]" << std::endl;
        exit(1);
    } 
    Graph *g = Graph::fromFile(argv[1], true);
    std::cout << *g;
    delete g;
}