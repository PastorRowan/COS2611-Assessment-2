// Masiviwe Sishwali 59132132
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

// Bubble Sort - First Algorithm
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    // Swapped flag to indicate whether a swapped occured during a pass
    bool swapped;
    for (int i = 0; i < n-1; i++) {
        // Set swapped to false at the start of each pass
        swapped = false;
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                // if a swapped occured, set the flag to true
                swapped = true;
            }
        }
        // If no swaps occurred during a full pass, the array is already sorted
        if (swapped == false) {
            break; // or return;
        };
    }
}

// Merge Sort Helper Functions
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++; k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++; k++;
    }
}

void mergeSortHelper(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left)/2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort(vector<int>& arr) {
    mergeSortHelper(arr, 0, arr.size()-1);
}

// Generate random array
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000;
    }
    return arr;
}

// Timing functions (kept similar to skeleton)
void measureSortingTimeFirstSortingAlgorithm(vector<int>& arr, double& timeExecuted, double& timeComplexity) {
    clock_t start = clock();
    bubbleSort(arr);
    clock_t end = clock();
    timeExecuted = (double)(end - start) / CLOCKS_PER_SEC;
    timeComplexity = 0;
}

void measureSortingTimeSecondSortingAlgorithm(vector<int>& arr, double& timeExecuted, double& timeComplexity) {
    clock_t start = clock();
    mergeSort(arr);
    clock_t end = clock();
    timeExecuted = (double)(end - start) / CLOCKS_PER_SEC;
    timeComplexity = 0;
}

void printIsSorted(vector<int>& arr) {
    for (unsigned int i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) {
            std::cout << "array is not sorted" << std::endl;
            return;
        };
    };
    std::cout << "array is sorted" << std::endl;
};

int main() {
    cout << "COS2611 Assessment 2 Project 1\n\n";
    
    vector<int> sizes = {100, 1000, 5000};
    
    for (int size : sizes) {
        vector<int> arr = generateRandomArray(size);
        vector<int> arr2 = arr;  // copy for second algorithm
        
        double time1 = 0, time2 = 0;
        double comp1 = 0, comp2 = 0;
        
        measureSortingTimeFirstSortingAlgorithm(arr, time1, comp1);
        measureSortingTimeSecondSortingAlgorithm(arr2, time2, comp2);

        std::cout << "arr is sorted: ";
        printIsSorted(arr);

        std::cout << "arr2 is sorted: ";
        printIsSorted(arr2);

        cout << "Input Size: " << size << endl;
        cout << "Bubble Sort: Execution Time: " << fixed << setprecision(4) << time1 << " seconds" << endl;
        cout << "Merge Sort: Execution Time: " << fixed << setprecision(4) << time2 << " seconds" << endl << endl;
    }
    
    cout << "The time complexity formula for Bubble Sort: O(n^2)" << endl;
    cout << "The time complexity formula for Merge Sort: O(n log n)" << endl;
    
    return 0;
}
