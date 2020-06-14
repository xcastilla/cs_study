#include <iostream>
#include <string>

int edit_distance(std::string s1, std::string s2) {
    // Edit distance can be calculated by the following recurrence
    //                | D[i-1, j-1] if s1[i] == s2[j]; else D[i-1][j-1] + 1 // Match or substitution
    // D[i, j] =  min | D[i-1, j] + 1 // insertion
    //                | D[i, j-1] + 1 // deletion
    int N = s1.size();
    int M = s2.size();
    int D[N+1][M+1];
    for(int i = 0; i <= N; i++) D[i][0] = i;
    for(int j = 0; j <= M; j++) D[0][j] = j;

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            int matchSub;
            if(s1[i] == s2[j]) matchSub = D[i-1][j-1];
            else matchSub = D[i-1][j-1] + 1;
            int ins = D[i-1][j] + 1;
            int sub = D[i][j-1] + 1;

            D[i][j] = std::min(std::min(matchSub, ins), sub);
        }
    }

    return D[N][M];
}



int main() {
    std::string s1 = "elephant";
    std::string s2 = "elefante";
    std::cout << edit_distance(s1, s2) << std::endl;
}