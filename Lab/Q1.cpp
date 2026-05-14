#include <iostream>
using namespace std;

// Node structure for BST
class Node {
public:
    int data;
    Node* left;
    Node* right;
    
    // Constructor
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Binary Search Tree class
class BinarySearchTree {
private:
    Node* root;
    
    // Helper function for insertion
    Node* insertRecursive(Node* node, int data) {
        // If tree is empty, create new node
        if (node == nullptr) {
            return new Node(data);
        }
        
        // Otherwise, recur down the tree
        if (data < node->data) {
            node->left = insertRecursive(node->left, data);
        }
        else if (data > node->data) {
            node->right = insertRecursive(node->right, data);
        }
        
        return node;
    }
    
    // Helper function for Inorder traversal (Left -> Root -> Right)
    void inorderRecursive(Node* node) {
        if (node != nullptr) {
            inorderRecursive(node->left);
            cout << node->data << " ";
            inorderRecursive(node->right);
        }
    }
    
    // Helper function for Preorder traversal (Root -> Left -> Right)
    void preorderRecursive(Node* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preorderRecursive(node->left);
            preorderRecursive(node->right);
        }
    }
    
    // Helper function for Postorder traversal (Left -> Right -> Root)
    void postorderRecursive(Node* node) {
        if (node != nullptr) {
            postorderRecursive(node->left);
            postorderRecursive(node->right);
            cout << node->data << " ";
        }
    }
    
public:
    // Constructor
    BinarySearchTree() {
        root = nullptr;
    }
    
    // Public insert function
    void insert(int data) {
        root = insertRecursive(root, data);
        cout << "Inserted: " << data << endl;
    }
    
    // Public Inorder traversal function
    void inorderTraversal() {
        cout << "\nInorder Traversal (Left-Root-Right): ";
        inorderRecursive(root);
        cout << endl;
    }
    
    // Public Preorder traversal function
    void preorderTraversal() {
        cout << "Preorder Traversal (Root-Left-Right): ";
        preorderRecursive(root);
        cout << endl;
    }
    
    // Public Postorder traversal function
    void postorderTraversal() {
        cout << "Postorder Traversal (Left-Right-Root): ";
        postorderRecursive(root);
        cout << endl;
    }
    
    // Display tree structure
    void displayTree(Node* node, string indent = "", bool isRight = true) {
        if (node != nullptr) {
            cout << indent;
            if (isRight) {
                cout << "R----";
                indent += "     ";
            } else {
                cout << "L----";
                indent += "|    ";
            }
            cout << node->data << endl;
            
            displayTree(node->left, indent, false);
            displayTree(node->right, indent, true);
        }
    }
    
    void display() {
        cout << "\nTree Structure:" << endl;
        if (root != nullptr) {
            cout << "Root: " << root->data << endl;
            displayTree(root->left, "", false);
            displayTree(root->right, "", true);
        }
    }
};

int main() {
    BinarySearchTree bst;
    
    // Given sequence: 50, 30, 70, 20, 40, 60, 80
    cout << "=== Binary Search Tree Implementation ===" << endl;
    cout << "\nInserting elements: 50, 30, 70, 20, 40, 60, 80\n" << endl;
    
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    
    // Display tree structure
    bst.display();
    
    cout << "\n=== Tree Traversals ===" << endl;
    
    // Perform all three traversals
    bst.inorderTraversal();
    bst.preorderTraversal();
    bst.postorderTraversal();
    
    cout << "\n=== Explanation ===" << endl;
    cout << "Inorder: Gives sorted sequence (ascending order)" << endl;
    cout << "Preorder: Root is visited first, useful for copying tree" << endl;
    cout << "Postorder: Root is visited last, useful for deleting tree" << endl;
    
    return 0;
}