#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

// Structure to hold sorting statistics
struct SortStats {
    string algorithmName;
    int comparisons;
    int swaps;
    int passes;
};

// Helper function to convert time string to minutes for easier comparison
int timeToMinutes(const string& time) {
    int hours, minutes;
    char colon;
    stringstream ss(time);
    ss >> hours >> colon >> minutes;
    return hours * 60 + minutes;
}

// Helper function to print the array
void printArray(const vector<string>& arr, const string& label = "") {
    if (!label.empty()) {
        cout << label << ": ";
    }
    cout << "[";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// Helper function to compare two time strings
bool isEarlier(const string& time1, const string& time2) {
    return timeToMinutes(time1) < timeToMinutes(time2);
}

// ==================== BUBBLE SORT ====================
SortStats bubbleSort(vector<string> arr) {
    SortStats stats = {"Bubble Sort", 0, 0, 0};
    int n = arr.size();
    
    cout << "\n========== BUBBLE SORT ==========\n";
    cout << "Initial: ";
    printArray(arr);
    cout << "\nDetailed Steps:\n";
    
    for (int i = 0; i < n - 1; i++) {
        stats.passes++;
        bool swapped = false;
        
        cout << "\nPass " << i + 1 << ":\n";
        
        for (int j = 0; j < n - i - 1; j++) {
            stats.comparisons++;
            
            if (isEarlier(arr[j + 1], arr[j])) {
                swap(arr[j], arr[j + 1]);
                stats.swaps++;
                swapped = true;
                cout << "  Swap: " << arr[j + 1] << " <-> " << arr[j] << " → ";
                printArray(arr);
            }
        }
        
        if (!swapped) {
            cout << "  No swaps needed - array is sorted!\n";
            break;
        }
        
        cout << "  After pass " << i + 1 << ": ";
        printArray(arr);
    }
    
    cout << "\nFinal sorted: ";
    printArray(arr);
    
    return stats;
}

// ==================== INSERTION SORT ====================
SortStats insertionSort(vector<string> arr) {
    SortStats stats = {"Insertion Sort", 0, 0, 0};
    int n = arr.size();
    
    cout << "\n========== INSERTION SORT ==========\n";
    cout << "Initial: ";
    printArray(arr);
    cout << "\nDetailed Steps:\n";
    
    for (int i = 1; i < n; i++) {
        stats.passes++;
        string key = arr[i];
        int j = i - 1;
        
        cout << "\nPass " << i << " (Inserting " << key << "):\n";
        
        while (j >= 0) {
            stats.comparisons++;
            
            if (isEarlier(key, arr[j])) {
                arr[j + 1] = arr[j];
                stats.swaps++;
                j--;
            } else {
                break;
            }
        }
        
        arr[j + 1] = key;
        cout << "  Inserted at position " << j + 1 << ": ";
        printArray(arr);
    }
    
    cout << "\nFinal sorted: ";
    printArray(arr);
    
    return stats;
}

// ==================== SELECTION SORT ====================
SortStats selectionSort(vector<string> arr) {
    SortStats stats = {"Selection Sort", 0, 0, 0};
    int n = arr.size();
    
    cout << "\n========== SELECTION SORT ==========\n";
    cout << "Initial: ";
    printArray(arr);
    cout << "\nDetailed Steps:\n";
    
    for (int i = 0; i < n - 1; i++) {
        stats.passes++;
        int minIdx = i;
        
        cout << "\nPass " << i + 1 << ":\n";
        cout << "  Finding minimum from position " << i << " onwards...\n";
        
        for (int j = i + 1; j < n; j++) {
            stats.comparisons++;
            if (isEarlier(arr[j], arr[minIdx])) {
                minIdx = j;
            }
        }
        
        if (minIdx != i) {
            cout << "  Minimum found: " << arr[minIdx] << " at position " << minIdx << "\n";
            cout << "  Swap: " << arr[i] << " <-> " << arr[minIdx] << "\n";
            swap(arr[i], arr[minIdx]);
            stats.swaps++;
        } else {
            cout << "  Element " << arr[i] << " is already in correct position\n";
        }
        
        cout << "  After pass " << i + 1 << ": ";
        printArray(arr);
    }
    
    cout << "\nFinal sorted: ";
    printArray(arr);
    
    return stats;
}

// ==================== MERGE SORT ====================
void merge(vector<string>& arr, int left, int mid, int right, SortStats& stats) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<string> leftArr(n1);
    vector<string> rightArr(n2);
    
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        stats.comparisons++;
        if (isEarlier(leftArr[i], rightArr[j])) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        stats.swaps++;
        k++;
    }
    
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
        stats.swaps++;
    }
    
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
        stats.swaps++;
    }
}

void mergeSortHelper(vector<string>& arr, int left, int right, SortStats& stats, int depth = 0) {
    if (left < right) {
        stats.passes++;
        int mid = left + (right - left) / 2;
        
        mergeSortHelper(arr, left, mid, stats, depth + 1);
        mergeSortHelper(arr, mid + 1, right, stats, depth + 1);
        merge(arr, left, mid, right, stats);
    }
}

SortStats mergeSort(vector<string> arr) {
    SortStats stats = {"Merge Sort", 0, 0, 0};
    
    cout << "\n========== MERGE SORT ==========\n";
    cout << "Initial: ";
    printArray(arr);
    cout << "\nNote: Merge Sort uses a divide-and-conquer approach\n";
    cout << "It recursively divides the array and merges sorted subarrays\n";
    
    mergeSortHelper(arr, 0, arr.size() - 1, stats);
    
    cout << "\nFinal sorted: ";
    printArray(arr);
    
    return stats;
}

// Function to print comparison table
void printComparisonTable(const vector<SortStats>& allStats) {
    cout << "\n\n";
    cout << "================================================================\n";
    cout << "              ALGORITHM PERFORMANCE COMPARISON                  \n";
    cout << "================================================================\n\n";
    
    // Header
    cout << "+---------------------+--------------+----------+----------+\n";
    cout << "| Algorithm           | Comparisons  |  Swaps   |  Passes  |\n";
    cout << "+---------------------+--------------+----------+----------+\n";
    
    // Data rows
    for (const auto& stats : allStats) {
        cout << "| " << left << setw(19) << stats.algorithmName << " | ";
        cout << right << setw(12) << stats.comparisons << " | ";
        cout << setw(8) << stats.swaps << " | ";
        cout << setw(8) << stats.passes << " |\n";
    }
    
    cout << "+---------------------+--------------+----------+----------+\n";
}

// Function to analyze and provide insights
void analyzeResults(const vector<SortStats>& allStats) {
    cout << "\n================================================================\n";
    cout << "                      ANALYSIS & INSIGHTS                       \n";
    cout << "================================================================\n\n";
    
    // Find most efficient in each category
    int minComparisons = allStats[0].comparisons;
    int minSwaps = allStats[0].swaps;
    string bestComparison = allStats[0].algorithmName;
    string bestSwaps = allStats[0].algorithmName;
    
    for (const auto& stats : allStats) {
        if (stats.comparisons < minComparisons) {
            minComparisons = stats.comparisons;
            bestComparison = stats.algorithmName;
        }
        if (stats.swaps < minSwaps) {
            minSwaps = stats.swaps;
            bestSwaps = stats.algorithmName;
        }
    }
    
    cout << "Most Efficient (Fewest Comparisons): " << bestComparison << " (" << minComparisons << " comparisons)\n";
    cout << "Most Efficient (Fewest Swaps): " << bestSwaps << " (" << minSwaps << " swaps)\n\n";
    
    cout << "Key Observations:\n";
    cout << "-----------------\n";
    cout << "* Bubble Sort: Simple but makes many comparisons; checks adjacent elements\n";
    cout << "* Insertion Sort: Efficient for small/nearly sorted data; builds sorted portion\n";
    cout << "* Selection Sort: Minimizes swaps; always finds minimum element\n";
    cout << "* Merge Sort: Divide-and-conquer; excellent for larger datasets\n\n";
    
    cout << "For this small dataset (5 login times):\n";
    cout << "  - All algorithms perform reasonably well\n";
    cout << "  - Insertion Sort often wins for small, partially sorted data\n";
    cout << "  - Merge Sort's advantage shows more with larger datasets (100+ items)\n";
}

int main() {
    // Employee login times
    vector<string> loginTimes = {"9:05", "8:55", "9:20", "8:45", "9:10"};
    
    cout << "================================================================\n";
    cout << "           EARLY LOGIN DETECTION - SORTING COMPARISON           \n";
    cout << "================================================================\n";
    cout << "\nScenario: Analyzing employee login times to find earliest arrivals\n";
    cout << "Original Login Times: ";
    printArray(loginTimes);
    
    vector<SortStats> allStats;
    
    // Run all sorting algorithms
    allStats.push_back(bubbleSort(loginTimes));
    allStats.push_back(insertionSort(loginTimes));
    allStats.push_back(selectionSort(loginTimes));
    allStats.push_back(mergeSort(loginTimes));
    
    // Display comparison table
    printComparisonTable(allStats);
    
    // Provide analysis
    analyzeResults(allStats);
    
    cout << "\nEarliest Login: " << "8:45" << "\n";
    cout << "Sorted Order: [8:45, 8:55, 9:05, 9:10, 9:20]\n\n";
    
    return 0;
}