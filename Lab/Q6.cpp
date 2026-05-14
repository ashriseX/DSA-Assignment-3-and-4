#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
    
    Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;
    
    // Get height of node
    int height(Node* node) {
        return node ? node->height : 0;
    }
    
    // Get balance factor
    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    
    // Update height of node
    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + max(height(node->left), height(node->right));
        }
    }
    
    // Right rotation
    Node* rightRotate(Node* y) {
        cout << "Right rotation on node " << y->data << endl;
        Node* x = y->left;
        Node* T2 = x->right;
        
        // Perform rotation
        x->right = y;
        y->left = T2;
        
        // Update heights
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    // Left rotation
    Node* leftRotate(Node* x) {
        cout << "Left rotation on node " << x->data << endl;
        Node* y = x->right;
        Node* T2 = y->left;
        
        // Perform rotation
        y->left = x;
        x->right = T2;
        
        // Update heights
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    // Insert and balance
    Node* insert(Node* node, int val) {
        // 1. Perform standard BST insertion
        if (!node) {
            cout << "Inserted " << val << endl;
            return new Node(val);
        }
        
        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        else
            return node; // Duplicate values not allowed
        
        // 2. Update height of current node
        updateHeight(node);
        
        // 3. Get balance factor
        int balance = getBalance(node);
        
        // 4. Balance the tree if needed
        
        // Left Left Case
        if (balance > 1 && val < node->left->data) {
            cout << "LL imbalance at node " << node->data << endl;
            return rightRotate(node);
        }
        
        // Right Right Case
        if (balance < -1 && val > node->right->data) {
            cout << "RR imbalance at node " << node->data << endl;
            return leftRotate(node);
        }
        
        // Left Right Case
        if (balance > 1 && val > node->left->data) {
            cout << "LR imbalance at node " << node->data << endl;
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // Right Left Case
        if (balance < -1 && val < node->right->data) {
            cout << "RL imbalance at node " << node->data << endl;
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    // Inorder traversal
    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }
    
    // Print tree structure
    void printTree(Node* node, string indent = "", bool isRight = true) {
        if (node) {
            cout << indent;
            if (isRight) {
                cout << "R----";
                indent += "     ";
            } else {
                cout << "L----";
                indent += "|    ";
            }
            cout << node->data << " (h=" << node->height << ", bf=" << getBalance(node) << ")" << endl;
            
            if (node->left || node->right) {
                printTree(node->left, indent, false);
                printTree(node->right, indent, true);
            }
        }
    }
    
public:
    AVLTree() : root(nullptr) {}
    
    void insert(int val) {
        root = insert(root, val);
        cout << "Current tree structure:" << endl;
        printTree(root);
        cout << endl;
    }
    
    void inorderTraversal() {
        cout << "Inorder: ";
        inorder(root);
        cout << endl;
    }
};

int main() {
    AVLTree tree;
    
    cout << "=== Inserting sequence: 20, 10, 30, 25, 40, 22 ===" << endl << endl;
    
    int sequence[] = {20, 10, 30, 25, 40, 22};
    
    for (int val : sequence) {
        cout << "--- Inserting " << val << " ---" << endl;
        tree.insert(val);
    }
    
    tree.inorderTraversal();
    
    return 0;
}