// COS2611 Assignment 2: Bubble and Merge Sorting
// 62458981
// Kalnisha Singh

#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

// Function for the first sorting algorithm
void bubbleSort(vector<int> &arr) // reference vector of integers
{
    int n = arr.size();
    bool swapped;                   // track swaps during a pass
    for (int i = 0; i < n - 1; ++i) // outer loop for each pass through the array
    {
        swapped = false;                    // assume no swaps
        for (int j = 0; j < n - i - 1; ++j) // inner loop for actual comparisons
        {                                   // i elements are already sorted
            if (arr[j] > arr[j + 1])        // neighbour comparison
            {
                swap(arr[j], arr[j + 1]); // bubble action - larger element moves right
                swapped = true;           // mark the swap
            }
        }
        // If no two elements were swapped in the inner loop, then the array is already sorted
        if (!swapped)
        { // If no swaps, array is already sorted and no need for the loop
            break;
        }
    }
}

// Function for the second sorting algorithm
void merge(vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1; // calculate the sizes of the two halves
    int n2 = right - mid;    // n1 and n2 stires how many elements in each half
    // Create temporary arrays
    vector<int> L(n1), R(n2);
    // Copy data to temporary arrays L[] and R[] to hold copies of data while merging
    for (int i = 0; i < n1; ++i)
    {
        L[i] = arr[left + i]; // copy left portion into array L
    }
    for (int j = 0; j < n2; ++j)
    {
        R[j] = arr[mid + 1 + j]; // copy right portion into array R
    }
    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left; // initializing merge pointers
    // merge sort
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j]) // compare current elements of L and R
        {
            arr[k] = L[i]; // copy smaller one into arr[k]
            ++i;           // mover pointer
        }
        else
        {
            arr[k] = R[j];
            ++j;
        }
        ++k; // move main array forward
    }
    // Copy the remaining elements of L[], if any
    while (i < n1)
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    // Copy the remaining elements of R[], if any
    while (j < n2)
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}
void mergeSort(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2; // midpoint
        // Sort first and second halves recursively
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Function to generate a random array of a given size
vector<int> generateRandomArray(int size)
{

    vector<int> arr(size);
    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand() % 1000;
    }

    return arr;

} // generateRandomArray

void measureSortingTimeFirstSortingAlgorithm(vector<int> &arr, double &timeExecuted, double &timeComplexity)
{
    vector<int> arrCopy = arr; // Copy of original array
    int n = arr.size();

    // measure start time
    clock_t startTime = clock();

    // Call your first sorting algorithm
    bubbleSort(arrCopy);

    // measure end time
    clock_t endTime = clock();

    // calculate executation time in secods for first sorting algorithm
    timeExecuted = double(endTime - startTime) / CLOCKS_PER_SEC;

    // calculate time comlexity for your sorting algorithm
    timeComplexity = n * n; // this will then be the time complexity

} // measureSortingTimeFirstSortingAlgorithm

void measureSortingTimeSecondSortingAlgorithm(vector<int> &arr, double &timeExecuted, double &timeComplexity)
{
    vector<int> arrCopy = arr; // Copy of original array
    int n = arr.size();

    // measure start time
    clock_t startTime = clock();

    // Call your second algorithm
    mergeSort(arrCopy, 0, arrCopy.size() - 1);

    // measure end time
    clock_t endTime = clock();

    // calculate executation time in secods for first sorting algorithm
    timeExecuted = double(endTime - startTime) / CLOCKS_PER_SEC;

    // calculate time comlexity for your sorting algorithm
    timeComplexity = n * (log(n) / log(2)); // this will then be the time complexity

} // measureSortingTimeSecondSortingAlgorithm

int main()
{
    srand(time(0));

    cout << "COS2611 Assessment 2 Project 1 - Skeleton \n";
    cout << endl;
    cout << "ARRAYS";

    cout << fixed << setprecision(6);

    // generate an array with 100 random elements

    double timeExecuted1, timeExecuted2;
    double timeComplexity1, timeComplexity2;

    vector<int> inputSizes = {100, 1000, 5000};

    for (int size : inputSizes)
    {
        vector<int> arr = generateRandomArray(size);

        // measure the sorting time for sorting algorithm
        measureSortingTimeFirstSortingAlgorithm(arr, timeExecuted1, timeComplexity1);

        measureSortingTimeSecondSortingAlgorithm(arr, timeExecuted2, timeComplexity2);

        // Print results
        cout << "\n--------------------------------------------------------------------------\n";
        cout << "Input size: " << size << "\n";

        cout << "\nBubble Sort: " << endl;
        cout << "Execution time: " << timeExecuted1 << " seconds\n";

        cout << "\nMerge Sort: " << endl;
        cout << "Execution time: " << timeExecuted2 << " seconds\n";

        cout << "\nThe time complexity formula for Bubble Sort (n^2): " << timeComplexity1 << "\n";
        cout << "The time complexity formula for Merge Sort (n log n): " << timeComplexity2 << "\n";
    }

    return 0;
} // main
