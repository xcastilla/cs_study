#include <vector>
#include <iostream>

class UnionFindSet {
public:
    UnionFindSet(int nElements);
    int find(int el);
    void merge(int el1, int el2);
    inline bool same_components(int el1, int el2) { return find(el1) == find(el2); }

    friend std::ostream& operator <<(std::ostream& oss, const UnionFindSet& other) {
        oss << "Parent sets:" << std::endl;
        for(int i = 0; i < other.nElements_; i++) {
            oss << "Idx: " << i << ": " << other.parents_[i] << std::endl; 
        }
        oss << "Rank:" << std::endl;
        for(int i = 0; i < other.nElements_ ; i++) {
            oss << "Idx: " << i << ": " << other.rank_[i] << std::endl; 
        }
        return oss;
    }

private:
    std::vector<int> parents_;
    std::vector<int> rank_;
    int nElements_;
};

UnionFindSet::UnionFindSet(int n) {
    // Each element is assigned its own id as set id at startup
    nElements_ = n;
    for(int i = 0; i < nElements_; i++) parents_.push_back(i);
    rank_ = std::vector<int>(nElements_, 1);
}

int UnionFindSet::find(int el) {
    if(el < 0 || el > nElements_ - 1) return -1;
    // Find with path compression
    if(parents_[el] != el) {
        parents_[el] = find(parents_[el]);
    }
    return parents_[el];
}

void UnionFindSet::merge(int el1, int el2) {
    if(el1  < 0 || el2 < 0 || el1 > nElements_ - 1 || el2 > nElements_ - 1) return;

    // Find set ids for el1 and el2
    int s1 = find(el1);
    int s2 = find(el2);

    // If both elements already belong to the same set, we don't need to continue
    if(s1 == s2) return;

    if(rank_[s1] > rank_[s2]) {
        parents_[s2] = s1;
    }
    else if(rank_[s1] < rank_[s2]) {
        parents_[s1] = s2;
    }
    else {
        parents_[s2] = s1;
        rank_[s1]++;
    }

}
