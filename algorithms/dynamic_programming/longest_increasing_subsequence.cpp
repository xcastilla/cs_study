#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

// We can pose the problem as the following recurrence
// Given seq, a sequence of elements
// Let len_i be the length of the longest subsequence up to the ith elemen in seq
// We can calculate len_i as the maximum len_j for 0 < j < i, where seq_j < seq_i
std::vector<int> LIS(std::vector<int> seq) {
    std::vector<int> len(seq.size(), 0);
    std::vector<int> predecessor(seq.size(), 0);
    len[0] = 1;
    predecessor[0] = -1;
    for(int i = 1; i < seq.size(); i++) {
        int maxLen = 0;
        int pred = -1;
        for(int j = 0; j < i; j++) {
            if(seq[j] < seq[i]) {
                if(len[j] > maxLen) {
                    maxLen = len[j];
                    pred = j;
                }
            }
        }
        len[i] = maxLen + 1;
        predecessor[i] = pred;
    }
    // Create longest increasing sequence out of the predecessors vector
    int idx = std::distance(len.begin(), std::max_element(len.begin(), len.end()));
    std::vector<int> longestSeq;
    while(idx != -1) {
        longestSeq.push_back(seq[idx]);
        idx = predecessor[idx];
    }
    std::reverse(longestSeq.begin(), longestSeq.end());
    return longestSeq;
}

int main() {
    std::vector<int> seq = {2, -1, 0, 3, 5, 1, 7, 6, 9 , 7, 11};
    std::vector<int> longestSeq = LIS(seq);

    std::cout << "Length of longest subsequence: " << longestSeq.size() << std::endl;
    for(int elem: longestSeq) {
        std::cout << " " << elem;
    }
    std::cout << std::endl;
}