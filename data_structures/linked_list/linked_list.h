#include <iostream>

struct node {
    int key;
    node* next;
    node(int v): key(v), next(nullptr) {};
};

// Unsorted singly linked list
class list {
public:
    list() : head_(nullptr) {};
    // Initialize from node
    list(node *head) : head_(head) {};
    // Find the first node with key v
    node* search(int v) const;
    // Insert a new node with key v
    void insert(int v);
    // Remove the first node with value v
    void remove(int v);
    // Returns a boolean indicating the presence of a loop in the list
    bool findLoop() const;

    friend std::ostream& operator <<(std::ostream& oss, const list& other) {
        node* p = other.head_;
        while(p != nullptr) {
            oss << p->key << std::endl;
            p = p->next;
        }
        oss << "<EOList>" << std::endl;
        return oss;
    }
private:
    node *head_;
};

node* list::search(int v) const {
    node* p = head_;
    while(p != nullptr) {
        if(p->key == v) return p;
        p = p->next;
    }
    return p;
}

void list::insert(int v) {
    node* n = new node(v);
    n->next = head_;
    head_ = n;
}

void list::remove(int v) {
    if(head_ == nullptr) return;
    // Two pointers to store the current item being checked
    // and its predecessor
    node *curr = head_;
    node *prev = nullptr;
    while(curr!= nullptr && curr->key != v) {
        prev = curr;
        curr = curr->next;
    }
    // If we are at EOList
    if(curr == nullptr) return;

    // Item has been found
    prev->next = curr->next;
    delete curr;
}


bool list::findLoop() const {
    node *skip1, *skip2;
    skip1 = head_;
    skip2 = skip1->next;
    // The idea is that we move skip2 by 2 positions at a time, and skip1 by only 1
    // If there is a loop, at some point both pointers will be pointing at the same node
    while(skip2 != nullptr) {
        if(skip1->key == skip2->key) return true;
        else if(skip2->next == nullptr) return false;
        skip1 = skip1->next;
        skip2 = skip2->next->next;
    }
    return false;
}




