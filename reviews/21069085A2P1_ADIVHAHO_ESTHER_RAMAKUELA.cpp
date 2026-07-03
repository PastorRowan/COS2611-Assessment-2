// COS2611_2024_As2_P1.cpp
// Student Number: [Your Number]
// Name: [Your Name]

#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <iomanip>
using namespace std;

// ========== Function Prototypes ==========
void bubbleSort(vector<int>& arr);
void heapSort(vector<int>& arr);
void heapify(vector<int>& arr, int n, int i);
vector<int> generateRandomArray(int size);
void measureSortingTimeFirstSortingAlgorithm(vector<int>& arr, double& timeExecuted, double& timeComplexity);
void measureSortingTimeSecondSortingAlgorithm(vector<int>& arr, double& timeExecuted, double& timeComplexity);

// ========== Bubble Sort: O(n^2) ==========
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ========== Heap Sort: O(n log n) ==========
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest!= i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ========== Generate Random Array ==========
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

// ========== Timing Wrappers ==========
void measureSortingTimeFirstSortingAlgorithm(vector<int>& arr, double& timeExecuted, double& timeComplexity) {
    clock_t startTime = clock();
    bubbleSort(arr);
    clock_t endTime = clock();
    timeExecuted = double(endTime - startTime) / CLOCKS_PER_SEC;
    timeComplexity = arr.size() * arr.size(); // n^2
}

void measureSortingTimeSecondSortingAlgorithm(vector<int>& arr, double& timeExecuted, double& timeComplexity) {
    clock_t startTime = clock();
    heapSort(arr);
    clock_t endTime = clock();
    timeExecuted = double(endTime - startTime) / CLOCKS_PER_SEC;
    timeComplexity = arr.size() * log2(arr.size()); // n log n
}

int main()
{
    srand(time(0)); // Seed once only

    vector<int> inputSizes = { 100, 1000, 5000 };
    double timeExecuted1, timeExecuted2;
    double timeComplexity1, timeComplexity2;

    for (int size : inputSizes) {
        vector<int> arr1 = generateRandomArray(size);
        vector<int> arr2 = arr1; // copy for fair test

        measureSortingTimeFirstSortingAlgorithm(arr1, timeExecuted1, timeComplexity1);
        measureSortingTimeSecondSortingAlgorithm(arr2, timeExecuted2, timeComplexity2);

        cout << "Input Size: " << size << "\n\n";
        cout << "Bubble Sort:\n";
        cout << "Execution Time: " << fixed << setprecision(3) << timeExecuted1 << " seconds\n";
        cout << "Heap Sort:\n";
        cout << "Execution Time: " << fixed << setprecision(3) << timeExecuted2 << " seconds\n";
    }

    cout << "The time complexity formula for Bubble Sort: O(n^2)\n";
    cout << "The time complexity formula for Heap Sort: O(n log n)\n";

    return 0;
}