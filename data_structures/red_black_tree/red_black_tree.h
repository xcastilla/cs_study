#include <iostream>

enum class color_t {
    RED,
    BLACK,
    NIL
};

struct node {
    int key;
    color_t color;
    node *left, *right, *parent;
    node(int key, color_t color, node *nil) : key(key), color(color), left(nil), right(nil), parent(nil) { };
    node* left_rotate();
    node* right_rotate();
    node* insert(int key);

    friend std::ostream& operator <<(std::ostream& oss, const node& other) {
        if(other.color != color_t::NIL) {
            oss << other.key << ((other.color == color_t::RED) ? " RED" : " BLACK") << ". Son of: "
                << ((other.parent->color == color_t::NIL) ? "NIL" : std::to_string(other.parent->key)) <<  std::endl;
            if(other.left != nullptr) oss << *(other.left);
            if(other.right != nullptr) oss << *(other.right);
        }
        return oss;
    }
};

class RedBlackTree {
public:
    RedBlackTree() { nil_ = new node(-1, color_t::NIL, nullptr); root_ = nil_; };
    ~RedBlackTree();
    void insert(int key);
    node *find(int key) const;
    node* rightRotate(node *y);
    node* leftRotate(node *x);
    void remove(int key);

    friend std::ostream& operator <<(std::ostream& oss, const RedBlackTree& other) {
        if(other.root_ != nullptr)
            oss << *(other.root_) << std::endl;
        else
            oss << "<EMPTY>" << std::endl;
        return oss;
    }
private:
    node* root_;
    node* nil_;
    void insertFixup_(node* z);
    void transplant_(node* u, node *v);
    node* treeMinimum_(node *x) const;
    void deleteFixup_(node *x);
};

RedBlackTree::~RedBlackTree() {
    delete root_;
}

node* RedBlackTree::rightRotate(node *y) {
    //     y             x
    //    / \           / \
    //   x   d    =>   a   y
    //  / \               / \
    // a   b             b   d
    node *x = y->left;
    y->left = x->right;
    if(x->right != nil_) x->right->parent = y;
    x->parent = y->parent;
    if(y->parent == nil_) {
        root_ = x;
    }
    else {
        if(y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
    return x;
}

node* RedBlackTree::leftRotate(node *x) {
    //     x             y
    //    / \           / \
    //   a   y     =>  x   d
    //      / \       / \
    //     b   d     a   b
    node *y = x->right;
    x->right = y->left;
    if(y->left != nil_) y->left->parent = x;
    y->parent = x->parent;
    if(x->parent == nil_) {
        root_ = y;
    }
    else {
        if(x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return y;
}

node* RedBlackTree::find(int key) const {
    node *x = root_;
    while(x != nil_) {
        if(x->key == key) {
            return x;
        }
        else if(x->key > key) {
            x = x->left;     
        }
        else {
            x = x->right;
        }
    }
    return x;
}

void RedBlackTree::insert(int key) {
    node *pre = nil_;
    node *x = root_;
    while(x != nil_) {
        pre = x;
        if(x->key > key) {
            x = x->left;
        }
        else {
            x = x->right;
        }

    }
    node *z = new node(key, color_t::RED, nil_);
    z->parent = pre;
    if(pre == nil_) {
        root_ = z;
    }
    else if(pre->key > key) {
        pre->left = z;
    }
    else {
        pre->right = z;
    }
    insertFixup_(z);
}

void RedBlackTree::insertFixup_(node *z) {
    while(z->parent->color == color_t::RED) {
        if(z->parent == z->parent->parent->left) {
            node *y = z->parent->parent->right;
            if(y->color == color_t::RED) {
                z->parent->color = color_t::BLACK;
                y->color = color_t::BLACK;
                z->parent->parent->color = color_t::RED;
                z = z->parent->parent;
            }
            else {
                if(z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = color_t::BLACK;
                z->parent->parent->color = color_t::RED;
                rightRotate(z->parent->parent);
            }
        }
        else {
            node *y = z->parent->parent->left;
            if(y == nullptr) return;
            if(y->color == color_t::RED) {
                z->parent->color = color_t::BLACK;
                y->color = color_t::BLACK;
                z->parent->parent->color = color_t::RED;
                z = z->parent->parent;  
            }
            else {
                if(z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = color_t::BLACK;
                z->parent->parent->color = color_t::RED;
                leftRotate(z->parent->parent);
            }
        }
        if(z == root_) break;
    }
    root_->color = color_t::BLACK;
}

void RedBlackTree::transplant_(node *u, node *v) {
    if(u->parent == nil_) {
        root_ = v;
    }
    else if(u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

node* RedBlackTree::treeMinimum_(node* x) const {
    while(x->left != nil_) {
        x = x->left;
    }
    return x;
}

void RedBlackTree::remove(int key) {
    node *z = find(key);
    if(z == nil_) return;
    node *y = z;
    node *x;
    color_t y_original_color = y->color;
    if(z->left == nil_) {
       x = z->right;
       transplant_(z, z->right);
    }
    else if(z->right == nil_) {
        x = z->left;
        transplant_(z, z->left);
    }
    else {
        y = treeMinimum_(z->right);
        y_original_color = y->color;
        x = y->right;
        if(y->parent == z) {
            x->parent = y;
        }
        else {
            transplant_(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant_(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if(y_original_color == color_t::BLACK) {
        deleteFixup_(x);
    }
}

void RedBlackTree::deleteFixup_(node *x) {
    while(x != root_ && x->color == color_t::BLACK) {
        if (x == x->parent->left) {
            node *w = x->parent->right;
            if(w->color == color_t::RED) {
                w->color = color_t::BLACK;
                x->parent->color = color_t::RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if(w->left->color == color_t::BLACK && w->right->color == color_t::BLACK) {
                w->color = color_t::RED;
                x = x->parent;
            }
            else {
                if(w->right->color == color_t::BLACK) {
                    w->left->color = color_t::BLACK;
                    w->color = color_t::RED;
                    rightRotate(w);
                    x = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = color_t::BLACK;
                w->right->color = color_t::BLACK;
                leftRotate(x->parent);
                x = root_;
            }
        }
        else {
            node *w = x->parent->left;
            if(w->color == color_t::RED) {
                w->color = color_t::BLACK;
                x->parent->color = color_t::RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if(w->right->color == color_t::BLACK && w->left->color == color_t::BLACK) {
                w->color = color_t::RED;
                x = x->parent;
            }
            else {
                if(w->left->color == color_t::BLACK) {
                    w->right->color = color_t::BLACK;
                    w->color = color_t::RED;
                    leftRotate(w);
                    x = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = color_t::BLACK;
                w->left->color = color_t::BLACK;
                rightRotate(x->parent);
                x = root_;
            }
        }
    }
    if(x != nil_) {
        x->color = color_t::BLACK;
    }
}

