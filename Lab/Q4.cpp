#include <iostream>
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
    
    // Helper function to calculate height of a node
    int heightRecursive(Node* node) {
        // Base case: empty tree has height -1
        // (or you can use 0 for empty tree, depends on convention)
        if (node == nullptr) {
            return -1;
        }
        
        // Calculate height of left and right subtrees
        int leftHeight = heightRecursive(node->left);
        int rightHeight = heightRecursive(node->right);
        
        // Height is 1 + maximum of left and right heights
        return 1 + max(leftHeight, rightHeight);
    }
    
    // Helper function to find a node with given key
    Node* findNode(Node* node, int key) {
        // Base case: node not found
        if (node == nullptr) {
            return nullptr;
        }
        
        // Node found
        if (node->data == key) {
            return node;
        }
        
        // Search in left subtree
        if (key < node->data) {
            return findNode(node->left, key);
        }
        
        // Search in right subtree
        return findNode(node->right, key);
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
    
    // Helper function to display tree with heights
    void displayTreeWithHeight(Node* node, string indent = "", bool isRight = true) {
        if (node != nullptr) {
            cout << indent;
            if (isRight) {
                cout << "R----";
                indent += "     ";
            } else {
                cout << "L----";
                indent += "|    ";
            }
            cout << node->data << " (h=" << heightRecursive(node) << ")" << endl;
            
            displayTreeWithHeight(node->left, indent, false);
            displayTreeWithHeight(node->right, indent, true);
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
    
    // Public function to get height of entire tree
    int height() {
        return heightRecursive(root);
    }
    
    // Public function to get height of a specific node
    int heightOfNode(int key) {
        Node* node = findNode(root, key);
        
        if (node == nullptr) {
            cout << "Node " << key << " not found in the tree!" << endl;
            return -1;
        }
        
        return heightRecursive(node);
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
    
    void displayWithHeights() {
        cout << "\nTree Structure with Heights:" << endl;
        if (root != nullptr) {
            cout << "Root: " << root->data << " (h=" << heightRecursive(root) << ")" << endl;
            displayTreeWithHeight(root->left, "", false);
            displayTreeWithHeight(root->right, "", true);
        } else {
            cout << "Tree is empty!" << endl;
        }
    }
};

int main() {
    BinarySearchTree bst;
    
    cout << "=====================================" << endl;
    cout << "      BST Height Calculation         " << endl;
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
    cout << "        Height Calculations          " << endl;
    cout << "=====================================" << endl;
    
    // Calculate height of entire tree
    int treeHeight = bst.height();
    cout << "\nHeight of entire BST: " << treeHeight << endl;
    
    // Calculate height of node 30
    int height30 = bst.heightOfNode(30);
    cout << "Height of node 30: " << height30 << endl;
    
    // Calculate height of node 60
    int height60 = bst.heightOfNode(60);
    cout << "Height of node 60: " << height60 << endl;
    
    // Calculate heights of all nodes
    cout << "\n=====================================" << endl;
    cout << "      Heights of All Nodes           " << endl;
    cout << "=====================================" << endl;
    
    int nodes[] = {50, 30, 70, 20, 40, 60, 80};
    for (int node : nodes) {
        cout << "Height of node " << node << ": " << bst.heightOfNode(node) << endl;
    }
    
    // Display tree with heights
    bst.displayWithHeights();
    
    // Visual explanation
    cout << "\n=====================================" << endl;
    cout << "      Visual Explanation             " << endl;
    cout << "=====================================" << endl;
    cout << "\nTree Structure:\n" << endl;
    cout << "           50 (h=2)                  " << endl;
    cout << "          /  \\                       " << endl;
    cout << "      30(h=1) 70(h=1)               " << endl;
    cout << "      / \\     / \\                   " << endl;
    cout << "  20(h=0) 40(h=0) 60(h=0) 80(h=0)  " << endl;
    
    cout << "\n=====================================" << endl;
    cout << "      Height Definition              " << endl;
    cout << "=====================================" << endl;
    cout << "\nHeight of a node:" << endl;
    cout << "  = Number of edges on the longest path" << endl;
    cout << "    from that node to a leaf" << endl;
    cout << "\nKey Points:" << endl;
    cout << "  - Leaf nodes have height 0" << endl;
    cout << "  - Empty tree (null) has height -1" << endl;
    cout << "  - Height of tree = height of root" << endl;
    cout << "  - Height = max(leftHeight, rightHeight) + 1" << endl;
    
    cout << "\n=====================================" << endl;
    cout << "      Detailed Calculation           " << endl;
    cout << "=====================================" << endl;
    
    cout << "\nFor Node 30:" << endl;
    cout << "  Left child (20): height = 0 (leaf)" << endl;
    cout << "  Right child (40): height = 0 (leaf)" << endl;
    cout << "  Height of 30 = max(0, 0) + 1 = 1" << endl;
    
    cout << "\nFor Node 60:" << endl;
    cout << "  Left child: NULL" << endl;
    cout << "  Right child: NULL" << endl;
    cout << "  Height of 60 = max(-1, -1) + 1 = 0 (leaf)" << endl;
    
    cout << "\nFor Root (50):" << endl;
    cout << "  Left subtree (30): height = 1" << endl;
    cout << "  Right subtree (70): height = 1" << endl;
    cout << "  Height of 50 = max(1, 1) + 1 = 2" << endl;
    
    cout << "\n=====================================" << endl;
    cout << "      Complexity Analysis            " << endl;
    cout << "=====================================" << endl;
    cout << "\nTime Complexity:" << endl;
    cout << "  - height(): O(n) - visits all nodes" << endl;
    cout << "  - heightOfNode(key): O(n)" << endl;
    cout << "    - O(log n) to find node (average)" << endl;
    cout << "    - O(n) to calculate height" << endl;
    cout << "\nSpace Complexity: O(h)" << endl;
    cout << "  - Due to recursive call stack" << endl;
    cout << "  - h = height of tree" << endl;
    
    return 0;
}