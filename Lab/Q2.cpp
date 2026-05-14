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
    
    // Helper function for searching (Recursive)
    bool searchRecursive(Node* node, int key) {
        // Base case: node is null (key not found)
        if (node == nullptr) {
            return false;
        }
        
        // Key found
        if (node->data == key) {
            return true;
        }
        
        // Key is smaller, search in left subtree
        if (key < node->data) {
            return searchRecursive(node->left, key);
        }
        
        // Key is larger, search in right subtree
        return searchRecursive(node->right, key);
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
    
    // Public search function
    bool search(int key) {
        return searchRecursive(root, key);
    }
    
    // Iterative search function (alternative implementation)
    bool searchIterative(int key) {
        Node* current = root;
        
        while (current != nullptr) {
            // Key found
            if (current->data == key) {
                return true;
            }
            // Key is smaller, go to left subtree
            else if (key < current->data) {
                current = current->left;
            }
            // Key is larger, go to right subtree
            else {
                current = current->right;
            }
        }
        
        // Key not found
        return false;
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
    
    // Search functionality
    cout << "\n=== Search Feature ===" << endl;
    
    // Test search with existing keys
    int searchKeys[] = {50, 30, 20, 40, 60, 70, 80};
    cout << "\nSearching for existing keys:" << endl;
    for (int key : searchKeys) {
        bool found = bst.search(key);
        cout << "Search(" << key << "): " << (found ? "FOUND" : "NOT FOUND") << endl;
    }
    
    // Test search with non-existing keys
    int notFoundKeys[] = {10, 25, 35, 55, 75, 90, 100};
    cout << "\nSearching for non-existing keys:" << endl;
    for (int key : notFoundKeys) {
        bool found = bst.search(key);
        cout << "Search(" << key << "): " << (found ? "FOUND" : "NOT FOUND") << endl;
    }
    
    // Interactive search
    cout << "\n=== Interactive Search ===" << endl;
    char choice;
    do {
        int key;
        cout << "\nEnter a number to search (or -1 to exit): ";
        cin >> key;
        
        if (key == -1) break;
        
        bool found = bst.search(key);
        
        if (found) {
            cout << "✓ Contact with ID " << key << " FOUND in the directory!" << endl;
        } else {
            cout << "✗ Contact with ID " << key << " NOT FOUND in the directory." << endl;
        }
        
        cout << "Continue searching? (y/n): ";
        cin >> choice;
        
    } while (choice == 'y' || choice == 'Y');
    
    cout << "\n=== Search Complexity ===" << endl;
    cout << "Time Complexity:" << endl;
    cout << "  - Best Case: O(log n) - Balanced tree" << endl;
    cout << "  - Worst Case: O(n) - Skewed tree" << endl;
    cout << "  - Average Case: O(log n)" << endl;
    cout << "Space Complexity: O(h) for recursive, O(1) for iterative" << endl;
    cout << "  where h = height of tree" << endl;
    
    return 0;
}