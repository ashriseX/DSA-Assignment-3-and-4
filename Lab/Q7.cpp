#include <iostream>
#include <algorithm>
#include <iomanip>
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
    
    int height(Node* node) {
        return node ? node->height : 0;
    }
    
    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    
    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + max(height(node->left), height(node->right));
        }
    }
    
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }
    
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }
    
    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        
        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        else
            return node;
        
        updateHeight(node);
        int balance = getBalance(node);
        
        if (balance > 1 && val < node->left->data)
            return rightRotate(node);
        if (balance < -1 && val > node->right->data)
            return leftRotate(node);
        if (balance > 1 && val > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && val < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    // Method 1: Inorder traversal with BF and height
    void printNodeInfo(Node* node) {
        if (node) {
            printNodeInfo(node->left);
            cout << "Node: " << setw(3) << node->data 
                 << " | Height: " << node->height 
                 << " | BF: " << setw(2) << getBalance(node) << endl;
            printNodeInfo(node->right);
        }
    }
    
    // Method 2: Level-order (breadth-first) traversal
    void printLevelOrder(Node* node) {
        if (!node) return;
        
        Node* queue[100];
        int front = 0, rear = 0;
        queue[rear++] = node;
        
        cout << "\n=== Level-Order Traversal ===" << endl;
        while (front < rear) {
            Node* current = queue[front++];
            
            cout << "Node: " << setw(3) << current->data 
                 << " | Height: " << current->height 
                 << " | BF: " << setw(2) << getBalance(current) << endl;
            
            if (current->left) queue[rear++] = current->left;
            if (current->right) queue[rear++] = current->right;
        }
    }
    
    // Method 3: Visual tree with BF and height
    void printVisualTree(Node* node, string indent = "", bool isRight = true) {
        if (node) {
            cout << indent;
            if (isRight) {
                cout << "R----";
                indent += "     ";
            } else {
                cout << "L----";
                indent += "|    ";
            }
            cout << node->data << " [h=" << node->height 
                 << ", bf=" << getBalance(node) << "]" << endl;
            
            if (node->left || node->right) {
                printVisualTree(node->left, indent, false);
                printVisualTree(node->right, indent, true);
            }
        }
    }
    
    // Method 4: Tabular format
    void printTableHeader() {
        cout << "\n" << string(45, '=') << endl;
        cout << "| " << setw(6) << "Node" 
             << " | " << setw(8) << "Height" 
             << " | " << setw(4) << "BF" 
             << " | " << setw(10) << "Balance" << " |" << endl;
        cout << string(45, '=') << endl;
    }
    
    void printTableRow(Node* node) {
        if (node) {
            printTableRow(node->left);
            
            string balanceStatus;
            int bf = getBalance(node);
            if (bf == 0) balanceStatus = "Balanced";
            else if (bf > 0) balanceStatus = "Left-heavy";
            else balanceStatus = "Right-heavy";
            
            cout << "| " << setw(6) << node->data 
                 << " | " << setw(8) << node->height 
                 << " | " << setw(4) << bf 
                 << " | " << setw(10) << balanceStatus << " |" << endl;
            
            printTableRow(node->right);
        }
    }
    
public:
    AVLTree() : root(nullptr) {}
    
    void insert(int val) {
        root = insert(root, val);
    }
    
    // Public interface for printing functions
    void printAllNodeInfo() {
        cout << "\n=== Inorder Traversal (Sorted Order) ===" << endl;
        printNodeInfo(root);
    }
    
    void printLevelOrderInfo() {
        printLevelOrder(root);
    }
    
    void printVisual() {
        cout << "\n=== Visual Tree Structure ===" << endl;
        printVisualTree(root);
    }
    
    void printTable() {
        printTableHeader();
        printTableRow(root);
        cout << string(45, '=') << endl;
    }
};

int main() {
    AVLTree tree;
    
    cout << "Building AVL tree with sequence: 20, 10, 30, 25, 40, 22" << endl;
    
    int sequence[] = {20, 10, 30, 25, 40, 22};
    for (int val : sequence) {
        tree.insert(val);
    }
    
    // Method 1: Inorder traversal
    tree.printAllNodeInfo();
    
    // Method 2: Level-order traversal
    tree.printLevelOrderInfo();
    
    // Method 3: Visual tree
    tree.printVisual();
    
    // Method 4: Table format
    tree.printTable();
    
    return 0;
}