#include <iostream>
#include <vector>
#include <algorithm>
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
    
    // Helper function to store elements in sorted order using inorder traversal
    void storeInorderRecursive(Node* node, vector<int>& arr) {
        if (node == nullptr) {
            return;
        }
        
        // Left -> Root -> Right (Inorder)
        storeInorderRecursive(node->left, arr);
        arr.push_back(node->data);  // Store current node
        storeInorderRecursive(node->right, arr);
    }
    
    // Alternative: Store in array (fixed size)
    void storeInorderArray(Node* node, int arr[], int& index) {
        if (node == nullptr) {
            return;
        }
        
        storeInorderArray(node->left, arr, index);
        arr[index++] = node->data;
        storeInorderArray(node->right, arr, index);
    }
    
    // Helper function to count nodes
    int countNodes(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
    
    // Helper function for Inorder traversal display
    void inorderRecursive(Node* node) {
        if (node != nullptr) {
            inorderRecursive(node->left);
            cout << node->data << " ";
            inorderRecursive(node->right);
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
    
    // Method 1: Store in vector (dynamic array)
    vector<int> toSortedVector() {
        vector<int> sortedArray;
        storeInorderRecursive(root, sortedArray);
        return sortedArray;
    }
    
    // Method 2: Store in fixed array
    void toSortedArray(int arr[], int& size) {
        int index = 0;
        size = countNodes(root);
        storeInorderArray(root, arr, index);
    }
    
    // Get total number of nodes
    int getSize() {
        return countNodes(root);
    }
    
    // Display inorder traversal
    void inorderTraversal() {
        cout << "Inorder Traversal: ";
        inorderRecursive(root);
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

// Utility function to print array
void printArray(int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// Utility function to print vector
void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    BinarySearchTree bst;
    
    cout << "=====================================" << endl;
    cout << "   BST to Sorted Array Conversion   " << endl;
    cout << "=====================================" << endl;
    
    // Given sequence: 50, 30, 70, 20, 40, 60, 80
    cout << "\nInserting elements: 50, 30, 70, 20, 40, 60, 80\n" << endl;
    
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    
    // Display tree
    bst.display();
    
    cout << "\n=====================================" << endl;
    cout << "      Method 1: Using Vector         " << endl;
    cout << "=====================================" << endl;
    
    // Method 1: Store in vector
    vector<int> sortedVector = bst.toSortedVector();
    
    cout << "\nSorted elements stored in vector:" << endl;
    cout << "Vector: ";
    printVector(sortedVector);
    cout << "Size: " << sortedVector.size() << endl;
    
    cout << "\n=====================================" << endl;
    cout << "     Method 2: Using Fixed Array     " << endl;
    cout << "=====================================" << endl;
    
    // Method 2: Store in array
    int size = bst.getSize();
    int* sortedArray = new int[size];
    int arraySize = 0;
    
    bst.toSortedArray(sortedArray, arraySize);
    
    cout << "\nSorted elements stored in array:" << endl;
    cout << "Array: ";
    printArray(sortedArray, arraySize);
    cout << "Size: " << arraySize << endl;
    
    cout << "\n=====================================" << endl;
    cout << "         Verification                " << endl;
    cout << "=====================================" << endl;
    
    cout << "\nOriginal BST (Inorder): ";
    bst.inorderTraversal();
    
    cout << "\nArray representation:   ";
    printArray(sortedArray, arraySize);
    
    cout << "\nBoth are identical? ";
    bool identical = true;
    for (int i = 0; i < arraySize; i++) {
        if (sortedArray[i] != sortedVector[i]) {
            identical = false;
            break;
        }
    }
    cout << (identical ? "YES ✓" : "NO ✗") << endl;
    
    cout << "\n=====================================" << endl;
    cout << "      How It Works                   " << endl;
    cout << "=====================================" << endl;
    
    cout << "\nInorder Traversal Process:" << endl;
    cout << "  Step 1: Traverse left subtree" << endl;
    cout << "  Step 2: Visit current node (store value)" << endl;
    cout << "  Step 3: Traverse right subtree" << endl;
    
    cout << "\nFor our BST:" << endl;
    cout << "           50                  " << endl;
    cout << "          /  \\                " << endl;
    cout << "        30    70               " << endl;
    cout << "       / \\   / \\             " << endl;
    cout << "      20 40 60 80             " << endl;
    
    cout << "\nTraversal Order:" << endl;
    cout << "  1. Go left from 50 → 30" << endl;
    cout << "  2. Go left from 30 → 20" << endl;
    cout << "  3. 20 is leaf, store: [20]" << endl;
    cout << "  4. Back to 30, store: [20, 30]" << endl;
    cout << "  5. Go right from 30 → 40" << endl;
    cout << "  6. 40 is leaf, store: [20, 30, 40]" << endl;
    cout << "  7. Back to 50, store: [20, 30, 40, 50]" << endl;
    cout << "  8. Go right from 50 → 70" << endl;
    cout << "  9. Go left from 70 → 60" << endl;
    cout << "  10. 60 is leaf, store: [20, 30, 40, 50, 60]" << endl;
    cout << "  11. Back to 70, store: [20, 30, 40, 50, 60, 70]" << endl;
    cout << "  12. Go right from 70 → 80" << endl;
    cout << "  13. 80 is leaf, store: [20, 30, 40, 50, 60, 70, 80]" << endl;
    
    cout << "\n=====================================" << endl;
    cout << "      Complexity Analysis            " << endl;
    cout << "=====================================" << endl;
    
    cout << "\nTime Complexity: O(n)" << endl;
    cout << "  - Visit each node exactly once" << endl;
    cout << "  - n = number of nodes in BST" << endl;
    
    cout << "\nSpace Complexity: O(n)" << endl;
    cout << "  - Array/Vector storage: O(n)" << endl;
    cout << "  - Recursive call stack: O(h)" << endl;
    cout << "  - h = height of tree" << endl;
    
    cout << "\n=====================================" << endl;
    cout << "      Use Cases                      " << endl;
    cout << "=====================================" << endl;
    
    cout << "\n1. Reporting: Generate sorted reports" << endl;
    cout << "2. Exporting: Export data in sorted order" << endl;
    cout << "3. Analysis: Statistical analysis on sorted data" << endl;
    cout << "4. Merging: Merge multiple BSTs" << endl;
    cout << "5. Searching: Binary search on sorted array" << endl;
    
    // Additional demonstration: Insert more elements
    cout << "\n=====================================" << endl;
    cout << "   Adding More Elements              " << endl;
    cout << "=====================================" << endl;
    
    cout << "\nInserting: 10, 25, 45, 65, 75, 90\n" << endl;
    bst.insert(10);
    bst.insert(25);
    bst.insert(45);
    bst.insert(65);
    bst.insert(75);
    bst.insert(90);
    
    bst.display();
    
    // Get updated sorted array
    vector<int> updatedVector = bst.toSortedVector();
    cout << "\nUpdated Sorted Array:" << endl;
    printVector(updatedVector);
    cout << "Total elements: " << updatedVector.size() << endl;
    
    // Cleanup
    delete[] sortedArray;
    
    return 0;
}