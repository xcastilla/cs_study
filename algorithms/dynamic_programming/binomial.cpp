#include <iostream>
#include <vector>

int binomial(int n, int k) {
    assert(n >= 0 && k >= 0);
    assert(n >= k);
    int b[n+1][n+1];
    // Diagonal elements are 1 as there is only one way to choose k elements out of a set of k
    for(int d = 0; d <= n; d++) b[d][d] = 1;
    // All elements where k = 0 are 1, as there is only one way to choose 0 elements out of n
    for(int i = 1; i <= n; i++) b[i][0] = 1;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < i; j++) {
            b[i][j] = b[i-1][j-1] + b[i-1][j];
        }
    }

    return b[n][k];
}

int main() {
    std::cout << "Binomial 5 over 3: " << binomial(5, 3) << std::endl;
    std::cout << "Binomial 4 over 2: " << binomial(4, 2) << std::endl;
    std::cout << "Binomial 3 over 0: " << binomial(3, 0) << std::endl;
    std::cout << "Binomial 2 over 2: " << binomial(2, 2) << std::endl;
    std::cout << "Binomial 0 over 0: " << binomial(0, 0) << std::endl;
}