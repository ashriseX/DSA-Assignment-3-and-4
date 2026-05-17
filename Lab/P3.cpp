#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

// Structure to hold search statistics
struct SearchStats {
    string searchType;
    int comparisons;
    int position;
    bool found;
};

// Helper function to print patient list
void printPatientList(const vector<int>& patients, const string& label = "") {
    if (!label.empty()) {
        cout << label << ": ";
    }
    cout << "[";
    for (size_t i = 0; i < patients.size(); i++) {
        cout << patients[i];
        if (i < patients.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// ==================== LINEAR SEARCH ====================
SearchStats linearSearch(const vector<int>& patients, int targetID) {
    SearchStats stats = {"Linear Search", 0, -1, false};
    
    cout << "\n========== LINEAR SEARCH ==========\n";
    cout << "Searching for Patient ID: " << targetID << "\n";
    cout << "List: ";
    printPatientList(patients);
    cout << "\nSearch Process (Sequential):\n";
    cout << "----------------------------------------\n";
    
    for (size_t i = 0; i < patients.size(); i++) {
        stats.comparisons++;
        
        cout << "Step " << stats.comparisons << ": Checking position " << i 
             << " -> Patient ID " << patients[i];
        
        if (patients[i] == targetID) {
            stats.found = true;
            stats.position = i;
            cout << " --> FOUND!\n";
            break;
        } else {
            cout << " --> Not a match, continue...\n";
        }
    }
    
    cout << "----------------------------------------\n";
    
    if (stats.found) {
        cout << "Result: Patient ID " << targetID << " found at position " << stats.position << "\n";
    } else {
        cout << "Result: Patient ID " << targetID << " not found in the list\n";
    }
    
    cout << "Total Comparisons: " << stats.comparisons << "\n";
    
    return stats;
}

// ==================== BINARY SEARCH ====================
SearchStats binarySearch(const vector<int>& patients, int targetID) {
    SearchStats stats = {"Binary Search", 0, -1, false};
    
    cout << "\n========== BINARY SEARCH ==========\n";
    cout << "Searching for Patient ID: " << targetID << "\n";
    cout << "List (must be sorted): ";
    printPatientList(patients);
    cout << "\nSearch Process (Divide & Conquer):\n";
    cout << "----------------------------------------\n";
    
    int left = 0;
    int right = patients.size() - 1;
    int step = 0;
    
    while (left <= right) {
        step++;
        stats.comparisons++;
        
        int mid = left + (right - left) / 2;
        
        cout << "Step " << step << ":\n";
        cout << "  Search Range: [" << left << " to " << right << "]\n";
        cout << "  Middle Position: " << mid << " -> Patient ID " << patients[mid] << "\n";
        
        if (patients[mid] == targetID) {
            stats.found = true;
            stats.position = mid;
            cout << "  Comparison: " << patients[mid] << " == " << targetID << " --> FOUND!\n";
            break;
        } else if (patients[mid] < targetID) {
            cout << "  Comparison: " << patients[mid] << " < " << targetID 
                 << " --> Search RIGHT half\n";
            left = mid + 1;
        } else {
            cout << "  Comparison: " << patients[mid] << " > " << targetID 
                 << " --> Search LEFT half\n";
            right = mid - 1;
        }
        cout << "\n";
    }
    
    cout << "----------------------------------------\n";
    
    if (stats.found) {
        cout << "Result: Patient ID " << targetID << " found at position " << stats.position << "\n";
    } else {
        cout << "Result: Patient ID " << targetID << " not found in the list\n";
    }
    
    cout << "Total Comparisons: " << stats.comparisons << "\n";
    
    return stats;
}

// Function to print comparison table
void printComparisonTable(const SearchStats& linear, const SearchStats& binary) {
    cout << "\n\n";
    cout << "================================================================\n";
    cout << "                   SEARCH ALGORITHM COMPARISON                  \n";
    cout << "================================================================\n\n";
    
    cout << "+------------------+-------------+----------+--------+\n";
    cout << "| Search Type      | Comparisons | Position | Found  |\n";
    cout << "+------------------+-------------+----------+--------+\n";
    
    cout << "| " << left << setw(16) << linear.searchType << " | ";
    cout << right << setw(11) << linear.comparisons << " | ";
    cout << setw(8) << (linear.found ? to_string(linear.position) : "N/A") << " | ";
    cout << setw(6) << (linear.found ? "Yes" : "No") << " |\n";
    
    cout << "| " << left << setw(16) << binary.searchType << " | ";
    cout << right << setw(11) << binary.comparisons << " | ";
    cout << setw(8) << (binary.found ? to_string(binary.position) : "N/A") << " | ";
    cout << setw(6) << (binary.found ? "Yes" : "No") << " |\n";
    
    cout << "+------------------+-------------+----------+--------+\n";
}

// Function to analyze results
void analyzeResults(const SearchStats& linear, const SearchStats& binary, int listSize) {
    cout << "\n================================================================\n";
    cout << "                    ANALYSIS & INSIGHTS                         \n";
    cout << "================================================================\n\n";
    
    if (linear.found && binary.found) {
        int improvement = linear.comparisons - binary.comparisons;
        double percentage = ((double)improvement / linear.comparisons) * 100;
        
        cout << "Efficiency Comparison:\n";
        cout << "----------------------\n";
        cout << "* Linear Search made " << linear.comparisons << " comparison(s)\n";
        cout << "* Binary Search made " << binary.comparisons << " comparison(s)\n";
        cout << "* Binary Search was " << improvement << " comparison(s) faster\n";
        cout << "* That's a " << fixed << setprecision(1) << percentage << "% improvement!\n\n";
    }
    
    cout << "Algorithm Characteristics:\n";
    cout << "--------------------------\n";
    cout << "LINEAR SEARCH:\n";
    cout << "  * Works on: Unsorted OR Sorted lists\n";
    cout << "  * Method: Sequential check, element by element\n";
    cout << "  * Time Complexity: O(n) - worst case checks all elements\n";
    cout << "  * Best for: Small lists or unsorted data\n";
    cout << "  * Comparisons needed: 1 to " << listSize << " (depends on position)\n\n";
    
    cout << "BINARY SEARCH:\n";
    cout << "  * Works on: ONLY Sorted lists (REQUIRED!)\n";
    cout << "  * Method: Divide and conquer, eliminates half each time\n";
    cout << "  * Time Complexity: O(log n) - very efficient\n";
    cout << "  * Best for: Large sorted datasets\n";
    cout << "  * Comparisons needed: Maximum " << (int)ceil(log2(listSize)) << " for list of " << listSize << " elements\n\n";
    
    cout << "Real-World Application:\n";
    cout << "-----------------------\n";
    cout << "In a hospital with 1000 patients:\n";
    cout << "  * Linear Search: Up to 1000 comparisons (slow!)\n";
    cout << "  * Binary Search: Maximum 10 comparisons (fast!)\n";
    cout << "  * Performance difference becomes HUGE with larger datasets\n\n";
    
    cout << "Key Takeaway:\n";
    cout << "-------------\n";
    cout << "If data can be kept sorted, Binary Search is FAR superior.\n";
    cout << "The time investment in sorting pays off with faster searches!\n";
}

int main() {
    cout << "================================================================\n";
    cout << "         HOSPITAL PATIENT SEARCH - LINEAR vs BINARY             \n";
    cout << "================================================================\n\n";
    
    // Scenario setup
    cout << "Scenario: Hospital Patient ID Lookup System\n";
    cout << "--------------------------------------------\n\n";
    
    // Unsorted list (Emergency Admissions)
    vector<int> emergencyPatients = {102, 150, 97, 130, 121};
    cout << "Emergency Admissions (Unsorted): ";
    printPatientList(emergencyPatients);
    
    // Sorted list (Registered Patients)
    vector<int> registeredPatients = {97, 102, 121, 130, 150};
    cout << "Registered Patients (Sorted):    ";
    printPatientList(registeredPatients);
    
    int searchID = 130;
    cout << "\nTarget: Find Patient ID " << searchID << "\n";
    cout << "================================================================\n";
    
    // Perform Linear Search on unsorted list
    SearchStats linearStats = linearSearch(emergencyPatients, searchID);
    
    cout << "\n\n";
    
    // Perform Binary Search on sorted list
    SearchStats binaryStats = binarySearch(registeredPatients, searchID);
    
    // Print comparison
    printComparisonTable(linearStats, binaryStats);
    
    // Analyze results
    analyzeResults(linearStats, binaryStats, emergencyPatients.size());
    
    // Additional demonstration: Search for element not in list
    cout << "\n\n================================================================\n";
    cout << "              BONUS: Searching for Non-Existent ID              \n";
    cout << "================================================================\n";
    
    int notFoundID = 999;
    cout << "\nSearching for Patient ID " << notFoundID << " (not in lists):\n";
    
    SearchStats linearNotFound = linearSearch(emergencyPatients, notFoundID);
    cout << "\n";
    SearchStats binaryNotFound = binarySearch(registeredPatients, notFoundID);
    
    cout << "\n\nComparison (Not Found Case):\n";
    printComparisonTable(linearNotFound, binaryNotFound);
    
    cout << "\nObservation:\n";
    cout << "------------\n";
    cout << "When element is NOT found:\n";
    cout << "* Linear Search must check ALL " << emergencyPatients.size() << " elements\n";
    cout << "* Binary Search still only needs " << binaryNotFound.comparisons 
         << " comparisons (logarithmic)\n";
    cout << "* Binary Search's efficiency advantage is even more apparent!\n\n";
    
    return 0;
}