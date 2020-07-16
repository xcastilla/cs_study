#include "red_black_tree.h"

int main() {
    RedBlackTree l;
    l.insert(6);
    l.insert(4);
    l.insert(5);
    l.insert(2);
    l.insert(0);
    l.insert(-1);
    l.insert(8);
    l.insert(10);
    l.insert(7);
    std::cout << l;
    std::cout << "-----" << std::endl;
    l.remove(6);
    l.remove(8);
    l.remove(10);
    std::cout << l;
    std::cout << "-----" << std::endl;
    // Shouldn't be there
    l.remove(6);
    std::cout << l;
    std::cout << "-----" << std::endl;
    l.remove(-1);
    l.remove(2);
    std::cout << l;
    std::cout << "-----" << std::endl;
    l.remove(7);
    l.remove(5);
    l.remove(4);
    l.remove(0);
    std::cout << l;

     
}
