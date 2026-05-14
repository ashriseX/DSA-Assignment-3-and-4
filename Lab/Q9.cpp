#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// Node structure for BST/AVL Tree
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;  // For AVL tree
    
    Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

class BSTtoAVL {
private:
    // Helper function to get height of node
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }
    
    // Helper function to update height of node
    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }
    
    // Get balance factor of node
    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
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
        
        return x;  // New root
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
        
        return y;  // New root
    }
    
    // Store inorder traversal in vector
    void storeInorder(Node* root, vector<int>& inorder) {
        if (!root) return;
        
        storeInorder(root->left, inorder);
        inorder.push_back(root->data);
        storeInorder(root->right, inorder);
    }
    
    // Build balanced AVL tree from sorted array
    Node* buildBalancedAVL(vector<int>& arr, int start, int end) {
        if (start > end) return nullptr;
        
        // Choose middle element as root
        int mid = start + (end - start) / 2;
        Node* root = new Node(arr[mid]);
        
        // Recursively build left and right subtrees
        root->left = buildBalancedAVL(arr, start, mid - 1);
        root->right = buildBalancedAVL(arr, mid + 1, end);
        
        // Update height
        updateHeight(root);
        
        return root;
    }
    
    // Alternative: Convert in-place using AVL insertions
    Node* insertAVL(Node* node, int data) {
        // Standard BST insertion
        if (!node) return new Node(data);
        
        if (data < node->data)
            node->left = insertAVL(node->left, data);
        else if (data > node->data)
            node->right = insertAVL(node->right, data);
        else
            return node;  // Duplicate values not allowed
        
        // Update height
        updateHeight(node);
        
        // Get balance factor
        int balance = getBalance(node);
        
        // Left Left Case
        if (balance > 1 && data < node->left->data)
            return rotateRight(node);
        
        // Right Right Case
        if (balance < -1 && data > node->right->data)
            return rotateLeft(node);
        
        // Left Right Case
        if (balance > 1 && data > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right Left Case
        if (balance < -1 && data < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }

public:
    // Method 1: Convert BST to AVL (Efficient - O(n) time, O(n) space)
    Node* convertToAVL_Method1(Node* root) {
        if (!root) return nullptr;
        
        // Step 1: Store inorder traversal (sorted order)
        vector<int> inorder;
        storeInorder(root, inorder);
        
        // Step 2: Build balanced AVL tree from sorted array
        return buildBalancedAVL(inorder, 0, inorder.size() - 1);
    }
    
    // Method 2: Convert BST to AVL (Using AVL insertion - O(n log n) time)
    Node* convertToAVL_Method2(Node* root) {
        if (!root) return nullptr;
        
        // Step 1: Store all elements
        vector<int> elements;
        storeInorder(root, elements);
        
        // Step 2: Build AVL tree by inserting elements
        Node* avlRoot = nullptr;
        for (int val : elements) {
            avlRoot = insertAVL(avlRoot, val);
        }
        
        return avlRoot;
    }
    
    // Utility: Print tree (level order)
    void printLevelOrder(Node* root) {
        if (!root) return;
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            
            for (int i = 0; i < levelSize; i++) {
                Node* curr = q.front();
                q.pop();
                
                cout << curr->data << "(h=" << curr->height << ") ";
                
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            cout << endl;
        }
    }
    
    // Utility: Print inorder traversal
    void printInorder(Node* root) {
        if (!root) return;
        printInorder(root->left);
        cout << root->data << " ";
        printInorder(root->right);
    }
    
    // Utility: Check if tree is AVL
    bool isAVL(Node* root) {
        if (!root) return true;
        
        int balance = getBalance(root);
        
        if (abs(balance) > 1) return false;
        
        return isAVL(root->left) && isAVL(root->right);
    }
    
    // Utility: Get tree height
    int getTreeHeight(Node* root) {
        return getHeight(root);
    }
};

// Helper function to insert into BST (unbalanced)
Node* insertBST(Node* root, int data) {
    if (!root) return new Node(data);
    
    if (data < root->data)
        root->left = insertBST(root->left, data);
    else if (data > root->data)
        root->right = insertBST(root->right, data);
    
    return root;
}

int main() {
    BSTtoAVL converter;
    
    // Create an unbalanced BST
    Node* bstRoot = nullptr;
    vector<int> values = {50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 55};
    
    cout << "Creating unbalanced BST with values: ";
    for (int val : values) {
        cout << val << " ";
        bstRoot = insertBST(bstRoot, val);
    }
    cout << "\n\n";
    
    cout << "Original BST (Level Order):\n";
    converter.printLevelOrder(bstRoot);
    cout << "\nOriginal BST Height: " << converter.getTreeHeight(bstRoot) << endl;
    cout << "Is AVL? " << (converter.isAVL(bstRoot) ? "Yes" : "No") << "\n\n";
    
    // Method 1: Convert using sorted array approach
    Node* avlRoot1 = converter.convertToAVL_Method1(bstRoot);
    cout << "After conversion to AVL (Method 1 - O(n)):\n";
    converter.printLevelOrder(avlRoot1);
    cout << "\nAVL Tree Height: " << converter.getTreeHeight(avlRoot1) << endl;
    cout << "Is AVL? " << (converter.isAVL(avlRoot1) ? "Yes" : "No") << "\n\n";
    
    // Test with a highly unbalanced BST (skewed tree)
    cout << "\n--- Testing with Skewed Tree ---\n";
    Node* skewedBST = nullptr;
    for (int i = 1; i <= 7; i++) {
        skewedBST = insertBST(skewedBST, i);
    }
    
    cout << "Skewed BST (Level Order):\n";
    converter.printLevelOrder(skewedBST);
    cout << "\nSkewed BST Height: " << converter.getTreeHeight(skewedBST) << endl;
    cout << "Is AVL? " << (converter.isAVL(skewedBST) ? "Yes" : "No") << "\n\n";
    
    Node* avlFromSkewed = converter.convertToAVL_Method1(skewedBST);
    cout << "After conversion to AVL:\n";
    converter.printLevelOrder(avlFromSkewed);
    cout << "\nAVL Tree Height: " << converter.getTreeHeight(avlFromSkewed) << endl;
    cout << "Is AVL? " << (converter.isAVL(avlFromSkewed) ? "Yes" : "No") << endl;
    
    return 0;
}