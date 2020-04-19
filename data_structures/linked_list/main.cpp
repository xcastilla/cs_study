#include "linked_list.h"

int main() {
    list l;
    l.insert(5);
    l.insert(4);
    std::cout << l;
    l.remove(5);
    l.insert(3);
    std::cout << l;
    
    // Synthetic list for loop checking
    node *n1 = new node(1);
    node *n2 = new node(2);
    node *n3 = new node(4);
    node *n4 = new node(4);
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    list l2(n1);
    // There should be no loop at this point
    std::cout << "Is there a loop? -> " << (l2.findLoop() ? "Yes" : "No") << std::endl;
    // There should be a loop after we set n4 to point to n2
    n4->next = n2;
    std::cout << "Is there a loop now? -> " << (l2.findLoop() ? "Yes" : "No") << std::endl;
}
