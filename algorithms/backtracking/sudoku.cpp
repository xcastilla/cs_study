#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>

// Find a solution for a partially complete sudoku.
// Unlike the other programs in this directory, this one 
// finds one solution and quits execution

// Helper data structure containing information about the board
// It comes with some goodies to deal with the board, but it's not 
// really needed since it adds additional complexity and
// we could (and should) operate on the vector of actions directly
struct Board {
    const int side;
    const int boardSize;
    int freePositions;
    std::vector<std::vector<int>> state;

    Board(int side): side(side), boardSize(side * side) {
        for(int i = 0; i < side; i++) {
            state.push_back(std::vector<int>(side, 0));
        }
        freePositions = boardSize;
    }

    void addValue(int i, int j, int value) {
        state[i][j] = value;
        freePositions--;
    }

    // Fill board content for a raveled vector
    void fill(std::vector<int> moves) {
        for(int a = 0; a < moves.size(); a++) {
            // If the number is set in the vector of moves, we add it to the board
            // and decrease the number of free positions in the board
            if(moves[a] != 0) {
                int i = a / side;
                int j = a % side;
                addValue(i, j, moves[a]);
            }
        }
    }
    
    // Pretty print the board
    friend std::ostream& operator <<(std::ostream& oss, const Board& board) {
        oss << "----------------------" << std::endl;
        for(int i = 0; i < board.side; i++) {
            // Left-most vertical separator
            oss << "|";
            for(int j = 0; j < board.side; j++) {
                // If the board state for (i, j) is unset, print it empty instead
                if(board.state[i][j] == 0) oss << "  ";
                else oss << " " << board.state[i][j];
                // Print vertical separators every 3 columns
                if((j + 1) % 3 == 0) oss << "|";
            }
            oss << std::endl;
            // Print horizontal separators every 3 rows
            if((i + 1) % 3 == 0) oss << "----------------------" << std::endl;
        }
        return oss;
    }
};

/* Backtracking related functions from here */

bool solutionState(std::vector<int>& a) {
    Board board(sqrt(a.size()));
    board.fill(a);
    
    return board.freePositions == 0;
}

void processSolution(std::vector<int>& a) {
    Board board(sqrt(a.size()));
    board.fill(a);
    std::cout << board;
}

// Checks if the value of (i, j) is valid in the current configuration of the board
bool isValidConfiguration(int k, std::vector<int> a)  {
    Board board(sqrt(a.size()));
    board.fill(a);

    int i = k / board.side;
    int j = k % board.side;

    // Check row configuration
    for(int col = 0; col < board.side; col++) {
        if(col != j) {
            if(board.state[i][col] == board.state[i][j]) {
                return false;
            } 
        }
    }

    // Check column configuration
    for(int row = 0; row < board.side; row++) {
        if(row != i) {
            if(board.state[row][j] == board.state[i][j]) {
                return false;
            } 
        }
    }

    // Check subboard configuration
    int subI = 3 * (i / 3);
    int subJ = 3 * (j / 3);
    for(int row = subI; row < std::min(subI + 3, board.side); row++) {
        for(int col = subJ; col < std::min(subJ + 3, board.side); col++) {
            if((row != i || col != j) && board.state[row][col] == board.state[i][j]) {
                return false;
            }
        }
    }

    return true;
}

std::vector<int> generateCandidates(int k, std::vector<int> a) {
    std::vector<int> candidates;
    for(int c = 1; c <= sqrt(a.size()); c++) {
        a[k] = c;
        if(isValidConfiguration(k, a)) {
            candidates.push_back(c);
        }
    }
    return candidates;
}

bool backtrack(int k, std::vector<int> a) {
    if(solutionState(a)){
        processSolution(a);
        return true;
    }
    else {
        // If the position was filled in the initial board, skip it
        if(a[k] != 0) {
            return backtrack(k + 1, a);
        }
        std::vector<int> candidates = generateCandidates(k, a);
        for(int c: candidates) {
            a[k] = c;
            if(backtrack(k + 1, a)) {
                return true;
            }
        }   
    }
    return false;
}

int main(int argc, char* argv[]) {
    // Read the initial state of the board from a file
    if(argc != 2) {
        std::cerr << "Usage: sudoku [INPUT_FILE]" << std::endl;
        std::cerr << "e.g: sudoku assets/sudoku" << std::endl;
        exit(1);
    }

    std::ifstream inFile;
    inFile.open(argv[1]);
    if(!inFile) {
        std::cerr << "Path: " << argv[1] << " could not be opened." << std::endl;
        exit(1);
    }

    std::string line;
    int side;    
    std::getline(inFile, line);
    std::istringstream iss(line);
    iss >> side;
    std::vector<int> a(side * side, 0);

    int pos = 0;
    while(std::getline(inFile, line)) {
        std::istringstream iss(line);
        int num;
        while(iss >> num){
            a[pos] = num;
            pos++;
        }
    }

    // Pretty print the initial state
    std::cout << "Intial state:" << std::endl;
    Board b(sqrt(a.size()));
    b.fill(a);
    std::cout << b;

    // Solve the board
    std::cout << "SOLUTION:" << std::endl;
    if(!backtrack(0, a)) {
        std::cout << "Failed to find a solution" << std::endl;
    }
}