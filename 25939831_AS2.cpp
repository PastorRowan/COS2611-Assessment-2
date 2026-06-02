
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <iomanip>

// Returns a random number from min to max (inclusive)
unsigned int ran(const unsigned int min, const unsigned int max) {

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<unsigned int> dist(min, max);

    return dist(gen);

};

// Returns true if the vector is in ascending order or false if it is not
bool isAscending(const std::vector<unsigned int>& arr) {
    for (unsigned int i = 0; i < arr.size() - 2; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        };
    };
    return true;
};

// Helper function to print vectors
void printVec(const std::vector<unsigned int>& arr) {
    for (unsigned int num : arr) {
        std::cout << num << " ";
    };
    std::cout << std::endl;
};

void bubbleSort(std::vector<unsigned int>& arr) {

		bool swapped;

        // Loop over all elements except the last
		for (unsigned int i = 0; i < arr.size() - 1; i++) {

			swapped = false;

            // Loop over all elements from the start to the line
			for (unsigned int j = 0; j < arr.size() - 2 - i; j++) {

                // Swap elements next to each other if left element is greater than right element
				if (arr[j] > arr[j + 1]) {
				    std::swap(arr[j], arr[j + 1]);
				    swapped = true;
				};

			};

            // If we go through a full iteration without swapping that means that the loop is already sorted
			if (swapped == false) {
			    break;
		    };

		};

};

void mergeSort(
    std::vector<unsigned int>& arr, 
    std::vector<unsigned int>& temp, 
    const int left,
    const int right
) {

    // Divide step


    // If size of array is 0 or 1 then it is already sorted so return
    if (left >= right)
        return;

    const unsigned int mid = (left + right) / 2;
    const unsigned int rightStart = mid + 1;

    // Sort left array
    mergeSort(arr, temp, left, mid);

    // Sort right array
    mergeSort(arr, temp, rightStart, right);

    // Merge step
    // During this part we assume that both left and right halves of the array are sorted
    // For example [1, 5] and [3, 4]
    // Now we combine both sorted halves

    unsigned int leftIndex = left;
    unsigned int rightIndex = rightStart;
    unsigned int tempPos = left;
    const unsigned int numElements = right - left + 1;

    // Compare the front elements of both halves
    // If left is smaller then insert left into temp
    // else insert right into temp
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

    // After left or right run out then copy the remaning of left and right
    while (leftIndex <= mid) {
        temp[tempPos] = arr[leftIndex];
        tempPos++;
        leftIndex++;
    };

    while (rightIndex <= right) {
        temp[tempPos] = arr[rightIndex];
        tempPos++;
        rightIndex++;
    };

    // copy back temp results back to the original array
    for (unsigned int i = 0; i < numElements; i++) {
        arr[left + i] = temp[left + i];
    };

};

void mergeSortInitialCall(std::vector<unsigned int>& arr) {

    std::vector<unsigned int> temp(arr.size());

    const unsigned int
        firstLeft = 0,
        firstRight = arr.size() - 1
    ;

    mergeSort(arr, temp, firstLeft, firstRight);

};

std::string formatNanoseconds(const unsigned long long nanoseconds) {
    std::string ns_str = std::to_string(nanoseconds);
    
    // Pad with leading zeros if length < 10 (so we have at least 1 digit before decimal)
    while (ns_str.length() < 10) {
        ns_str = "0" + ns_str;
    };

    // Insert decimal point 9 digits from right
    ns_str.insert(ns_str.length() - 9, ".");

    while (ns_str.back() == '0') {
        ns_str.pop_back();
    };

    // If ends with '.', remove it too
    if (ns_str.back() == '.') {
        ns_str.pop_back();
    };

    return ns_str;

};

struct Test {

    const unsigned int numberItems;

    unsigned long long
        bubbleSortExecutionTime = 0,
        mergeSortExecutionTime = 0
    ;

    void printTest() const {

        std::string
            bubbleSortExecTimeSeconds = formatNanoseconds(bubbleSortExecutionTime),
            mergeSortExecTimeSeconds = formatNanoseconds(mergeSortExecutionTime)
        ;

        std::cout
            << "Input Size: " << numberItems << std::endl
            << std::endl
            << "Bubble Sort:" << std::endl
            << "Execution Time: " << bubbleSortExecTimeSeconds << 's' << std::endl
            << std::endl
            << "MergeSort:" << std::endl
            << "Execution Time: " << mergeSortExecTimeSeconds << 's' << std::endl
        ;
    };

};

int main() {

    const unsigned int NUMBER_OF_TESTS = 3;

    std::vector<Test> tests;

    tests.reserve(NUMBER_OF_TESTS);

    tests.push_back({
        .numberItems = 100
    });

    tests.push_back({
        .numberItems = 1000
    });

    tests.push_back({
        .numberItems = 5000
    });

    std::cout << std::endl;

    for (unsigned int i = 0; i < tests.size(); i++) {

        Test& currentTest = tests[i];

        std::vector<unsigned int> arr1;
        arr1.reserve(currentTest.numberItems);
        for (unsigned int j = 0; j < currentTest.numberItems; j++) {
            arr1.push_back(ran(0, 1000000));
        };
        std::vector<unsigned int> arr2 = arr1;

        auto bubbleSortStart = std::chrono::high_resolution_clock::now();
        bubbleSort(arr1);
        auto bubbleSortEnd = std::chrono::high_resolution_clock::now();
        currentTest.bubbleSortExecutionTime =
            std::chrono::duration<unsigned long long, std::nano>(bubbleSortEnd - bubbleSortStart).count();

        auto mergeSortStart = std::chrono::high_resolution_clock::now();
        mergeSortInitialCall(arr2);
        auto mergeSortEnd = std::chrono::high_resolution_clock::now();
        currentTest.mergeSortExecutionTime =
            std::chrono::duration<unsigned long long, std::nano>(mergeSortEnd - mergeSortStart).count();

        if (!isAscending(arr1)) {
            std::cout << "arr1 is not sorted in asending order after being sorted, terminating program";
            exit(1);
            return 1;
        };

        if (!isAscending(arr2)) {
            std::cout << "arr2 is not sorted in asending order after being sorted, terminating program";
            exit(1);
            return 1;
        };

        std::cout << std::endl;

        currentTest.printTest();

        std::cout << std::endl;

    };

	return 0;

};
