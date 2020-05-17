#include "union_find_set.h"

int main() {
    UnionFindSet ufSet = UnionFindSet(5);
    std::cout << ufSet;
    ufSet.merge(0, 4);
    std::cout << ufSet;
    ufSet.merge(4, 3);
    std::cout << ufSet;
}
