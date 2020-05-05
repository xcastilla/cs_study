#include "../connected_components.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: conn_comps [INPUT_FILE]" << std::endl;
        exit(1);
    } 
    Graph *g = Graph::fromFile(argv[1], true);
    int comps = connected_components(g);

    std::cout << "Graph:" << std::endl << *g;
    std::cout << "Connected components: " << comps << std::endl;

    delete g;
}