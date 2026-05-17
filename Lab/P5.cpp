#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <chrono>
using namespace std;
using namespace std::chrono;

class InventoryManager {
private:
    vector<int> prices;
    int comparisonCount;
    
    // Selection Sort - sorts prices in ascending order
    void selectionSort(vector<int>& arr) {
        int n = arr.size();
        comparisonCount = 0;
        
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            
            // Find minimum element in unsorted portion
            for (int j = i + 1; j < n; j++) {
                comparisonCount++;
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            
            // Swap minimum element with first unsorted element
            if (minIndex != i) {
                swap(arr[i], arr[minIndex]);
            }
        }
    }
    
    // Binary Search - searches for target price
    int binarySearch(const vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;
        comparisonCount = 0;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            comparisonCount++;
            
            if (arr[mid] == target) {
                return mid;  // Found
            } else if (arr[mid] < target) {
                left = mid + 1;  // Search right half
            } else {
                right = mid - 1;  // Search left half
            }
        }
        
        return -1;  // Not found
    }
    
    // Linear Search - for comparison purposes
    int linearSearch(const vector<int>& arr, int target) {
        comparisonCount = 0;
        
        for (int i = 0; i < arr.size(); i++) {
            comparisonCount++;
            if (arr[i] == target) {
                return i;
            }
        }
        
        return -1;
    }
    
public:
    // Load prices into inventory
    void loadPrices(const vector<int>& inputPrices) {
        prices = inputPrices;
    }
    
    // Display prices
    void displayPrices(const vector<int>& arr, const string& label) {
        cout << label << ": [";
        for (int i = 0; i < arr.size(); i++) {
            cout << arr[i];
            if (i < arr.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
    
    // Sort and search demonstration
    void sortAndSearch(int targetPrice) {
        vector<int> sortedPrices = prices;
        
        cout << "\n--- Sorting Process ---" << endl;
        displayPrices(prices, "Original Prices");
        
        auto startSort = high_resolution_clock::now();
        selectionSort(sortedPrices);
        auto endSort = high_resolution_clock::now();
        auto sortDuration = duration_cast<microseconds>(endSort - startSort);
        
        displayPrices(sortedPrices, "Sorted Prices");
        cout << "Sorting Comparisons: " << comparisonCount << endl;
        cout << "Sorting Time: " << sortDuration.count() << " microseconds" << endl;
        
        cout << "\n--- Binary Search (on sorted array) ---" << endl;
        cout << "Searching for price: " << targetPrice << endl;
        
        auto startBinary = high_resolution_clock::now();
        int binaryResult = binarySearch(sortedPrices, targetPrice);
        auto endBinary = high_resolution_clock::now();
        auto binaryDuration = duration_cast<microseconds>(endBinary - startBinary);
        
        if (binaryResult != -1) {
            cout << "Found at index: " << binaryResult << endl;
        } else {
            cout << "Not found" << endl;
        }
        cout << "Binary Search Comparisons: " << comparisonCount << endl;
        cout << "Binary Search Time: " << binaryDuration.count() << " microseconds" << endl;
        
        cout << "\n--- Linear Search (on unsorted array) - For Comparison ---" << endl;
        cout << "Searching for price: " << targetPrice << endl;
        
        auto startLinear = high_resolution_clock::now();
        int linearResult = linearSearch(prices, targetPrice);
        auto endLinear = high_resolution_clock::now();
        auto linearDuration = duration_cast<microseconds>(endLinear - startLinear);
        
        if (linearResult != -1) {
            cout << "Found at index: " << linearResult << endl;
        } else {
            cout << "Not found" << endl;
        }
        cout << "Linear Search Comparisons: " << comparisonCount << endl;
        cout << "Linear Search Time: " << linearDuration.count() << " microseconds" << endl;
    }
    
    // Performance comparison with large dataset
    void performanceComparison(int dataSize) {
        cout << "\n========================================" << endl;
        cout << "Performance Comparison (N = " << dataSize << ")" << endl;
        cout << "========================================" << endl;
        
        // Generate random prices
        vector<int> largePrices;
        srand(time(0));
        
        for (int i = 0; i < dataSize; i++) {
            largePrices.push_back(rand() % 10000 + 1);
        }
        
        // Choose a target price that exists
        int targetPrice = largePrices[dataSize / 2];
        
        cout << "Dataset size: " << dataSize << " prices" << endl;
        cout << "Target price: " << targetPrice << endl;
        
        // Sort the array
        vector<int> sortedLargePrices = largePrices;
        
        auto startSort = high_resolution_clock::now();
        selectionSort(sortedLargePrices);
        auto endSort = high_resolution_clock::now();
        auto sortDuration = duration_cast<microseconds>(endSort - startSort);
        
        int sortComparisons = comparisonCount;
        
        // Binary Search
        auto startBinary = high_resolution_clock::now();
        int binaryResult = binarySearch(sortedLargePrices, targetPrice);
        auto endBinary = high_resolution_clock::now();
        auto binaryDuration = duration_cast<microseconds>(endBinary - startBinary);
        
        int binaryComparisons = comparisonCount;
        
        // Linear Search
        auto startLinear = high_resolution_clock::now();
        int linearResult = linearSearch(largePrices, targetPrice);
        auto endLinear = high_resolution_clock::now();
        auto linearDuration = duration_cast<microseconds>(endLinear - startLinear);
        
        int linearComparisons = comparisonCount;
        
        // Display results
        cout << "\n--- Results ---" << endl;
        cout << fixed << setprecision(2);
        
        cout << "\nSelection Sort:" << endl;
        cout << "  Comparisons: " << sortComparisons << endl;
        cout << "  Time: " << sortDuration.count() << " microseconds" << endl;
        
        cout << "\nBinary Search (sorted):" << endl;
        cout << "  Comparisons: " << binaryComparisons << endl;
        cout << "  Time: " << binaryDuration.count() << " microseconds" << endl;
        cout << "  Result: " << (binaryResult != -1 ? "Found" : "Not Found") << endl;
        
        cout << "\nLinear Search (unsorted):" << endl;
        cout << "  Comparisons: " << linearComparisons << endl;
        cout << "  Time: " << linearDuration.count() << " microseconds" << endl;
        cout << "  Result: " << (linearResult != -1 ? "Found" : "Not Found") << endl;
        
        cout << "\n--- Efficiency Analysis ---" << endl;
        cout << "Binary Search is " << (double)linearComparisons / binaryComparisons 
             << "x more efficient (comparisons)" << endl;
        
        if (binaryDuration.count() > 0) {
            cout << "Binary Search is " << (double)linearDuration.count() / binaryDuration.count() 
                 << "x faster (time)" << endl;
        }
    }
    
    // Step-by-step demonstration
    void stepByStepDemo() {
        vector<int> demoData = {500, 150, 300, 100, 200};
        int target = 300;
        
        cout << "\n========================================" << endl;
        cout << "Step-by-Step Demonstration" << endl;
        cout << "========================================" << endl;
        
        displayPrices(demoData, "\nOriginal Prices");
        
        cout << "\n--- Selection Sort Process ---" << endl;
        int n = demoData.size();
        
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            
            cout << "\nPass " << (i + 1) << ":" << endl;
            cout << "  Looking for minimum in range [" << i << " to " << (n-1) << "]" << endl;
            
            for (int j = i + 1; j < n; j++) {
                if (demoData[j] < demoData[minIndex]) {
                    minIndex = j;
                }
            }
            
            cout << "  Minimum value: " << demoData[minIndex] << " at index " << minIndex << endl;
            
            if (minIndex != i) {
                cout << "  Swapping " << demoData[i] << " and " << demoData[minIndex] << endl;
                swap(demoData[i], demoData[minIndex]);
            }
            
            cout << "  Array after pass: ";
            displayPrices(demoData, "");
        }
        
        cout << "\n--- Binary Search Process ---" << endl;
        cout << "Searching for: " << target << endl;
        
        int left = 0, right = n - 1;
        int step = 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            cout << "\nStep " << step++ << ":" << endl;
            cout << "  Search range: [" << left << " to " << right << "]" << endl;
            cout << "  Middle index: " << mid << ", Value: " << demoData[mid] << endl;
            
            if (demoData[mid] == target) {
                cout << "  Match found at index " << mid << endl;
                break;
            } else if (demoData[mid] < target) {
                cout << "  " << demoData[mid] << " < " << target << ", search right half" << endl;
                left = mid + 1;
            } else {
                cout << "  " << demoData[mid] << " > " << target << ", search left half" << endl;
                right = mid - 1;
            }
        }
    }
};

int main() {
    InventoryManager manager;
    
    cout << "========================================" << endl;
    cout << "   Inventory Manager - Price Search    " << endl;
    cout << "========================================" << endl;
    
    // Example from problem statement
    vector<int> prices = {500, 150, 300, 100, 200};
    manager.loadPrices(prices);
    
    // Demonstrate with example data
    manager.sortAndSearch(300);
    
    // Step-by-step demonstration
    manager.stepByStepDemo();
    
    // Performance comparison with different sizes
    manager.performanceComparison(100);
    manager.performanceComparison(1000);
    
    // Interactive menu
    cout << "\n========================================" << endl;
    cout << "Interactive Mode" << endl;
    cout << "========================================" << endl;
    
    int choice;
    
    do {
        cout << "\n1. Enter custom prices and search" << endl;
        cout << "2. Generate random prices and compare performance" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int n, target;
                cout << "Enter number of products: ";
                cin >> n;
                
                vector<int> customPrices(n);
                cout << "Enter " << n << " prices: ";
                for (int i = 0; i < n; i++) {
                    cin >> customPrices[i];
                }
                
                cout << "Enter target price to search: ";
                cin >> target;
                
                manager.loadPrices(customPrices);
                manager.sortAndSearch(target);
                break;
            }
            
            case 2: {
                int size;
                cout << "Enter dataset size: ";
                cin >> size;
                manager.performanceComparison(size);
                break;
            }
            
            case 3:
                cout << "Exiting program..." << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
    
    return 0;
}