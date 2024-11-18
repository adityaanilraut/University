#include "bst.h"
#include <queue>
#include <cmath>

// Node constructor
Bst::Node::Node(string value) : m_value(value), m_left(nullptr), m_right(nullptr) {}

// Node destructor
Bst::Node::~Node() {
    delete m_left;
    delete m_right;
}

// BST constructor
Bst::Bst() : m_root(nullptr), m_count(0) {}

// BST destructor
Bst::~Bst() {
    delete m_root;
}

// Helper function for insert
bool insertHelper(string value, Bst::Node*& root) {
    if (root == nullptr) {
        root = new Bst::Node(value);
        return true;
    }
    
    if (value < root->m_value) {
        return insertHelper(value, root->m_left);
    } else if (value > root->m_value) {
        return insertHelper(value, root->m_right);
    }
    return false;  // Value already exists
}

bool Bst::insert(string value) {
    bool result = insertHelper(value, m_root);
    if (result) {
        m_count++;
    }
    return result;
}

// Helper function for find
bool findHelper(string value, Bst::Node* root) {
    if (root == nullptr) {
        return false;
    }
    
    if (value == root->m_value) {
        return true;
    }
    
    if (value < root->m_value) {
        return findHelper(value, root->m_left);
    }
    return findHelper(value, root->m_right);
}

bool Bst::find(string value) {
    return findHelper(value, m_root);
}

// Helper function for depth-first traversal
void dftHelper(Bst::Node* root, vector<string>& values) {
    if (root == nullptr) {
        return;
    }
    
    dftHelper(root->m_left, values);
    values.push_back(root->m_value);
    dftHelper(root->m_right, values);
}

void Bst::dft(vector<string>& values) {
    values.clear();
    dftHelper(m_root, values);
}

void Bst::bft(vector<string>& values) {
    values.clear();
    if (m_root == nullptr) {
        return;
    }
    
    queue<Node*> q;
    q.push(m_root);
    
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        
        values.push_back(current->m_value);
        
        if (current->m_left != nullptr) {
            q.push(current->m_left);
        }
        if (current->m_right != nullptr) {
            q.push(current->m_right);
        }
    }
}

// Helper function for getHeight
int getHeightHelper(Bst::Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + max(getHeightHelper(root->m_left), getHeightHelper(root->m_right));
}

int Bst::getHeight() {
    return getHeightHelper(m_root);
}

// Helper function for isBalanced
bool isBalancedHelper(Bst::Node* root) {
    if (root == nullptr) {
        return true;
    }
    
    int leftHeight = getHeightHelper(root->m_left);
    int rightHeight = getHeightHelper(root->m_right);
    
    return abs(leftHeight - rightHeight) <= 1 && 
           isBalancedHelper(root->m_left) && 
           isBalancedHelper(root->m_right);
}

bool Bst::isBalanced() {
    return isBalancedHelper(m_root);
}

void Bst::insertFromVector(vector<string>& values, int start, int end) {
    if (start > end) {
        return;
    }
    
    int mid = (start + end) / 2;
    insert(values[mid]);
    
    insertFromVector(values, start, mid - 1);
    insertFromVector(values, mid + 1, end);
}

void Bst::rebalance() {
    vector<string> values;
    dft(values);
    
    delete m_root;
    m_root = nullptr;
    m_count = 0;
    
    if (!values.empty()) {
        insertFromVector(values, 0, values.size() - 1);
    }
}

int Bst::getCount() {
    return m_count;
}