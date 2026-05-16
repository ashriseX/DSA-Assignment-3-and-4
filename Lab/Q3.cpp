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
    
    // Helper function to find minimum value node (leftmost node)
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    // Helper function for deleting a node
    Node* deleteRecursive(Node* node, int key) {
        // Base case: tree is empty
        if (node == nullptr) {
            return nullptr;
        }
        
        // Traverse to find the node to delete
        if (key < node->data) {
            node->left = deleteRecursive(node->left, key);
        }
        else if (key > node->data) {
            node->right = deleteRecursive(node->right, key);
        }
        else {
            // Node found! Now handle three cases
            
            // Case 1: Node has no children (leaf node)
            if (node->left == nullptr && node->right == nullptr) {
                cout << "  Deleting leaf node: " << node->data << endl;
                delete node;
                return nullptr;
            }
            
            // Case 2a: Node has only right child
            else if (node->left == nullptr) {
                cout << "  Node " << node->data << " has only right child" << endl;
                Node* temp = node->right;
                delete node;
                return temp;
            }
            
            // Case 2b: Node has only left child
            else if (node->right == nullptr) {
                cout << "  Node " << node->data << " has only left child" << endl;
                Node* temp = node->left;
                delete node;
                return temp;
            }
            
            // Case 3: Node has two children
            else {
                cout << "  Node " << node->data << " has two children" << endl;
                
                // Find inorder successor (smallest in right subtree)
                Node* successor = findMin(node->right);
                cout << "  Inorder successor is: " << successor->data << endl;
                
                // Copy successor's data to this node
                node->data = successor->data;
                
                // Delete the successor
                node->right = deleteRecursive(node->right, successor->data);
            }
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
    
    // Public delete function
    void deleteNode(int key) {
        cout << "\n--- Deleting Employee ID: " << key << " ---" << endl;
        
        // Check if node exists
        if (!search(key)) {
            cout << "Employee ID " << key << " not found in the system!" << endl;
            return;
        }
        
        root = deleteRecursive(root, key);
        cout << "Employee ID " << key << " successfully removed!" << endl;
    }
    
    // Public search function
    bool search(int key) {
        return searchRecursive(root, key);
    }
    
    // Public Inorder traversal function
    void inorderTraversal() {
        cout << "Inorder Traversal: ";
        inorderRecursive(root);
        cout << endl;
    }
    
    // Public Preorder traversal function
    void preorderTraversal() {
        cout << "Preorder Traversal: ";
        preorderRecursive(root);
        cout << endl;
    }
    
    // Public Postorder traversal function
    void postorderTraversal() {
        cout << "Postorder Traversal: ";
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
        } else {
            cout << "Tree is empty!" << endl;
        }
    }
};

int main() {
    BinarySearchTree bst;
    
    cout << "=====================================" << endl;
    cout << "   Employee Management System (BST)  " << endl;
    cout << "=====================================" << endl;
    
    // Given sequence: 50, 30, 70, 20, 40, 60, 80
    cout << "\nInserting Employee IDs: 50, 30, 70, 20, 40, 60, 80\n" << endl;
    
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    
    cout << "\n=== Original BST ===" << endl;
    bst.display();
    cout << "\nTraversals:" << endl;
    bst.inorderTraversal();
    bst.preorderTraversal();
    bst.postorderTraversal();
    
    // Delete employee 30
    cout << "\n\n=====================================" << endl;
    cout << "Employee 30 is leaving the company..." << endl;
    cout << "=====================================" << endl;
    
    bst.deleteNode(30);
    
    cout << "\n=== Updated BST (After Deleting 30) ===" << endl;
    bst.display();
    cout << "\nTraversals:" << endl;
    bst.inorderTraversal();
    bst.preorderTraversal();
    bst.postorderTraversal();
    
    // Demonstrate all three deletion cases
    cout << "\n\n=====================================" << endl;
    cout << "   Demonstrating All Delete Cases   " << endl;
    cout << "=====================================" << endl;
    
    // Case 1: Delete leaf node (20)
    cout << "\n--- CASE 1: Delete Leaf Node (Employee 20) ---" << endl;
    bst.deleteNode(20);
    bst.display();
    bst.inorderTraversal();
    
    // Case 2: Delete node with one child (70)
    cout << "\n--- CASE 2: Delete Node with One Child (Employee 70) ---" << endl;
    bst.deleteNode(70);
    bst.display();
    bst.inorderTraversal();
    
    // Case 3: Delete node with two children (50 - root)
    cout << "\n--- CASE 3: Delete Node with Two Children (Employee 50 - Root) ---" << endl;
    bst.deleteNode(50);
    bst.display();
    bst.inorderTraversal();
    
    // Try to delete non-existing employee
    cout << "\n--- Attempting to Delete Non-Existing Employee (100) ---" << endl;
    bst.deleteNode(100);
    
    cout << "\n=== Final BST ===" << endl;
    bst.display();
    bst.inorderTraversal();
    
    cout << "\n\n=====================================" << endl;
    cout << "   Delete Operation Complexity       " << endl;
    cout << "=====================================" << endl;
    cout << "Time Complexity:" << endl;
    cout << "  - Best Case: O(log n)" << endl;
    cout << "  - Worst Case: O(n)" << endl;
    cout << "  - Average Case: O(log n)" << endl;
    cout << "\nThree Cases of Deletion:" << endl;
    cout << "  1. Leaf Node: Simply remove" << endl;
    cout << "  2. One Child: Replace with child" << endl;
    cout << "  3. Two Children: Replace with inorder successor" << endl;
    
    return 0;
}