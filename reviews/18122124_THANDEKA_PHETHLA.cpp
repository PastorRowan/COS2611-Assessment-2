// COS2611 Assessment 2 Project 1

// Student Number:18122124

// T PHETHLA



#include <iostream>

#include <vector>

#include <ctime>

#include <cstdlib>

#include <cmath>



using namespace std;


// Bubble Sort



void bubbleSort(vector<int>& arr)

{

    int n = arr.size();

    // Swapped flag to indicate whether a swapped occured during a pass
    bool swapped;

    for (int i = 0; i < n - 1; i++)

    {

        // Set swapped to false at the start of each pass
        swapped = false;

        for (int j = 0; j < n - i - 1; j++)

        {

            if (arr[j] > arr[j + 1])

            {

                swap(arr[j], arr[j + 1]);
                // A swap occured: set swapped flag to true
                swapped = true;
            }

        }

        // If no swaps occurred during a full pass, the array is already sorted
        if (swapped == false) {
            break; // or return;
        };

    }

}


// Quick Sort



int partition(vector<int>& arr, int low, int high)

{

    int pivot = arr[high];

    int i = low - 1;



    for (int j = low; j < high; j++)

    {

        if (arr[j] < pivot)

        {

            i++;

            swap(arr[i], arr[j]);

        }

    }



    swap(arr[i + 1], arr[high]);



    return i + 1;

}



void quickSort(vector<int>& arr, int low, int high)

{

    if (low < high)

    {

        int pi = partition(arr, low, high);



        quickSort(arr, low, pi - 1);

        quickSort(arr, pi + 1, high);

    }

}





// Generating  random arra


vector<int> generateRandomArray(int size)

{

    vector<int> arr(size);



    for (int i = 0; i < size; i++)

    {

        arr[i] = rand() % 1000;

    }



    return arr;

}



// Measure Bubble Sort



void measureSortingTimeFirstSortingAlgorithm(vector<int>& arr,

    double& timeExecuted,

    double& timeComplexity)

{

    vector<int> copy = arr;



    clock_t startTime = clock();



    bubbleSort(copy);



    clock_t endTime = clock();



    timeExecuted = (double)(endTime - startTime) / CLOCKS_PER_SEC;



    timeComplexity = pow(arr.size(), 2);   // O(n²)

}




// Measure Quick Sort



void measureSortingTimeSecondSortingAlgorithm(vector<int>& arr,

    double& timeExecuted,

    double& timeComplexity)

{

    vector<int> copy = arr;



    clock_t startTime = clock();



    quickSort(copy, 0, copy.size() - 1);



    clock_t endTime = clock();



    timeExecuted = (double)(endTime - startTime) / CLOCKS_PER_SEC;



    timeComplexity = arr.size() * log2(arr.size());   // O(n log n)

}




// Main



int main()

{

    srand(time(0));



    cout << "COS2611 Assessment 2 Project 1\n\n";



    vector<int> inputSizes = { 100, 1000, 5000 };



    cout << "Size\tBubble(s)\tQuick(s)\tBubble Complexity\tQuick Complexity\n";

    cout << "-\n";



    for (int size : inputSizes)

    {

        vector<int> arr = generateRandomArray(size);



        double timeExecuted1, timeExecuted2;

        double timeComplexity1, timeComplexity2;



        measureSortingTimeFirstSortingAlgorithm(arr,

            timeExecuted1,

            timeComplexity1);



        measureSortingTimeSecondSortingAlgorithm(arr,

            timeExecuted2,

            timeComplexity2);



        cout << size << "\t"

            << timeExecuted1 << "\t\t"

            << timeExecuted2 << "\t\t"

            << timeComplexity1 << "\t\t"

            << timeComplexity2 << endl;

    }



    return 0;

}