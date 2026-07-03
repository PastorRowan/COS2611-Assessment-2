//NAME:CEBELIHLE
//SURNAME: KHANYILE
//STUDENT NO: 66881749
#include <iostream>
#include <chrono>
#include<cstdlib>
#include<ctime>
#include<iomanip>
using namespace std;
using namespace chrono;

void BubbleSort(int array[], int size);
void fillRandom(int array[], int size, int min, int max);
void heapSort(int arr[], int n);

int main()
{
    srand(time(0));

    //sizes for 3 different arrays
    const int size1 = 100;
    const int size2 = 1000;
    const int size3 = 5000;

    //3 different arrays
    int numbers100[size1];
    int numbers1000[size2];
    int numbers5000[size3];

    //random function called to fill up the arrays with random values
    fillRandom(numbers100, size1, 1, 100);
    fillRandom(numbers1000, size2, 1, 1000);
    fillRandom(numbers5000, size3, 1, 5000);

    //timer for array of 100  bubble sort
    auto bubblestart = high_resolution_clock::now();
    BubbleSort(numbers100, size1);
    auto bubblestop = high_resolution_clock::now();
    auto bubbleduration = duration_cast<microseconds>(bubblestop - bubblestart);

    //timer for array of 100 heap sort
    auto heapstart = high_resolution_clock::now();
    heapSort(numbers100, size1);
    auto heapstop = high_resolution_clock::now();
    auto heapduration = duration_cast<microseconds>(heapstop - heapstart);

    //report for array of 100 in microseconds 
    cout << "input size : 100" << endl;
    cout << endl;
    cout << "Bubble sort" << endl;
    cout << "execution time :" <<bubbleduration.count() << " microseconds" << endl;
    cout << endl;
    cout << "heap Sort" << endl;
    cout << "execution time :" <<heapduration.count() << " microseconds" << endl;
    cout << endl;

    cout << "==========================================" << endl;

    //timer for array of 1000 bubbleSort
    auto bubblestart2 = high_resolution_clock::now();
    BubbleSort(numbers1000, size2);
    auto bubblestop2 = high_resolution_clock::now();
    auto bubbleduration2 = duration_cast<microseconds>(bubblestop2 - bubblestart2);

    //timer for array of 1000 heapsort
    auto heapstart2 = high_resolution_clock::now();
    heapSort(numbers1000, size2);
    auto heapstop2 = high_resolution_clock::now();
    auto heapduration2 = duration_cast<microseconds>(heapstop2 - heapstart2);

    //report for array of 1000 in microseconds
    cout << "input size : 1000" << endl;
    cout << endl;
    cout << "Bubble sort" << endl;
    cout << "execution time :" << bubbleduration2.count() << " microseconds" << endl;
    cout << endl;
    cout << "heap Sort" << endl;
    cout << "execution time :" << heapduration2.count() << " microseconds" << endl;
    cout << endl;

    cout << "==========================================" << endl;

    //timer for array of 5000 bubble sort
    auto bubblestart3 = high_resolution_clock::now();
    BubbleSort(numbers5000, size3);
    auto bubblestop3 = high_resolution_clock::now();
    auto bubbleduration3 = duration_cast<microseconds>(bubblestop3 - bubblestart3);

    //timer for array of 5000 heap sort
    auto heapstart3 = high_resolution_clock::now();
    heapSort(numbers5000, size3);
    auto heapstop3 = high_resolution_clock::now();
    auto heapduration3 = duration_cast<microseconds>(heapstop3 - heapstart3);

    // report for array of 5000 in micro seconds
    cout << "input size : 5000" << endl;
    cout << endl;
    cout << "Bubble sort" << endl;
    cout << "execution time :" <<bubbleduration3.count() << " microseconds" << endl;
    cout << endl;
    cout << "heap Sort" << endl;
    cout << "execution time :" <<heapduration3.count() << " microseconds" << endl;
    cout << endl;
    
    cout << "==========================================" << endl;

    cout << "the time complexity formular for bubbleSort : O(n^2)"<< endl;
    cout << "the time complexity formular for heapSort : O(nLogn)"<< endl;
    return 0;

    //NB DUE TO MY COMPUTER SPEEDS I USED MICROSECONDS INSTEAD OF SECONDS//
}
//function definations
void BubbleSort(int array[], int size)
{
	for (int i = 1; i < size; i++)
	{
		for (int index = 0; index < size - i; index++)
		{
			if (array[index] > array[index + 1])
			{
				int temp = array[index];
				array[index] = array[index + 1];
				array[index + 1] = temp;
			}
		}

	}
}

void fillRandom(int array[], int size, int min, int max)
{
	for (int i = 0; i < size; i++)
	{
		array[i] = min + rand() % (max - min + 1);
	}
}
//heapfiy section 
void heapify(int array[], int n, int i)
{
    int largest = i;     
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    
    if (left < n && array[left] > array[largest])
        largest = left;
    if (right < n && array[right] > array[largest])
        largest = right;
    if (largest != i)
    {
        swap(array[i], array[largest]);
        heapify(array, n, largest);
    }
}

// Heap Sort function
void heapSort(int array[], int n)
{
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(array, n, i);
    }

    // Extract elements one by one
    for (int i = n - 1; i > 0; i--)
    {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}
