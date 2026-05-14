#include <iostream>
#include <algorithm>
using namespace std;

class AVLNode {
public:
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;
    
    // Get height of node
    int height(AVLNode* node) {
        return node ? node->height : 0;
    }
    
    // Get balance factor
    int getBalance(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    
    // Update height of node
    void updateHeight(AVLNode* node) {
        if (node) {
            node->height = 1 + max(height(node->left), height(node->right));
        }
    }
    
    // Right rotation
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        // Perform rotation
        x->right = y;
        y->left = T2;
        
        // Update heights
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    // Left rotation
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        // Perform rotation
        y->left = x;
        x->right = T2;
        
        // Update heights
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    // Insert helper
    AVLNode* insertHelper(AVLNode* node, int key) {
        // Standard BST insertion
        if (!node) return new AVLNode(key);
        
        if (key < node->key)
            node->left = insertHelper(node->left, key);
        else if (key > node->key)
            node->right = insertHelper(node->right, key);
        else
            return node; // Duplicate keys not allowed
        
        // Update height
        updateHeight(node);
        
        // Get balance factor
        int balance = getBalance(node);
        
        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);
        
        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);
        
        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    // Find minimum value node
    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left)
            current = current->left;
        return current;
    }
    
    // Delete helper
    AVLNode* deleteHelper(AVLNode* node, int key) {
        // Standard BST deletion
        if (!node) return node;
        
        if (key < node->key) {
            node->left = deleteHelper(node->left, key);
        }
        else if (key > node->key) {
            node->right = deleteHelper(node->right, key);
        }
        else {
            // Node with only one child or no child
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                
                if (!temp) {
                    // No child case
                    temp = node;
                    node = nullptr;
                } else {
                    // One child case
                    *node = *temp;
                }
                delete temp;
            }
            else {
                // Node with two children: get inorder successor
                AVLNode* temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = deleteHelper(node->right, temp->key);
            }
        }
        
        if (!node) return node;
        
        // Update height
        updateHeight(node);
        
        // Get balance factor
        int balance = getBalance(node);
        
        // Left Left Case
        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);
        
        // Left Right Case
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right Right Case
        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);
        
        // Right Left Case
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    // Inorder traversal helper
    void inorderHelper(AVLNode* node) {
        if (node) {
            inorderHelper(node->left);
            cout << node->key << " ";
            inorderHelper(node->right);
        }
    }
    
    // Print tree structure helper
    void printTreeHelper(AVLNode* node, string prefix, bool isLeft) {
        if (node) {
            cout << prefix;
            cout << (isLeft ? "├──" : "└──");
            cout << node->key << " (h=" << node->height << ", bf=" << getBalance(node) << ")" << endl;
            
            if (node->left || node->right) {
                if (node->left)
                    printTreeHelper(node->left, prefix + (isLeft ? "│   " : "    "), true);
                else {
                    cout << prefix + (isLeft ? "│   " : "    ") << "├──(null)" << endl;
                }
                
                if (node->right)
                    printTreeHelper(node->right, prefix + (isLeft ? "│   " : "    "), false);
                else {
                    cout << prefix + (isLeft ? "│   " : "    ") << "└──(null)" << endl;
                }
            }
        }
    }
    
public:
    AVLTree() : root(nullptr) {}
    
    void insert(int key) {
        root = insertHelper(root, key);
    }
    
    void remove(int key) {
        root = deleteHelper(root, key);
    }
    
    void inorder() {
        inorderHelper(root);
        cout << endl;
    }
    
    void printTree() {
        if (root) {
            printTreeHelper(root, "", false);
        } else {
            cout << "(empty tree)" << endl;
        }
        cout << endl;
    }
};

int main() {
    AVLTree tree;
    
    cout << "=== Inserting: 50, 30, 70, 20, 40, 60, 80 ===" << endl << endl;
    
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int val : values) {
        cout << "Inserting " << val << ":" << endl;
        tree.insert(val);
        tree.printTree();
    }
    
    cout << "Inorder traversal: ";
    tree.inorder();
    
    cout << "\n=== Deleting: 30, 70 ===" << endl << endl;
    
    cout << "Deleting 30:" << endl;
    tree.remove(30);
    tree.printTree();
    
    cout << "Inorder traversal: ";
    tree.inorder();
    
    cout << "\nDeleting 70:" << endl;
    tree.remove(70);
    tree.printTree();
    
    cout << "Final inorder traversal: ";
    tree.inorder();
    
    return 0;
}