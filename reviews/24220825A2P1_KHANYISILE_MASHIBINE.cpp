// 24220825 - Khanyisile Mashibine

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// Bubble Sort implementation
void bubbleSort(vector<int>& arr)
{
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // If no elements were swapped, the array is already sorted
        if (!swapped)
        {
            break;
        }
    }
}

// Merge function used by Merge Sort
void merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArray(n1);
    vector<int> rightArray(n2);

    for (int i = 0; i < n1; i++)
    {
        leftArray[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++)
    {
        rightArray[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (leftArray[i] <= rightArray[j])
        {
            arr[k] = leftArray[i];
            i++;
        }
        else
        {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

// Merge Sort implementation
void mergeSort(vector<int>& arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Function to generate random numbers
vector<int> generateRandomArray(int size)
{
    vector<int> arr(size);

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(1, 100000);

    for (int i = 0; i < size; i++)
    {
        arr[i] = distribution(generator);
    }

    return arr;
}

// Function to check whether the array was sorted correctly
bool isSorted(const vector<int>& arr)
{
    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i - 1] > arr[i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    vector<int> inputSizes = {100, 1000, 5000};

    cout << "COS2611 Assessment 2 - Sorting Algorithm Analysis" << endl;
    cout << "Algorithms Used: Bubble Sort and Merge Sort" << endl;
    cout << endl;

    cout << left << setw(15) << "Input Size"
         << setw(25) << "Bubble Sort Time"
         << setw(25) << "Merge Sort Time"
         << endl;

    cout << string(65, '-') << endl;

    for (int size : inputSizes)
    {
        vector<int> originalArray = generateRandomArray(size);

        vector<int> bubbleArray = originalArray;
        vector<int> mergeArray = originalArray;

        auto bubbleStart = high_resolution_clock::now();
        bubbleSort(bubbleArray);
        auto bubbleEnd = high_resolution_clock::now();

        auto mergeStart = high_resolution_clock::now();
        mergeSort(mergeArray, 0, mergeArray.size() - 1);
        auto mergeEnd = high_resolution_clock::now();

        double bubbleTime = duration<double, milli>(bubbleEnd - bubbleStart).count();
        double mergeTime = duration<double, milli>(mergeEnd - mergeStart).count();

        cout << left << setw(15) << size
             << setw(25) << fixed << setprecision(5) << bubbleTime
             << setw(25) << fixed << setprecision(5) << mergeTime
             << endl;

        if (!isSorted(bubbleArray) || !isSorted(mergeArray))
        {
            cout << "Warning: One of the arrays was not sorted correctly." << endl;
        }
    }

    cout << endl;
    cout << "Time Complexity Report" << endl;
    cout << string(65, '-') << endl;

    cout << "Bubble Sort:" << endl;
    cout << "Best Case: O(n), when the array is already sorted." << endl;
    cout << "Average Case: O(n^2)" << endl;
    cout << "Worst Case: O(n^2), when the array is sorted in reverse order." << endl;
    cout << "Formula: n(n - 1) / 2 comparisons in the worst case." << endl;

    cout << endl;

    cout << "Merge Sort:" << endl;
    cout << "Best Case: O(n log n)" << endl;
    cout << "Average Case: O(n log n)" << endl;
    cout << "Worst Case: O(n log n)" << endl;
    cout << "Formula: T(n) = 2T(n / 2) + O(n)" << endl;

    return 0;
}