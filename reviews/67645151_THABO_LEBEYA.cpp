//67645151
//Thabo
// I dont have your pc.h file so sohuld of eft this out you dont even use it
// #include "pch.h"
#include <iostream>
#include <vector>
#include<cstdlib>
#include<ctime>
#include <chrono>
#include <cmath>
#include <iomanip>

//#include "COS2611_As2_P1.h"
using namespace std;


//Function for the first sorting algorithm
void bubble_Sort(int arr[], int size)
{
    // Swapped flag to indicate whether a swapped occured during a pass
    bool swapped;
    for (int i = 0; i < size - 1; i++)
    {
        // Set swapped to false at the start of each pass
        swapped = false;
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // swaping of elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        // If no swaps occurred during a full pass, the array is already sorted
        if (swapped == false) {
            break; // or return;
        };
    }
}


//Function for the second sorting algorithm
void merge(int arr2[], int left, int mid, int right)
{
    int num1 = mid - left + 1;
    int num2 = right - mid;

    std::vector <int> L(num1);
    std::vector <int> R(num2);

    //copy data into the temporary arrays
    for (int i = 0; i < num1; i++)
        L[i] = arr2[left + i];

    for (int j = 0; j < num2; j++)
        R[j] = arr2[mid + 1 + j];

    int i = 0, j = 0, k = left;

    //merging the temporary arrays back into arr2[]
    while (i < num1 && j < num2)
    {
        if (L[i] <= R[j])
        {
            arr2[k] = L[i];
            i++;
        }
        else
        {
            arr2[k] = R[j];
            j++;
        }
        k++;
    }
    //copy the remaining elements of L[]
    while (i < num1)
    {
        arr2[k] = L[i];
        i++;
        k++;
    }
    //copy the remaining elements of R[]
    while (j < num2)
    {
        arr2[k] = R[j];
        j++;
        k++;
    }

}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}


//Function to generate a random array of a given size
vector<int> generateRandomArray(int size) {

    vector<int> arr(size);

    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000; //adjust the range to play around with it
    }

    return arr;

} //generateRandomArray


//you can make this more code efficient - did it this way for more clarity purposes

void measureSortingTimeFirstSortingAlgorithm(vector<int>& arr, double& timeExecuted, double& timeComplexity) {

    //measure start time
    auto startTime = std::chrono::high_resolution_clock::now();

    //Call your first sorting algorithm
    bubble_Sort(arr.data(), arr.size());


    //measure end time
    auto endTime = std::chrono::high_resolution_clock::now();

    //calculate executation time in secods for first sorting algorithm

    std::chrono::duration<double> elapsed = endTime - startTime;
    timeExecuted = elapsed.count();

    //calculate time complexity for your sorting algorithm

    timeComplexity = arr.size() * log2(arr.size());
    //this will then be the time complexity - you must provide the code

} //measureSortingTimeFirstSortingAlgorithm



void measureSortingTimeSecondSortingAlgorithm(vector<int>& arr, double& timeExecuted, double& timeComplexity) {

    //measure start time
    auto startTime = std::chrono::high_resolution_clock::now();

    //Call your second algortihm
    mergeSort(arr.data(), 0, arr.size() - 1);

    //measure end time

    auto endTime = std::chrono::high_resolution_clock::now();

    //calculate executation time in secods for first sorting algorithm

    std::chrono::duration<double> elapsed = endTime - startTime;
    timeExecuted = elapsed.count();

    //calculate time complexity for your sorting algorithm

    timeComplexity = arr.size() * log2(arr.size()); //this will then be the time complexity - you must provide the code

} //measureSortingTimeSecondSortingAlgorithm




int main()
{
    srand(time(0));

    cout << fixed << setprecision(3);
    cout << "COS2611 Assessment 2 Project 1 - Skeleton \n";
    cout << "ARRAYS";

    //generate an array with 100 random elements

    double timeExecuted1, timeExecuted2;
    double timeComplexity1, timeComplexity2;

    vector<int> inputSizes = { 100,1000,5000 };

    for (int size : inputSizes) {
        vector<int> arr = generateRandomArray(size);

        //measure the sorting time for sorting algorithm

        measureSortingTimeFirstSortingAlgorithm(arr, timeExecuted1, timeComplexity1);

        measureSortingTimeSecondSortingAlgorithm(arr, timeExecuted2, timeComplexity2);

        //The display of your results will go here.
        cout << "\nInput Size: " << size << "\n";
        cout << ""<<endl;
        cout << "Bubble Sort:\n";
        cout << "Execution Time: " << timeExecuted1 << " seconds\n";

        cout << "" << endl;

        cout << "Merge Sort:\n";
        cout << "Execution Time: " << timeExecuted2 << " seconds\n";

    }

    // Print formulas only once at the end
    cout << "\n--- Summary of Time Complexity Formulas ---\n";
    cout << "Bubble Sort: O(n^2)\n";
    cout << "Merge Sort: O(n log n)\n";

    return 0;
} //main

