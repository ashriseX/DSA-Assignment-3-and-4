#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

// Employee structure
struct Employee {
    int id;
    string name;
    string department;
    double salary;
    
    Employee(int i, string n, string d, double s) 
        : id(i), name(n), department(d), salary(s) {}
};

// Node for hash table chaining
struct HashNode {
    int employeeID;
    Employee* employee;
    HashNode* next;
    
    HashNode(int id, Employee* emp) 
        : employeeID(id), employee(emp), next(nullptr) {}
};

class EmployeePortal {
private:
    // Hash table for ID-based lookups
    vector<HashNode*> hashTable;
    int tableSize;
    
    // Sorted array for name-based searches
    vector<Employee*> sortedByName;
    
    int searchComparisons;
    
    // Hash function for employee IDs
    int hashFunction(int employeeID) {
        return employeeID % tableSize;
    }
    
    // Binary search by name
    int binarySearchByName(const string& targetName) {
        int left = 0;
        int right = sortedByName.size() - 1;
        searchComparisons = 0;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            searchComparisons++;
            
            if (sortedByName[mid]->name == targetName) {
                return mid;
            } else if (sortedByName[mid]->name < targetName) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;
    }
    
    // Sort employees by name (using selection sort for educational purposes)
    void sortEmployeesByName() {
        int n = sortedByName.size();
        
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            
            for (int j = i + 1; j < n; j++) {
                if (sortedByName[j]->name < sortedByName[minIndex]->name) {
                    minIndex = j;
                }
            }
            
            if (minIndex != i) {
                swap(sortedByName[i], sortedByName[minIndex]);
            }
        }
    }
    
public:
    EmployeePortal(int size = 10) : tableSize(size) {
        hashTable.resize(tableSize, nullptr);
        searchComparisons = 0;
    }
    
    // Add employee to both structures
    bool addEmployee(int id, string name, string department, double salary) {
        // Check if ID already exists
        if (searchByID(id) != nullptr) {
            cout << "Error: Employee ID " << id << " already exists" << endl;
            return false;
        }
        
        // Create new employee
        Employee* newEmployee = new Employee(id, name, department, salary);
        
        // Add to hash table
        int index = hashFunction(id);
        HashNode* newNode = new HashNode(id, newEmployee);
        
        if (hashTable[index] == nullptr) {
            hashTable[index] = newNode;
        } else {
            // Chain at the end
            HashNode* current = hashTable[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        
        // Add to sorted name array
        sortedByName.push_back(newEmployee);
        sortEmployeesByName();
        
        cout << "Employee added successfully: " << name << " (ID: " << id << ")" << endl;
        return true;
    }
    
    // Search by ID using hash table - O(1) average
    Employee* searchByID(int employeeID) {
        int index = hashFunction(employeeID);
        HashNode* current = hashTable[index];
        searchComparisons = 0;
        
        while (current != nullptr) {
            searchComparisons++;
            if (current->employeeID == employeeID) {
                return current->employee;
            }
            current = current->next;
        }
        
        return nullptr;
    }
    
    // Search by name using binary search - O(log n)
    Employee* searchByName(const string& name) {
        int index = binarySearchByName(name);
        
        if (index != -1) {
            return sortedByName[index];
        }
        
        return nullptr;
    }
    
    // Display employee details
    void displayEmployee(Employee* emp) {
        if (emp == nullptr) {
            cout << "Employee not found" << endl;
            return;
        }
        
        cout << "\n--- Employee Details ---" << endl;
        cout << "ID: " << emp->id << endl;
        cout << "Name: " << emp->name << endl;
        cout << "Department: " << emp->department << endl;
        cout << "Salary: $" << fixed << setprecision(2) << emp->salary << endl;
    }
    
    // Display hash table structure
    void displayHashTable() {
        cout << "\n=== Hash Table (ID-based) ===" << endl;
        for (int i = 0; i < tableSize; i++) {
            cout << "Index " << i << ": ";
            
            if (hashTable[i] == nullptr) {
                cout << "Empty";
            } else {
                HashNode* current = hashTable[i];
                while (current != nullptr) {
                    cout << "[ID:" << current->employeeID 
                         << ", " << current->employee->name << "]";
                    if (current->next != nullptr) {
                        cout << " -> ";
                    }
                    current = current->next;
                }
            }
            cout << endl;
        }
    }
    
    // Display sorted name list
    void displaySortedNames() {
        cout << "\n=== Sorted Names List (Alphabetical) ===" << endl;
        for (int i = 0; i < sortedByName.size(); i++) {
            cout << i << ". " << sortedByName[i]->name 
                 << " (ID: " << sortedByName[i]->id << ")" << endl;
        }
    }
    
    // Display all employees in a formatted table
    void displayAllEmployees() {
        cout << "\n=== All Employees ===" << endl;
        cout << left << setw(8) << "ID" 
             << setw(20) << "Name" 
             << setw(20) << "Department" 
             << setw(12) << "Salary" << endl;
        cout << string(60, '-') << endl;
        
        for (Employee* emp : sortedByName) {
            cout << left << setw(8) << emp->id 
                 << setw(20) << emp->name 
                 << setw(20) << emp->department 
                 << "$" << fixed << setprecision(2) << emp->salary << endl;
        }
    }
    
    // Delete employee by ID
    bool deleteEmployee(int employeeID) {
        // Find and remove from hash table
        int index = hashFunction(employeeID);
        HashNode* current = hashTable[index];
        HashNode* previous = nullptr;
        
        while (current != nullptr) {
            if (current->employeeID == employeeID) {
                Employee* empToDelete = current->employee;
                
                // Remove from hash table
                if (previous == nullptr) {
                    hashTable[index] = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                
                // Remove from sorted array
                for (int i = 0; i < sortedByName.size(); i++) {
                    if (sortedByName[i] == empToDelete) {
                        sortedByName.erase(sortedByName.begin() + i);
                        break;
                    }
                }
                
                cout << "Employee " << empToDelete->name << " deleted successfully" << endl;
                delete empToDelete;
                return true;
            }
            previous = current;
            current = current->next;
        }
        
        cout << "Employee ID " << employeeID << " not found" << endl;
        return false;
    }
    
    // Search performance comparison
    void compareSearchPerformance(int targetID, const string& targetName) {
        cout << "\n=== Search Performance Comparison ===" << endl;
        
        // Search by ID (Hash)
        cout << "\n1. Search by ID " << targetID << " (Hash Table):" << endl;
        Employee* empByID = searchByID(targetID);
        cout << "   Comparisons: " << searchComparisons << endl;
        cout << "   Time Complexity: O(1) average" << endl;
        if (empByID) {
            cout << "   Result: Found - " << empByID->name << endl;
        } else {
            cout << "   Result: Not found" << endl;
        }
        
        // Search by Name (Binary Search)
        cout << "\n2. Search by Name \"" << targetName << "\" (Binary Search):" << endl;
        Employee* empByName = searchByName(targetName);
        cout << "   Comparisons: " << searchComparisons << endl;
        cout << "   Time Complexity: O(log n)" << endl;
        if (empByName) {
            cout << "   Result: Found - ID " << empByName->id << endl;
        } else {
            cout << "   Result: Not found" << endl;
        }
    }
    
    // Statistics
    void displayStatistics() {
        cout << "\n=== System Statistics ===" << endl;
        cout << "Total Employees: " << sortedByName.size() << endl;
        cout << "Hash Table Size: " << tableSize << endl;
        
        // Calculate load factor
        double loadFactor = (double)sortedByName.size() / tableSize;
        cout << "Load Factor: " << fixed << setprecision(2) << loadFactor << endl;
        
        // Calculate max chain length
        int maxChain = 0;
        int emptyBuckets = 0;
        
        for (int i = 0; i < tableSize; i++) {
            int chainLength = 0;
            HashNode* current = hashTable[i];
            
            if (current == nullptr) {
                emptyBuckets++;
            } else {
                while (current != nullptr) {
                    chainLength++;
                    current = current->next;
                }
                maxChain = max(maxChain, chainLength);
            }
        }
        
        cout << "Max Chain Length: " << maxChain << endl;
        cout << "Empty Buckets: " << emptyBuckets << endl;
    }
    
    // Destructor
    ~EmployeePortal() {
        // Clean up hash table
        for (int i = 0; i < tableSize; i++) {
            HashNode* current = hashTable[i];
            while (current != nullptr) {
                HashNode* temp = current;
                current = current->next;
                delete temp->employee;
                delete temp;
            }
        }
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "  Employee Portal - Dual Index System  " << endl;
    cout << "========================================" << endl;
    
    EmployeePortal portal(10);
    
    // Example from problem statement
    cout << "\n--- Adding Sample Employees ---" << endl;
    portal.addEmployee(101, "Ali", "Engineering", 75000);
    portal.addEmployee(102, "Sara", "Marketing", 65000);
    portal.addEmployee(103, "Bilal", "Sales", 60000);
    portal.addEmployee(104, "Zara", "HR", 55000);
    portal.addEmployee(105, "Ahmed", "Finance", 70000);
    portal.addEmployee(106, "Fatima", "Engineering", 80000);
    portal.addEmployee(107, "Hassan", "Marketing", 62000);
    
    // Display both data structures
    portal.displayHashTable();
    portal.displaySortedNames();
    portal.displayAllEmployees();
    
    // Demonstrate searches
    cout << "\n========================================" << endl;
    cout << "Search Demonstrations" << endl;
    cout << "========================================" << endl;
    
    cout << "\n--- Search by ID 103 (Hash Lookup) ---" << endl;
    Employee* emp1 = portal.searchByID(103);
    portal.displayEmployee(emp1);
    
    cout << "\n--- Search by Name \"Sara\" (Binary Search) ---" << endl;
    Employee* emp2 = portal.searchByName("Sara");
    portal.displayEmployee(emp2);
    
    // Performance comparison
    portal.compareSearchPerformance(105, "Ahmed");
    
    // Statistics
    portal.displayStatistics();
    
    // Interactive menu
    cout << "\n========================================" << endl;
    cout << "Interactive Mode" << endl;
    cout << "========================================" << endl;
    
    int choice;
    
    do {
        cout << "\n1. Add Employee" << endl;
        cout << "2. Search by ID" << endl;
        cout << "3. Search by Name" << endl;
        cout << "4. Delete Employee" << endl;
        cout << "5. Display All Employees" << endl;
        cout << "6. Display Hash Table" << endl;
        cout << "7. Display Sorted Names" << endl;
        cout << "8. Display Statistics" << endl;
        cout << "9. Compare Search Performance" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int id;
                string name, dept;
                double salary;
                
                cout << "Enter Employee ID: ";
                cin >> id;
                cin.ignore();
                
                cout << "Enter Name: ";
                getline(cin, name);
                
                cout << "Enter Department: ";
                getline(cin, dept);
                
                cout << "Enter Salary: ";
                cin >> salary;
                
                portal.addEmployee(id, name, dept, salary);
                break;
            }
            
            case 2: {
                int id;
                cout << "Enter Employee ID to search: ";
                cin >> id;
                
                Employee* emp = portal.searchByID(id);
                portal.displayEmployee(emp);
                cout << "Hash lookups used: " << 
                    (emp ? "Found in comparisons" : "Not found") << endl;
                break;
            }
            
            case 3: {
                string name;
                cout << "Enter Employee Name to search: ";
                cin.ignore();
                getline(cin, name);
                
                Employee* emp = portal.searchByName(name);
                portal.displayEmployee(emp);
                break;
            }
            
            case 4: {
                int id;
                cout << "Enter Employee ID to delete: ";
                cin >> id;
                portal.deleteEmployee(id);
                break;
            }
            
            case 5:
                portal.displayAllEmployees();
                break;
                
            case 6:
                portal.displayHashTable();
                break;
                
            case 7:
                portal.displaySortedNames();
                break;
                
            case 8:
                portal.displayStatistics();
                break;
                
            case 9: {
                int id;
                string name;
                
                cout << "Enter Employee ID: ";
                cin >> id;
                cin.ignore();
                
                cout << "Enter Employee Name: ";
                getline(cin, name);
                
                portal.compareSearchPerformance(id, name);
                break;
            }
            
            case 10:
                cout << "Exiting program..." << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 10);
    
    return 0;
}