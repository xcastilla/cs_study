#include <iostream>

struct node {
    int key;
    int height;
    node *left;
    node *right;
    
    node(int key) {
        this->key = key;
        left = nullptr;
        right = nullptr;
        height = 1;
    }

    // Aux function to recursively find the location for insertion
    node* insert_(node* n, int key);

    // Aux function to delete a node from the tree
    node* remove_(node *n, int key);

    // Aux function to recursively delete (free memory) nodes
    void cleanup_(node *n);

    // Returns max height out of the children of a node
    int height_child() const;

    // Auxiliar function to find imbalances in the tree
    // Returns:
    // positive integer if left subtree's height is bigger than right subtree's
    // zero if both subrtrees are equal in height
    // negative integer if right subtree's height is bigger than left subtree's
    int balance() const;

    // Rotation functions used for balancing
    static node* r_rotate(node *n);
    static node* l_rotate(node *n);

    // Get the predecessor of a node in inorder
    node* predecessor();

    // Preorder print of the tree
    friend std::ostream& operator <<(std::ostream& oss, const node& other) {
        oss << other.key << std::endl;
        if(other.left != nullptr) oss << *(other.left);
        if(other.right != nullptr) oss << *(other.right);
        return oss;
    }
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    void insert(int key);
    void remove(int key);
    node* search(int key) const;

    friend std::ostream& operator <<(std::ostream& oss, const AVLTree& other) {
        if(other.root_ != nullptr)
            oss << *(other.root_) << std::endl;
        else
            oss << "<EMPTY>" << std::endl;
        return oss;
    }
private:
    node *root_;
};

AVLTree::AVLTree() {
    root_ = nullptr;
}

AVLTree::~AVLTree() {
    root_->cleanup_(root_);
}

void AVLTree::insert(int key) {
    std::cout << "Inserting " << key << std::endl;
    root_ = root_->insert_(root_, key);
}

void AVLTree::remove(int key) {
    std::cout << "Deleting " << key << std::endl;
    root_ = root_->remove_(root_, key);
}

// Auxiliar function to recursively find the location for the new key and insert it
node* node::insert_(node *n, int key) {
    // If pointer is null, we are at a leaf
    if(n == nullptr) return new node(key);
    // Otherwise, find where to insert the node
    if(key < n->key) {
        n->left = insert_(n->left, key);
    }
    else {
        n->right = insert_(n->right, key);
    }

    // Update n's height
    n->height = n->height_child() + 1;

    // Check for possible imbalances
    int diff = n->balance();
    // If the difference is positive and greater than one the tree is imbalanced on the left
    if(diff > 1) {
        // We need to find wether we need to do a right rotation or a left rotation + right rotation
        if(key < n->left->key) {
            return r_rotate(n);
        }
        else {
            n->left =  l_rotate(n->left);
            return r_rotate(n);
        }

    }
    // The case for right side imbalance is symmetric to the left case
    else if(diff < -1) {
        if(key > n->right->key) {
            return l_rotate(n);
        }
        else {
            n->right = r_rotate(n->right);
            return l_rotate(n);
        }
    }

    return n;
}

node* node::remove_(node *n, int key) {
    if(n == nullptr) return n;
    if(key < n->key) {
        n->left = remove_(n->left, key);
    } 
    else if (key > n->key) {
        n->right = remove_(n->right, key);
    }
    // We found the key!
    else {
        node *l = n->left;
        node *r = n->right;

        // If it doesn't have any child, we delete it
        if(l == nullptr && r == nullptr) {
            delete n;
            return nullptr;
        }
        // if the only child is the right child, we move it up
        else if(l == nullptr) {
            delete n;
            n = r;
        }
        else if(r == nullptr) {
            delete n;
            n = l;
        }
        // If both childs exists, we get the predecessor of the node (the max element in the 
        // left subtree, which at most will have one child - the left one -) copy it's data to the node we wanted 
        // to delete, and remove the leaf instead
        else {
            node* pred = n->predecessor();
            n->key = pred->key;
            n->left = remove_(n->left, pred->key);
        }
    }
    // Update height of n
    n->height = n->height_child() + 1;

    // Now we need to check if deleting the element imbalanced the tree
    if(n->left == nullptr && n->right == nullptr) return n;
    int diff = n->balance();
    // If the difference is positive and greater than one the tree is imbalanced on the left
    if(diff > 1) {
        // We need to find wether we need to do a right rotation or a left rotation + right rotation
        if(n->left->balance() >= 0) {
            return r_rotate(n);
        }
        else {
            n->left =  l_rotate(n->left);
            return r_rotate(n);
        }

    }
    // The case for right side imbalance is symmetric to the left case
    else if(diff < -1) {
        if(n->right->balance() <= 0) {
            return l_rotate(n);
        }
        else {
            n->right = r_rotate(n->right);
            return l_rotate(n);
        }
    }

    return n;
 }

void node::cleanup_(node *n) {
    if(n == nullptr) return;
    cleanup_(n->left);
    cleanup_(n->right);
    delete n;
}

node* node::r_rotate(node *n) {
    std::cout << "R on " << n->key << std::endl;
    node *tmp = n->left;
    n->left = tmp->right;
    tmp->right = n;

    n->height = n->height_child() + 1;
    tmp->height = tmp->height_child() + 1;
    return tmp;
}

node* node::l_rotate(node *n) {
    std::cout << "L on " << n->key << std::endl;
    node *tmp = n->right;
    n->right = tmp->left;
    tmp->left = n;

    n->height = n->height_child() + 1;
    tmp->height = tmp->height_child() + 1;
    return  tmp;
}

node* node::predecessor() {
    // Assumes n has a left child
    node *cur = left;
    while(cur->right != nullptr) {
        cur = cur->right;
    }
    return cur;
}

int node::height_child() const {
    int leftHeight = (left == nullptr) ? 0 : left->height;
    int rightHeight = (right == nullptr) ? 0 : right->height;
    return std::max(leftHeight, rightHeight);
}

int node::balance() const {
    int leftHeight = (left == nullptr) ? 0 : left->height;
    int rightHeight = (right == nullptr) ? 0 : right->height;
    return leftHeight - rightHeight;
}

node* AVLTree::search(int key) const {
    node *loc = root_;
    while(loc != nullptr) {
        if(loc->key == key) return loc;
        else if(key < loc->key) loc = loc->left;
        else loc = loc->right;
    }
    return loc;
}




