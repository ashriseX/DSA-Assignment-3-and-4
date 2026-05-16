#include <iostream>
#include <algorithm>
using namespace std;

// Node structure for AVL Tree
struct Node {
    int score;
    Node* left;
    Node* right;
    int height;
    
    Node(int s) : score(s), left(nullptr), right(nullptr), height(1) {}
};

// AVL Tree class for gaming scores
class AVLTree {
private:
    Node* root;
    
    // Get height of node
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }
    
    // Get balance factor of node
    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    
    // Update height of node
    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }
    
    // Right rotation
    Node* rotateRight(Node* y) {
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
    Node* rotateLeft(Node* x) {
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
    
    // Insert a score (recursive)
    Node* insert(Node* node, int score) {
        // 1. Perform normal BST insertion
        if (!node) {
            return new Node(score);
        }
        
        if (score < node->score) {
            node->left = insert(node->left, score);
        } else if (score > node->score) {
            node->right = insert(node->right, score);
        } else {
            // Duplicate scores allowed - insert to right
            node->right = insert(node->right, score);
        }
        
        // 2. Update height of current node
        updateHeight(node);
        
        // 3. Get balance factor
        int balance = getBalance(node);
        
        // 4. Balance the tree if needed
        
        // Left-Left Case
        if (balance > 1 && score < node->left->score) {
            return rotateRight(node);
        }
        
        // Right-Right Case
        if (balance < -1 && score > node->right->score) {
            return rotateLeft(node);
        }
        
        // Left-Right Case
        if (balance > 1 && score > node->left->score) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right-Left Case
        if (balance < -1 && score < node->right->score) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    // Find node with minimum value
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left) {
            current = current->left;
        }
        return current;
    }
    
    // Delete a score (recursive)
    Node* deleteNode(Node* node, int score) {
        // 1. Perform standard BST delete
        if (!node) {
            return node;
        }
        
        if (score < node->score) {
            node->left = deleteNode(node->left, score);
        } else if (score > node->score) {
            node->right = deleteNode(node->right, score);
        } else {
            // Node with one child or no child
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                
                if (!temp) {
                    // No child case
                    temp = node;
                    node = nullptr;
                } else {
                    // One child case
                    *node = *temp;
                }
                delete temp;
            } else {
                // Node with two children
                Node* temp = minValueNode(node->right);
                node->score = temp->score;
                node->right = deleteNode(node->right, temp->score);
            }
        }
        
        if (!node) {
            return node;
        }
        
        // 2. Update height
        updateHeight(node);
        
        // 3. Get balance factor
        int balance = getBalance(node);
        
        // 4. Balance the tree if needed
        
        // Left-Left Case
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }
        
        // Left-Right Case
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right-Right Case
        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }
        
        // Right-Left Case
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    // Reverse in-order traversal (right -> root -> left) for top scores
    void reverseInOrder(Node* node) {
        if (!node) {
            return;
        }
        
        // Visit right subtree first (higher scores)
        reverseInOrder(node->right);
        
        // Print current node
        cout << node->score << " ";
        
        // Visit left subtree (lower scores)
        reverseInOrder(node->left);
    }
    
    // Helper function to destroy tree
    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr) {}
    
    ~AVLTree() {
        destroyTree(root);
    }
    
    // Insert a score
    void insertScore(int score) {
        root = insert(root, score);
        cout << "Inserted score: " << score << endl;
    }
    
    // Remove a score
    void removeScore(int score) {
        root = deleteNode(root, score);
        cout << "Removed score: " << score << endl;
    }
    
    // Print top scores (highest to lowest)
    void printTopScores() {
        cout << "Top Scores (Highest to Lowest): ";
        if (!root) {
            cout << "No scores available";
        } else {
            reverseInOrder(root);
        }
        cout << endl;
    }
    
    // Utility function to check if tree is empty
    bool isEmpty() {
        return root == nullptr;
    }
};

// Main function to demonstrate the gaming platform
int main() {
    AVLTree scoreboard;
    
    cout << "=== Gaming Platform Score System ===" << endl << endl;
    
    // Insert player scores
    cout << "--- Adding Player Scores ---" << endl;
    scoreboard.insertScore(1500);
    scoreboard.insertScore(2000);
    scoreboard.insertScore(1200);
    scoreboard.insertScore(1800);
    scoreboard.insertScore(2500);
    scoreboard.insertScore(1000);
    scoreboard.insertScore(2200);
    scoreboard.insertScore(1600);
    
    cout << endl;
    scoreboard.printTopScores();
    
    // More insertions
    cout << endl << "--- More Players Joining ---" << endl;
    scoreboard.insertScore(3000);
    scoreboard.insertScore(2800);
    scoreboard.insertScore(900);
    
    cout << endl;
    scoreboard.printTopScores();
    
    // Remove some scores
    cout << endl << "--- Players Leaving ---" << endl;
    scoreboard.removeScore(1200);
    scoreboard.removeScore(2500);
    scoreboard.removeScore(1000);
    
    cout << endl;
    scoreboard.printTopScores();
    
    // Add more scores
    cout << endl << "--- New Players Joining ---" << endl;
    scoreboard.insertScore(2700);
    scoreboard.insertScore(1400);
    
    cout << endl;
    scoreboard.printTopScores();
    
    cout << endl << "=== Session Complete ===" << endl;
    
    return 0;
}