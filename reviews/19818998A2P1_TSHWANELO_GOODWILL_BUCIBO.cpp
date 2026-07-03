//19818998
//Tshwanelo Bucibo

#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;


//bubble sort function
void bubbleSort(vector<int> arr) {
    int n = arr.size();
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


//merge helper used by merge sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

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
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }
}

//merge sort function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


//generate random array of given size
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    srand(time(0));
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000;
    }
    return arr;
}


void measureSortingTimeFirstSortingAlgorithm(vector<int>& arr, double& timeExecuted, double& timeComplexity) {

    clock_t startTime = clock();

    bubbleSort(arr);

    clock_t endTime = clock();

    timeExecuted = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    int n = arr.size();
    timeComplexity = (double)n * (double)n;
}


void measureSortingTimeSecondSortingAlgorithm(vector<int>& arr, double& timeExecuted, double& timeComplexity) {

    clock_t startTime = clock();

    mergeSort(arr, 0, arr.size() - 1);

    clock_t endTime = clock();

    timeExecuted = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    int n = arr.size();
    timeComplexity = (double)n * log2((double)n);
}


int main() {

    cout << "COS2611 Assessment 2 Project 1 - Skeleton \n";
    cout << "ARRAYS\n\n";

    double timeExecuted1, timeExecuted2;
    double timeComplexity1, timeComplexity2;

    vector<int> inputSizes = { 100, 1000, 5000 };

    for (int size : inputSizes) {
        vector<int> arr1 = generateRandomArray(size);
        vector<int> arr2 = arr1;

        measureSortingTimeFirstSortingAlgorithm(arr1, timeExecuted1, timeComplexity1);
        measureSortingTimeSecondSortingAlgorithm(arr2, timeExecuted2, timeComplexity2);

        cout << "Input Size: " << size << "\n\n";

        cout << "Bubble Sort:\n";
        cout << "Execution Time: " << timeExecuted1 << " seconds\n\n\n";

        cout << "Merge Sort:\n";
        cout << "Execution Time: " << timeExecuted2 << " seconds\n\n\n";
    }

    cout << "The time complexity formula for Bubble Sort:  O(n^2)\n";
    cout << "The time complexity formula for Merge Sort:   O(n log n)\n";

    return 0;
}
