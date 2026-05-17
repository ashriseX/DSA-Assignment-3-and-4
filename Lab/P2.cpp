#include <iostream>
#include <vector>
using namespace std;

class HospitalRecordMerger {
private:
    // Merge two sorted arrays into one sorted array
    vector<int> mergeSortedLists(const vector<int>& branchA, const vector<int>& branchB) {
        vector<int> merged;
        int i = 0, j = 0;
        int sizeA = branchA.size();
        int sizeB = branchB.size();
        
        // Compare elements from both arrays and add smaller one
        while (i < sizeA && j < sizeB) {
            if (branchA[i] <= branchB[j]) {
                merged.push_back(branchA[i]);
                i++;
            } else {
                merged.push_back(branchB[j]);
                j++;
            }
        }
        
        // Add remaining elements from Branch A
        while (i < sizeA) {
            merged.push_back(branchA[i]);
            i++;
        }
        
        // Add remaining elements from Branch B
        while (j < sizeB) {
            merged.push_back(branchB[j]);
            j++;
        }
        
        return merged;
    }
    
public:
    void demonstrateMerge() {
        // Example from problem statement
        vector<int> branchA = {1001, 1003, 1006};
        vector<int> branchB = {1002, 1004, 1005};
        
        cout << "Branch A Patient IDs: ";
        displayList(branchA);
        
        cout << "Branch B Patient IDs: ";
        displayList(branchB);
        
        vector<int> merged = mergeSortedLists(branchA, branchB);
        
        cout << "Merged Patient IDs: ";
        displayList(merged);
        cout << endl;
    }
    
    void displayList(const vector<int>& list) {
        cout << "[";
        for (int i = 0; i < list.size(); i++) {
            cout << list[i];
            if (i < list.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
    
    // Interactive function to merge custom lists
    void mergeCustomLists() {
        int sizeA, sizeB;
        
        cout << "Enter number of patient IDs in Branch A: ";
        cin >> sizeA;
        
        vector<int> branchA(sizeA);
        cout << "Enter " << sizeA << " sorted patient IDs for Branch A: ";
        for (int i = 0; i < sizeA; i++) {
            cin >> branchA[i];
        }
        
        cout << "Enter number of patient IDs in Branch B: ";
        cin >> sizeB;
        
        vector<int> branchB(sizeB);
        cout << "Enter " << sizeB << " sorted patient IDs for Branch B: ";
        for (int i = 0; i < sizeB; i++) {
            cin >> branchB[i];
        }
        
        vector<int> merged = mergeSortedLists(branchA, branchB);
        
        cout << "\nMerged Patient IDs: ";
        displayList(merged);
    }
};

int main() {
    HospitalRecordMerger merger;
    
    cout << "=== Hospital Branch Record Merge System ===" << endl;
    cout << "\n--- Example Case ---" << endl;
    merger.demonstrateMerge();
    
    cout << "--- Custom Input ---" << endl;
    merger.mergeCustomLists();
    
    return 0;
}