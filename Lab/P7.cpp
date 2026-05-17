#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
using namespace std;

// Date structure for easy comparison
struct Date {
    int year, month, day;
    
    Date(int y = 2025, int m = 1, int d = 1) : year(y), month(m), day(d) {}
    
    // Parse date from string format "YYYY-MM-DD"
    static Date fromString(const string& dateStr) {
        Date d;
        sscanf(dateStr.c_str(), "%d-%d-%d", &d.year, &d.month, &d.day);
        return d;
    }
    
    // Convert to string
    string toString() const {
        char buffer[12];
        sprintf(buffer, "%04d-%02d-%02d", year, month, day);
        return string(buffer);
    }
    
    // Compare dates
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
    
    bool operator==(const Date& other) const {
        return year == other.year && month == other.month && day == other.day;
    }
    
    bool operator<=(const Date& other) const {
        return *this < other || *this == other;
    }
};

// Patient structure
struct Patient {
    int id;
    string name;
    Date admissionDate;
    string diagnosis;
    int age;
    
    Patient(int i = 0, string n = "", Date d = Date(), string diag = "", int a = 0)
        : id(i), name(n), admissionDate(d), diagnosis(diag), age(a) {}
    
    void display() const {
        cout << left << setw(8) << id 
             << setw(20) << name 
             << setw(15) << admissionDate.toString()
             << setw(25) << diagnosis
             << setw(5) << age << endl;
    }
};

// Hash table node for chaining
struct HashNode {
    int patientID;
    Patient* patient;
    HashNode* next;
    
    HashNode(int id, Patient* p) : patientID(id), patient(p), next(nullptr) {}
};

class HealthcareAnalytics {
private:
    // Hash table for ID-based access
    vector<HashNode*> hashTable;
    int tableSize;
    
    // Array for date-based sorting and searching
    vector<Patient*> patientsByDate;
    
    int comparisonCount;
    
    // Hash function
    int hashFunction(int patientID) {
        return patientID % tableSize;
    }
    
    // Merge Sort implementation
    void merge(vector<Patient*>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        vector<Patient*> leftArr(n1);
        vector<Patient*> rightArr(n2);
        
        for (int i = 0; i < n1; i++) {
            leftArr[i] = arr[left + i];
        }
        for (int i = 0; i < n2; i++) {
            rightArr[i] = arr[mid + 1 + i];
        }
        
        int i = 0, j = 0, k = left;
        
        while (i < n1 && j < n2) {
            comparisonCount++;
            if (leftArr[i]->admissionDate <= rightArr[j]->admissionDate) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
    }
    
    void mergeSort(vector<Patient*>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    
    // Binary search by date
    int binarySearchByDate(const Date& targetDate) {
        int left = 0;
        int right = patientsByDate.size() - 1;
        comparisonCount = 0;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            comparisonCount++;
            
            if (patientsByDate[mid]->admissionDate == targetDate) {
                // Find the first occurrence
                while (mid > 0 && patientsByDate[mid - 1]->admissionDate == targetDate) {
                    mid--;
                }
                return mid;
            } else if (patientsByDate[mid]->admissionDate < targetDate) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;
    }
    
public:
    HealthcareAnalytics(int size = 20) : tableSize(size), comparisonCount(0) {
        hashTable.resize(tableSize, nullptr);
    }
    
    // Add patient to system
    bool addPatient(int id, string name, string dateStr, string diagnosis, int age) {
        // Check if patient ID already exists
        if (searchByID(id) != nullptr) {
            cout << "Error: Patient ID " << id << " already exists" << endl;
            return false;
        }
        
        // Create new patient
        Date admissionDate = Date::fromString(dateStr);
        Patient* newPatient = new Patient(id, name, admissionDate, diagnosis, age);
        
        // Add to hash table
        int index = hashFunction(id);
        HashNode* newNode = new HashNode(id, newPatient);
        
        if (hashTable[index] == nullptr) {
            hashTable[index] = newNode;
        } else {
            HashNode* current = hashTable[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        
        // Add to date-sorted array
        patientsByDate.push_back(newPatient);
        
        cout << "Patient added: " << name << " (ID: " << id << ")" << endl;
        return true;
    }
    
    // Sort patients by admission date using Merge Sort
    void sortByAdmissionDate() {
        if (patientsByDate.empty()) {
            cout << "No patients to sort" << endl;
            return;
        }
        
        cout << "\n--- Sorting by Admission Date (Merge Sort) ---" << endl;
        comparisonCount = 0;
        
        mergeSort(patientsByDate, 0, patientsByDate.size() - 1);
        
        cout << "Sorting complete" << endl;
        cout << "Comparisons made: " << comparisonCount << endl;
        cout << "Time Complexity: O(n log n)" << endl;
    }
    
    // Search by patient ID using hash table - O(1) average
    Patient* searchByID(int patientID) {
        int index = hashFunction(patientID);
        HashNode* current = hashTable[index];
        comparisonCount = 0;
        
        while (current != nullptr) {
            comparisonCount++;
            if (current->patientID == patientID) {
                return current->patient;
            }
            current = current->next;
        }
        
        return nullptr;
    }
    
    // Search by admission date using binary search - O(log n)
    vector<Patient*> searchByDate(const string& dateStr) {
        Date targetDate = Date::fromString(dateStr);
        vector<Patient*> results;
        
        int index = binarySearchByDate(targetDate);
        
        if (index != -1) {
            // Collect all patients with the same date
            while (index < patientsByDate.size() && 
                   patientsByDate[index]->admissionDate == targetDate) {
                results.push_back(patientsByDate[index]);
                index++;
            }
        }
        
        return results;
    }
    
    // Display single patient
    void displayPatient(Patient* patient) {
        if (patient == nullptr) {
            cout << "Patient not found" << endl;
            return;
        }
        
        cout << "\n--- Patient Details ---" << endl;
        cout << "ID: " << patient->id << endl;
        cout << "Name: " << patient->name << endl;
        cout << "Admission Date: " << patient->admissionDate.toString() << endl;
        cout << "Diagnosis: " << patient->diagnosis << endl;
        cout << "Age: " << patient->age << endl;
    }
    
    // Display all patients (sorted by date)
    void displayAllPatients() {
        if (patientsByDate.empty()) {
            cout << "No patients in system" << endl;
            return;
        }
        
        cout << "\n=== All Patients (Sorted by Admission Date) ===" << endl;
        cout << left << setw(8) << "ID" 
             << setw(20) << "Name" 
             << setw(15) << "Date"
             << setw(25) << "Diagnosis"
             << setw(5) << "Age" << endl;
        cout << string(73, '-') << endl;
        
        for (Patient* patient : patientsByDate) {
            patient->display();
        }
    }
    
    // Display hash table structure
    void displayHashTable() {
        cout << "\n=== Hash Table Structure (ID-based) ===" << endl;
        for (int i = 0; i < tableSize; i++) {
            cout << "Index " << setw(2) << i << ": ";
            
            if (hashTable[i] == nullptr) {
                cout << "Empty";
            } else {
                HashNode* current = hashTable[i];
                while (current != nullptr) {
                    cout << "[ID:" << current->patientID 
                         << ", " << current->patient->name << "]";
                    if (current->next != nullptr) {
                        cout << " -> ";
                    }
                    current = current->next;
                }
            }
            cout << endl;
        }
    }
    
    // Generate admission report by date range
    void generateDateRangeReport(const string& startDateStr, const string& endDateStr) {
        Date startDate = Date::fromString(startDateStr);
        Date endDate = Date::fromString(endDateStr);
        
        cout << "\n=== Admission Report: " << startDateStr 
             << " to " << endDateStr << " ===" << endl;
        cout << left << setw(8) << "ID" 
             << setw(20) << "Name" 
             << setw(15) << "Date"
             << setw(25) << "Diagnosis"
             << setw(5) << "Age" << endl;
        cout << string(73, '-') << endl;
        
        int count = 0;
        for (Patient* patient : patientsByDate) {
            if (startDate <= patient->admissionDate && 
                patient->admissionDate <= endDate) {
                patient->display();
                count++;
            }
        }
        
        cout << "\nTotal patients in range: " << count << endl;
    }
    
    // Analytics: Patients by diagnosis
    void analyzeByDiagnosis() {
        cout << "\n=== Diagnosis Analysis ===" << endl;
        
        // Simple frequency count
        vector<pair<string, int>> diagnosisCounts;
        
        for (Patient* patient : patientsByDate) {
            bool found = false;
            for (auto& pair : diagnosisCounts) {
                if (pair.first == patient->diagnosis) {
                    pair.second++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                diagnosisCounts.push_back({patient->diagnosis, 1});
            }
        }
        
        cout << left << setw(30) << "Diagnosis" << "Count" << endl;
        cout << string(40, '-') << endl;
        
        for (const auto& pair : diagnosisCounts) {
            cout << left << setw(30) << pair.first << pair.second << endl;
        }
    }
    
    // Analytics: Average age by diagnosis
    void analyzeAgeByDiagnosis() {
        cout << "\n=== Average Age by Diagnosis ===" << endl;
        
        vector<tuple<string, int, int>> diagnosisData; // diagnosis, sum, count
        
        for (Patient* patient : patientsByDate) {
            bool found = false;
            for (auto& data : diagnosisData) {
                if (get<0>(data) == patient->diagnosis) {
                    get<1>(data) += patient->age;
                    get<2>(data)++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                diagnosisData.push_back({patient->diagnosis, patient->age, 1});
            }
        }
        
        cout << left << setw(30) << "Diagnosis" << "Average Age" << endl;
        cout << string(45, '-') << endl;
        
        for (const auto& data : diagnosisData) {
            double avgAge = (double)get<1>(data) / get<2>(data);
            cout << left << setw(30) << get<0>(data) 
                 << fixed << setprecision(1) << avgAge << endl;
        }
    }
    
    // System statistics
    void displayStatistics() {
        cout << "\n=== System Statistics ===" << endl;
        cout << "Total Patients: " << patientsByDate.size() << endl;
        cout << "Hash Table Size: " << tableSize << endl;
        
        double loadFactor = (double)patientsByDate.size() / tableSize;
        cout << "Load Factor: " << fixed << setprecision(2) << loadFactor << endl;
        
        // Calculate hash table statistics
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
        
        cout << "Max Hash Chain Length: " << maxChain << endl;
        cout << "Empty Hash Buckets: " << emptyBuckets << endl;
    }
    
    // Demonstrate complete pipeline
    void demonstratePipeline() {
        cout << "\n========================================" << endl;
        cout << "  Complete Data Pipeline Demonstration  " << endl;
        cout << "========================================" << endl;
        
        cout << "\nStep 1: Data Ingestion (Hashing)" << endl;
        cout << "  - Patients stored in hash table for O(1) ID lookup" << endl;
        displayHashTable();
        
        cout << "\nStep 2: Data Processing (Merge Sort)" << endl;
        cout << "  - Sorting patients by admission date" << endl;
        sortByAdmissionDate();
        
        cout << "\nStep 3: Data Retrieval (Binary Search)" << endl;
        cout << "  - Efficient searches by ID or date" << endl;
        
        cout << "\nStep 4: Analytics & Reporting" << endl;
        cout << "  - Generate insights from processed data" << endl;
        analyzeByDiagnosis();
    }
    
    // Destructor
    ~HealthcareAnalytics() {
        for (int i = 0; i < tableSize; i++) {
            HashNode* current = hashTable[i];
            while (current != nullptr) {
                HashNode* temp = current;
                current = current->next;
                delete temp->patient;
                delete temp;
            }
        }
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "  Healthcare Analytics System v1.0     " << endl;
    cout << "========================================" << endl;
    
    HealthcareAnalytics system(20);
    
    // Load sample data from problem statement
    cout << "\n--- Loading Sample Patient Data ---" << endl;
    system.addPatient(203, "Ayesha", "2025-05-12", "Fever", 28);
    system.addPatient(201, "Ahmed", "2025-05-10", "Fracture", 45);
    system.addPatient(205, "Bilal", "2025-05-13", "Diabetes", 52);
    system.addPatient(202, "Fatima", "2025-05-11", "Hypertension", 38);
    system.addPatient(204, "Hassan", "2025-05-12", "Fever", 31);
    system.addPatient(206, "Zainab", "2025-05-14", "Asthma", 26);
    system.addPatient(207, "Usman", "2025-05-10", "Fracture", 42);
    system.addPatient(208, "Maryam", "2025-05-15", "Diabetes", 55);
    system.addPatient(209, "Imran", "2025-05-11", "Hypertension", 48);
    system.addPatient(210, "Sana", "2025-05-13", "Asthma", 29);
    
    // Demonstrate complete pipeline
    system.demonstratePipeline();
    
    // Display sorted patients
    system.displayAllPatients();
    
    // Search demonstrations
    cout << "\n========================================" << endl;
    cout << "  Search Demonstrations                 " << endl;
    cout << "========================================" << endl;
    
    cout << "\n--- Search by ID: 203 (Hash Lookup) ---" << endl;
    Patient* patient = system.searchByID(203);
    system.displayPatient(patient);
    
    cout << "\n--- Search by Date: 2025-05-12 (Binary Search) ---" << endl;
    vector<Patient*> patientsOnDate = system.searchByDate("2025-05-12");
    
    if (patientsOnDate.empty()) {
        cout << "No patients found on this date" << endl;
    } else {
        cout << "Found " << patientsOnDate.size() << " patient(s):" << endl;
        cout << left << setw(8) << "ID" 
             << setw(20) << "Name" 
             << setw(15) << "Date"
             << setw(25) << "Diagnosis"
             << setw(5) << "Age" << endl;
        cout << string(73, '-') << endl;
        
        for (Patient* p : patientsOnDate) {
            p->display();
        }
    }
    
    // Generate reports
    cout << "\n========================================" << endl;
    cout << "  Analytics & Reporting                 " << endl;
    cout << "========================================" << endl;
    
    system.generateDateRangeReport("2025-05-10", "2025-05-13");
    system.analyzeByDiagnosis();
    system.analyzeAgeByDiagnosis();
    system.displayStatistics();
    
    // Interactive menu
    cout << "\n========================================" << endl;
    cout << "  Interactive Mode                      " << endl;
    cout << "========================================" << endl;
    
    int choice;
    
    do {
        cout << "\n1. Add Patient" << endl;
        cout << "2. Search by ID" << endl;
        cout << "3. Search by Admission Date" << endl;
        cout << "4. Display All Patients" << endl;
        cout << "5. Generate Date Range Report" << endl;
        cout << "6. Analyze by Diagnosis" << endl;
        cout << "7. Analyze Age by Diagnosis" << endl;
        cout << "8. Display Hash Table" << endl;
        cout << "9. Display Statistics" << endl;
        cout << "10. Re-sort by Date" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int id, age;
                string name, date, diagnosis;
                
                cout << "Enter Patient ID: ";
                cin >> id;
                cin.ignore();
                
                cout << "Enter Name: ";
                getline(cin, name);
                
                cout << "Enter Admission Date (YYYY-MM-DD): ";
                getline(cin, date);
                
                cout << "Enter Diagnosis: ";
                getline(cin, diagnosis);
                
                cout << "Enter Age: ";
                cin >> age;
                
                system.addPatient(id, name, date, diagnosis, age);
                system.sortByAdmissionDate();
                break;
            }
            
            case 2: {
                int id;
                cout << "Enter Patient ID: ";
                cin >> id;
                
                Patient* p = system.searchByID(id);
                system.displayPatient(p);
                break;
            }
            
            case 3: {
                string date;
                cout << "Enter Admission Date (YYYY-MM-DD): ";
                cin.ignore();
                getline(cin, date);
                
                vector<Patient*> patients = system.searchByDate(date);
                
                if (patients.empty()) {
                    cout << "No patients found on " << date << endl;
                } else {
                    cout << "\nPatients admitted on " << date << ":" << endl;
                    cout << left << setw(8) << "ID" 
                         << setw(20) << "Name" 
                         << setw(15) << "Date"
                         << setw(25) << "Diagnosis"
                         << setw(5) << "Age" << endl;
                    cout << string(73, '-') << endl;
                    
                    for (Patient* p : patients) {
                        p->display();
                    }
                }
                break;
            }
            
            case 4:
                system.displayAllPatients();
                break;
                
            case 5: {
                string startDate, endDate;
                cout << "Enter Start Date (YYYY-MM-DD): ";
                cin.ignore();
                getline(cin, startDate);
                
                cout << "Enter End Date (YYYY-MM-DD): ";
                getline(cin, endDate);
                
                system.generateDateRangeReport(startDate, endDate);
                break;
            }
            
            case 6:
                system.analyzeByDiagnosis();
                break;
                
            case 7:
                system.analyzeAgeByDiagnosis();
                break;
                
            case 8:
                system.displayHashTable();
                break;
                
            case 9:
                system.displayStatistics();
                break;
                
            case 10:
                system.sortByAdmissionDate();
                break;
                
            case 11:
                cout << "Exiting system..." << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 11);
    
    return 0;
}