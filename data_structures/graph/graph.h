#include <vector>
#include <fstream>
#include <sstream>

struct Edge {
    int fromIdx;
    int toIdx;
    float weight;
    Edge(int fromIdx, int toIdx, float weight): fromIdx(fromIdx), toIdx(toIdx), weight(weight) {};
};

class Graph {
public:
    Graph(int nNodes, bool directed);
    ~Graph();
    static Graph* fromFile(std::string path, bool directed);
    void addEdge(int from, int to, float weight);
    inline bool isDirected() const { return directed_; };

    friend std::ostream& operator <<(std::ostream& oss, const Graph& other) {
        for(int i = 0; i < other.nNodes_; i++) {
            for(Edge eg: other.adjList_[i]) {
                oss << i << " to " << eg.toIdx << " : Weight " << eg.weight << std::endl;
            }
        }
        return oss;
    }

private:
    // Number of nodes
    int nNodes_;
    // Adjacency list for each node in the graph
    std::vector<std::vector<Edge>> adjList_;
    // Output degree for every node in the graph
    std::vector<int> degree_;
    // Is the graph directed or undirected?
    bool directed_;
};

Graph::Graph(int nNodes, bool directed) {
    nNodes_ = nNodes;
    directed_ = directed;
    for(int i = 0; i < nNodes; i++) {
        adjList_.push_back(std::vector<Edge>());
        degree_.push_back(0);
    }
}

Graph::~Graph() {

}

void Graph::addEdge(int from, int to, float weight) {
    if(from > nNodes_) {
        std::cerr << "Invalid node id: " << from  << std::endl;
        return;
    }
    else if(to > nNodes_) {
        std::cerr << "Invalid node id: " << to  << std::endl;
        return;
    }
    adjList_[from].push_back(Edge(from, to, weight));
    degree_[from]++;
}

Graph* Graph::fromFile(std::string path, bool directed) {
    std::ifstream inFile;
    inFile.open(path);
    if(!inFile) {
        std::cerr << "Path: " << path << " could not be opened." << std::endl;
        exit(1);
    }

    std::string line;
    // Read number of nodes and create graph
    int nodes;    
    std::getline(inFile, line);
    std::istringstream iss(line);
    iss >> nodes;
    Graph *g = new Graph(nodes, directed);

    // Read edges from the list
    // Format:
    // [from id] [to id] [weight]
    while(std::getline(inFile, line)) {
        std::istringstream iss(line);
        int from, to;
        float weight;
        while(iss >> from >> to >> weight) {
            g->addEdge(from, to, weight);
            // If the graph is undirected, add an edge in the opposite direction as well
            if(!g->isDirected()) g->addEdge(to, from, weight);
        }
    }
    return g;
} 