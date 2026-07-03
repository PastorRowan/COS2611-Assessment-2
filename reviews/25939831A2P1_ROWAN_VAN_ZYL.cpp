//25939831
//Rowan Van Zyl

// See the Github repository at https://github.com/PastorRowan/COS2611-Assessment-2

#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;

//Function for the first sorting algorithm

// Sorts a vector using Bubble Sort algorithm
void bubbleSort(vector<int>& arr) {

    bool swapped;

    // Outer loop controls number of passes
    for (unsigned int i = 0; i < arr.size() - 1; i++) {

        swapped = false;

        // Inner loop compares adjacent elements
        for (unsigned int j = 0; j < arr.size() - 2 - i; j++) {

            // Swap elements next to each other if left element is greater than right element
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            };

        };

        // If no swaps occurred during a full pass, the array is already sorted
        if (swapped == false) {
            break;
        };

    };

};

//Function for the second sorting algorithm

/**
 * Recursive merge sort implementation.
 * 
 * Note:
 * 
 *     This is not the most efficient implementation of Merge Sort which would require a single
 *     large temp vector that gets allocated once.
 * 
 *     My version creates many smaller vectors which more directly maps to the
 *     Merge Sort algorithm but has more memory overhead.
 * 
 *     This version I understand but the other one I do not.
 *     Desipite this lack of optimsiation it still outperforms Bubble Sort by far.
 *     I do not know if that is because the compiler is optimising my code in some way
 *     or because Bubble Sort is that inefficient that an inefficient Merge Sort implementation still wins
 */
void mergeSort(
    vector<int>& arr
) {

    /**
     * Recursive divide step:
     * 
     * We are going to divide the array into left and right halves recursively (general case)
     * until the vector has 1 or 0 elements (base case) which means the vector is already sorted
     * After leftVec and rightVec are sorted merge them into a single sorted vector (merge step)
     */

    /**
     * Base case
     * 1 or less elements means vectors is already sorted
     */
    if (arr.size() <= 1) {
        return;
    };

    const unsigned int mid = arr.size() / 2;

    // Copy arr from beggining to the middle index - 1
    vector<int> leftVec(
        arr.begin(),
        arr.begin() + mid
    );

    // Copy arr from middle index to the end index of arr
    vector<int> rightVec(
        arr.begin() + mid,
        arr.end()
    );

    // Recursively sort left half
    mergeSort(leftVec);

    // Recursively sort right half
    mergeSort(rightVec);

    /**
     * Merge step:
     * 
     * At this point, both leftVec and rightVec are sorted and must be merged into a single sorted vector.
     * 
     * To do this we are going to iterate over both the left half and right half and full the big vector all
     * at the same time using leftIndex, rightIndex and arrayIndex respectively and and since leftVec and rightVec are
     * already sorted we do a (kind of) double vector insertion algorithm that requires only one pass.
     * 
     * Iterate over both vectors at the same time
     *     if leftIndex element is smaller than or equal to rightIndex element:
     *         copy the leftIndex element into the big array at arrayIndex then increment arrayIndex and leftIndex
     *         (to remove the element from leftVec)
     *     else:
     *         copy the rightIndex element into the big array at arrayIndex then increment arrayIndex and rightIndex
     *         (to remove the element from rightVec)
     *
     * Note that leftVec and rightVec might not be the same size so what could happen is that either leftIndex or rightIndex
     * could reach the end of their respective vectors meaning that that vector is essentially empty.
     * In that case the remaining elements of either leftIndex or rightIndex (only one will be used) will copy
     * The remaining elements into big vector.
     */

    // Using size_t because vector.size() returns size_t
    unsigned int leftIndex = 0;
    unsigned int rightIndex = 0;
    unsigned int arrayIndex = 0;

    // Merge by selecting smallest front element from each half
    while (leftIndex < leftVec.size() && rightIndex < rightVec.size()) {
        if (leftVec[leftIndex] <= rightVec[rightIndex]) {
            arr[arrayIndex] = leftVec[leftIndex];
            arrayIndex++;
            leftIndex++;
        } else {
            arr[arrayIndex] = rightVec[rightIndex];
            arrayIndex++;
            rightIndex++;
        };
    };

    /*
    Note:
        Only one of these loops runs to copy the remaining elements of the vector that did not run out
    */

    // Copy remaining elements from left half
    while (leftIndex < leftVec.size()) {
        arr[arrayIndex] = leftVec[leftIndex];
        arrayIndex++;
        leftIndex++;
    };

    // Copy remaining elements from right half
    while (rightIndex < rightVec.size()) {
        arr[arrayIndex] = rightVec[rightIndex];
        arrayIndex++;
        rightIndex++;
    };

    // At this point arr is sorted in ascending order

};

//Function to generate a random array of a given size
vector<int> generateRandomArray(
    const unsigned int size
) {

    vector<int> arr(size);

    srand(time(0));

    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000; //adjust the range to play around with it
    };
           
    return arr;

} //generateRandomArray


//you can make this more code efficient - did it this way for more clarity purposes

void measureSortingTimeFirstSortingAlgorithm(
    vector<int>& arr,
    double& timeExecuted,
    double& timeComplexity
) {

    //measure start time
    auto startTime = chrono::high_resolution_clock::now();
    
    //Call your first sorting algorithm
    bubbleSort(arr);

    //measure end time
    auto endTime = chrono::high_resolution_clock::now();

    //calculate executation time in secods for first sorting algorithm
    timeExecuted =
        static_cast<double>(
            chrono::duration_cast<chrono::nanoseconds>(
                endTime - startTime
            ).count()
        ) / 1000000000
    ;

    //calculate time comlexity for your sorting algorithm

    const unsigned int arrSize = arr.size();

    timeComplexity = arrSize * arrSize; //this will then be the time complexity - you must provide the code

} //measureSortingTimeFirstSortingAlgorithm



void measureSortingTimeSecondSortingAlgorithm(
    vector<int>& arr,
    double &timeExecuted,
    double &timeComplexity
) {

    //measure start time
    auto startTime = chrono::high_resolution_clock::now();

    //Call your second algortihm
    mergeSort(arr);

    //measure end time
    auto endTime = chrono::high_resolution_clock::now();

    //calculate executation time in secods for first sorting algorithm
    timeExecuted =
        static_cast<double>(
            chrono::duration_cast<chrono::nanoseconds>(
                endTime - startTime
            ).count()
        ) / 1000000000
    ;

    //calculate time comlexity for your sorting algorithm

    const double arrSizeDouble = arr.size();

    timeComplexity = arrSizeDouble * log2(arrSizeDouble); //this will then be the time complexity - you must provide the code

} //measureSortingTimeSecondSortingAlgorithm

/**
 * Checks whether a vector is sorted in ascending order
 * Returns true if sorted in ascending order, false otherwise
 */
bool isAscending(const vector<int>& arr) {
    for (unsigned int i = 1; i < arr.size() - 1; i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        };
    };
    return true;
};

int main() {

    cout
        << endl
        << endl
        << "COS2611 Assessment 2 Project 1 - Skeleton" << endl
        << "ARRAYS" << endl
        << endl
        << endl
    ;

    //generate an array with 100 random elements

    double timeExecuted1, timeExecuted2;
    double timeComplexity1, timeComplexity2;

    const vector<unsigned int> inputSizes = {
        100,
        1000,
        5000
    };

    for (const unsigned int size : inputSizes) {

        vector<int> vec1 = generateRandomArray(size);

        vector<int> vec2 = vec1;

        //measure the sorting time for first sorting algorithm
        measureSortingTimeFirstSortingAlgorithm(
            vec1,
            timeExecuted1,
            timeComplexity1
        );

        // Validate Bubble Sort vector is sorted in ascending order
        if (!isAscending(vec1)) {
            cout << "Error: 'vec1' is not sorted in asending order after being sorted, terminating program";
            return 1;
        };

        //measure the sorting time for second sorting algorithm
        measureSortingTimeSecondSortingAlgorithm(
            vec2,
            timeExecuted2,
            timeComplexity2
        );

        // Validate Merge  Sort vector is sorted in ascending order
        if (!isAscending(vec2)) {
            cout << "Error: 'vec2' is not sorted in asending order after being sorted, terminating program";
            return 1;
        };

        //The display of your results will go here.

        cout.precision(7);
        cout.setf(ios::fixed);

        cout
            << "Input Size: " << size << endl
            << endl
            << "Bubble Sort:" << endl
            << "Execution Time: " << timeExecuted1 << 's' << endl
            << endl
            << "MergeSort:" << endl
            << "Execution Time: " << timeExecuted2 << 's' << endl
            << endl
            << endl
        ;

    };

    /**
     * Bubble sort formula: O(n²)
     * Merge sort formula: O(nlog₂n)
     */
    cout
        << "The time complexity formula for Bubble Sort: O(n^2)" << endl
        << "The time complexity formula for Merge Sort: O( nlog_2(n) )" << endl
        << endl
    ;

    //the above may not be the best way to code it - it is just to give you a headstart.

    return 0;

} //main
