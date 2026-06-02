
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <iomanip>

// Generates a random unsigned integer in the range [min, max] (inclusive)
unsigned int ran(const unsigned int min, const unsigned int max) {

    static  std::random_device rd;
    static  std::mt19937 gen(rd());

    std::uniform_int_distribution<unsigned int> dist(min, max);

    return dist(gen);

};

/**
 * Checks whether a vector is sorted in ascending order
 * Returns true if sorted in ascending order, false otherwise
 */
bool isAscending(const std::vector<unsigned int>& arr) {

    for (unsigned int i = 0; i < arr.size() - 2; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        };
    };
    return true;

};

// Prints all elements of a vector to the console
void printVec(const std::vector<unsigned int>& arr) {
    for (unsigned int num : arr) {
        std::cout << num << " ";
    };
    std::cout << std::endl;
};

// Sorts a vector using Bubble Sort algorithm
void bubbleSort(std::vector<unsigned int>& arr) {

    bool swapped;

    // Outer loop controls number of passes
    for (unsigned int i = 0; i < arr.size() - 1; i++) {

        swapped = false;

        // Inner loop compares adjacent elements
        for (unsigned int j = 0; j < arr.size() - 2 - i; j++) {

            // Swap elements next to each other if left element is greater than right element
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            };

        };

        // If no swaps occurred during a full pass, the array is already sorted
        if (swapped == false) {
            break;
        };

    };

};

/**
 * Recursive merge sort implementation.
 *
 * Divides the vector into two halves, recursively sorts each half,
 * and then merges the sorted halves into a temporary buffer.
 */
void mergeSort(
    std::vector<unsigned int>& arr, 
    std::vector<unsigned int>& temp, 
    const int left,
    const int right
) {

    /*
    Base case
    single element is already sorted
    */
    if (left >= right)
        return;

    const unsigned int mid = (left + right) / 2;
    const unsigned int rightStart = mid + 1;

    // Recursively sort left half
    mergeSort(arr, temp, left, mid);

    // Recursively sort right half
    mergeSort(arr, temp, rightStart, right);

    /**
     * Merge step
     * At this point, both halves are sorted
     */

    unsigned int leftIndex = left;
    unsigned int rightIndex = rightStart;
    unsigned int tempPos = left;
    const unsigned int numElements = right - left + 1;

    // Merge by selecting smallest front element from each half
    while (leftIndex <= mid && rightIndex <= right) {
        if (arr[leftIndex] <= arr[rightIndex]) {
            temp[tempPos] = arr[leftIndex];
            tempPos++;
            leftIndex++;
        } else {
            temp[tempPos] = arr[rightIndex];
            tempPos++;
            rightIndex++;
        };
    };

    /*
    Note:
        Only one of these loops runs to copy the remaining elements of the other loop that
        was not copied during the previous while loop
    */

    // Copy remaining elements from left half
    while (leftIndex <= mid) {
        temp[tempPos] = arr[leftIndex];
        tempPos++;
        leftIndex++;
    };

    // Copy remaining elements from right half
    while (rightIndex <= right) {
        temp[tempPos] = arr[rightIndex];
        tempPos++;
        rightIndex++;
    };

    // Copy merged result back into original array
    for (unsigned int i = 0; i < numElements; i++) {
        arr[left + i] = temp[left + i];
    };

};

/**
 * Function to intially call merge sort
 * Creates a temporary vector once and calls the recursive mergeSort function with it
 */
void mergeSortInitialCall(std::vector<unsigned int>& arr) {

    std::vector<unsigned int> temp(arr.size());

    const unsigned int
        firstLeft = 0,
        firstRight = arr.size() - 1
    ;

    mergeSort(arr, temp, firstLeft, firstRight);

};

// Formats nanoseconds into a human-readable seconds string.
std::string formatNanoseconds(const unsigned long long nanoseconds) {

    std::string nanoseconds_str = std::to_string(nanoseconds);
    
    // Ensure minimum length for decimal formatting
    while (nanoseconds_str.length() < 10) {
        nanoseconds_str = "0" + nanoseconds_str;
    };

    // Insert decimal point to convert nanoseconds to seconds
    nanoseconds_str.insert(nanoseconds_str.length() - 9, ".");

    // Trim trailing zeros
    while (nanoseconds_str.back() == '0') {
        nanoseconds_str.pop_back();
    };

    // Remove trailing decimal point if needed
    if (nanoseconds_str.back() == '.') {
        nanoseconds_str.pop_back();
    };

    return nanoseconds_str;

};

// Stores benchmark results for a given input size
struct Test {

    // Constructs a test case with a given number of elements
    Test(
        const unsigned int numberItemsP
    ): numberItems(numberItemsP) {};

    // Number of elements in the test

    const unsigned int numberItems;

    // Execution time of bubble sort (nanoseconds)
    unsigned long long bubbleSortExecutionTime = 0;

    // Execution time of merge sort (nanoseconds)
    unsigned long long mergeSortExecutionTime = 0;

};

// Prints benchmark results for a single test case
void printTest(const Test& test) {

    std::string
        bubbleSortExecTimeSeconds = formatNanoseconds(test.bubbleSortExecutionTime),
        mergeSortExecTimeSeconds = formatNanoseconds(test.mergeSortExecutionTime)
    ;

    std::cout
        << "Input Size: " << test.numberItems << std::endl
        << std::endl
        << "Bubble Sort:" << std::endl
        << "Execution Time: " << bubbleSortExecTimeSeconds << 's' << std::endl
        << std::endl
        << "MergeSort:" << std::endl
        << "Execution Time: " << mergeSortExecTimeSeconds << 's' << std::endl
    ;

};

int main() {

    const unsigned int NUMBER_OF_TESTS = 3;

    // Predefined test sizes
    Test tests[NUMBER_OF_TESTS] = {
        Test(100),
        Test(1000),
        Test(5000)
    };

    std::cout << std::endl;

    // Loop over the tests
    for (unsigned int i = 0; i < NUMBER_OF_TESTS; i++) {

        Test& currentTest = tests[i];

        // Create identical datasets for fair comparison
        std::vector<unsigned int>
            bubbleSortArray(currentTest.numberItems),
            mergeSortArray(currentTest.numberItems)
        ;

        // Fill arrays with random values
        for (unsigned int j = 0; j < currentTest.numberItems; j++) {
            const unsigned int randomNumber = ran(0, 1000000);
            bubbleSortArray[j] = randomNumber;
            mergeSortArray[j] = randomNumber;
        };

        // Measure bubble sort
        auto bubbleSortTimeStart = std::chrono::high_resolution_clock::now();
        bubbleSort(bubbleSortArray);
        auto bubbleSortTimeEnd = std::chrono::high_resolution_clock::now();

        currentTest.bubbleSortExecutionTime =
            std::chrono::duration<unsigned long long, std::nano>(bubbleSortTimeEnd - bubbleSortTimeStart).count();

        // Measure merge sort
        auto mergeSortTimeStart = std::chrono::high_resolution_clock::now();
        mergeSortInitialCall(mergeSortArray);
        auto mergeSortTimeEnd = std::chrono::high_resolution_clock::now();

        currentTest.mergeSortExecutionTime =
            std::chrono::duration<unsigned long long, std::nano>(mergeSortTimeEnd - mergeSortTimeStart).count();


        // Validate both arrays are in sorted in ascending order
        if (!isAscending(bubbleSortArray)) {
            std::cout << "Error: bubbleSortStart is not sorted in asending order after being sorted, terminating program";
            return 1;
        };

        if (!isAscending(mergeSortArray)) {
            std::cout << "Error: mergeSortArray is not sorted in asending order after being sorted, terminating program";
            return 1;
        };

        std::cout << std::endl;

        printTest(currentTest);

        std::cout << std::endl;

    };

	return 0;

};
