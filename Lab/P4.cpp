#include <iostream>
#include <vector>
using namespace std;

// Node structure for linked list (chaining)
struct Node {
    int accountNumber;
    Node* next;
    
    Node(int acc) : accountNumber(acc), next(nullptr) {}
};

class BankHashTable {
private:
    vector<Node*> table;
    int tableSize;
    
    // Hash function: key % tableSize
    int hashFunction(int accountNumber) {
        return accountNumber % tableSize;
    }
    
public:
    BankHashTable(int size) : tableSize(size) {
        table.resize(tableSize, nullptr);
    }
    
    // Insert account number into hash table
    void insert(int accountNumber) {
        int index = hashFunction(accountNumber);
        
        // Create new node
        Node* newNode = new Node(accountNumber);
        
        // If bucket is empty, insert directly
        if (table[index] == nullptr) {
            table[index] = newNode;
            cout << "Account " << accountNumber << " inserted at index " << index << endl;
        } else {
            // Collision occurred - chain at the end
            cout << "Collision at index " << index << " for account " << accountNumber;
            
            Node* current = table[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
            cout << " - Chained to existing list" << endl;
        }
    }
    
    // Search for an account number
    bool search(int accountNumber) {
        int index = hashFunction(accountNumber);
        Node* current = table[index];
        
        while (current != nullptr) {
            if (current->accountNumber == accountNumber) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    // Delete an account number
    bool deleteAccount(int accountNumber) {
        int index = hashFunction(accountNumber);
        Node* current = table[index];
        Node* previous = nullptr;
        
        while (current != nullptr) {
            if (current->accountNumber == accountNumber) {
                if (previous == nullptr) {
                    // Deleting the first node in chain
                    table[index] = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                cout << "Account " << accountNumber << " deleted from index " << index << endl;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }
    
    // Display the entire hash table
    void display() {
        cout << "\n=== Hash Table Contents ===" << endl;
        for (int i = 0; i < tableSize; i++) {
            cout << "Index " << i << ": ";
            
            if (table[i] == nullptr) {
                cout << "Empty";
            } else {
                Node* current = table[i];
                while (current != nullptr) {
                    cout << current->accountNumber;
                    if (current->next != nullptr) {
                        cout << " -> ";
                    }
                    current = current->next;
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    
    // Display statistics
    void displayStatistics() {
        int totalAccounts = 0;
        int emptyBuckets = 0;
        int maxChainLength = 0;
        
        for (int i = 0; i < tableSize; i++) {
            int chainLength = 0;
            Node* current = table[i];
            
            if (current == nullptr) {
                emptyBuckets++;
            } else {
                while (current != nullptr) {
                    chainLength++;
                    totalAccounts++;
                    current = current->next;
                }
                maxChainLength = max(maxChainLength, chainLength);
            }
        }
        
        cout << "\n=== Hash Table Statistics ===" << endl;
        cout << "Total Accounts: " << totalAccounts << endl;
        cout << "Table Size: " << tableSize << endl;
        cout << "Load Factor: " << (double)totalAccounts / tableSize << endl;
        cout << "Empty Buckets: " << emptyBuckets << endl;
        cout << "Maximum Chain Length: " << maxChainLength << endl;
        cout << endl;
    }
    
    // Destructor to free memory
    ~BankHashTable() {
        for (int i = 0; i < tableSize; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
};

int main() {
    cout << "=== Bank Customer Account Hash Table System ===" << endl;
    cout << "\nHash Function: account_number % table_size\n" << endl;
    
    // Create hash table with size 5
    BankHashTable bankTable(5);
    
    // Example from problem statement
    cout << "--- Inserting Initial Accounts ---" << endl;
    vector<int> accounts = {101, 202, 303, 404, 505};
    
    for (int account : accounts) {
        bankTable.insert(account);
    }
    
    bankTable.display();
    
    // Insert account that causes collision
    cout << "--- Inserting Account with Collision ---" << endl;
    bankTable.insert(205);  // 205 % 5 = 0, same as 505
    
    bankTable.display();
    
    // Insert more accounts to demonstrate chaining
    cout << "--- Inserting More Accounts ---" << endl;
    bankTable.insert(506);  // 506 % 5 = 1, same as 101
    bankTable.insert(707);  // 707 % 5 = 2, same as 202
    
    bankTable.display();
    bankTable.displayStatistics();
    
    // Search operations
    cout << "--- Search Operations ---" << endl;
    int searchAccount = 303;
    cout << "Searching for account " << searchAccount << ": ";
    cout << (bankTable.search(searchAccount) ? "Found" : "Not Found") << endl;
    
    searchAccount = 999;
    cout << "Searching for account " << searchAccount << ": ";
    cout << (bankTable.search(searchAccount) ? "Found" : "Not Found") << endl;
    
    // Delete operations
    cout << "\n--- Delete Operations ---" << endl;
    bankTable.deleteAccount(205);
    bankTable.deleteAccount(101);
    
    bankTable.display();
    bankTable.displayStatistics();
    
    // Interactive menu
    cout << "\n--- Interactive Mode ---" << endl;
    int choice, account;
    
    do {
        cout << "\n1. Insert Account" << endl;
        cout << "2. Search Account" << endl;
        cout << "3. Delete Account" << endl;
        cout << "4. Display Hash Table" << endl;
        cout << "5. Display Statistics" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter account number to insert: ";
                cin >> account;
                bankTable.insert(account);
                break;
                
            case 2:
                cout << "Enter account number to search: ";
                cin >> account;
                cout << "Account " << account << ": ";
                cout << (bankTable.search(account) ? "Found" : "Not Found") << endl;
                break;
                
            case 3:
                cout << "Enter account number to delete: ";
                cin >> account;
                if (!bankTable.deleteAccount(account)) {
                    cout << "Account " << account << " not found" << endl;
                }
                break;
                
            case 4:
                bankTable.display();
                break;
                
            case 5:
                bankTable.displayStatistics();
                break;
                
            case 6:
                cout << "Exiting program..." << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
    
    return 0;
}