#include<array>
#include<vector>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include"Rubix.h"

template<class T>
void printVector(std::vector <T> theVector) {
	for (int x = 0; x < theVector.size(); x++) {
		std::cout << theVector[x] << " ";
	}
}

//shuffle 
template<class T>
void shuffle(std::vector <T> &theVector) {
	const int RUNS = 20;

	for (int x = 0; x < RUNS; x++) {
		std::swap(theVector[rand() % theVector.size()], theVector[rand() % theVector.size()]);
	}
	return;
}

int main() {
	using Rubix::sortType;
	using std::cout; using std::cin; using std::endl;

	srand(time(NULL));

	std::vector<int> theArray; //= {4,1,3,5,7,6,2,8,10,9};
	theArray.push_back(4);
	theArray.push_back(1);
	theArray.push_back(3);
	theArray.push_back(5);
	theArray.push_back(7);
	theArray.push_back(6);
	theArray.push_back(2);
	theArray.push_back(8);
	theArray.push_back(10);
	theArray.push_back(9);

	cout << endl << "Shuffling...";
	shuffle(theArray);
	cout << "Complete" << endl << endl;

	cout << "Unsorted: ";
	printVector(theArray);
	cout << endl;

	Rubix::bubbleSort(theArray, Rubix::BIG_SMALL);
	cout << "BubbleSort: ";
	printVector(theArray);
	cout << endl;

	Rubix::bubbleSort(theArray, Rubix::SMALL_BIG);
	cout << "BubbleSort: ";
	printVector(theArray);
	cout << endl;

	cout << endl << "Shuffling...";
	shuffle(theArray);
	cout << "Complete" << endl << endl;

	cout << "Unsorted: ";
	printVector(theArray);
	cout << endl;

	Rubix::quickSort(theArray, 0, theArray.size() - 1, Rubix::BIG_SMALL);
	cout << "QuickSort: ";
	printVector(theArray);
	cout << endl;

	Rubix::quickSort(theArray, 0, theArray.size() - 1, Rubix::SMALL_BIG);
	cout << "QuickSort: ";
	printVector(theArray);
	cout << endl;
	
	cout << endl << "Shuffling...";
	shuffle(theArray);
	cout << "Complete" << endl << endl;

	cout << "Unsorted: ";
	printVector(theArray);
	cout << endl;

	Rubix::heapSort(theArray, Rubix::BIG_SMALL);
	cout << "HeapSort: ";
	printVector(theArray);
	cout << endl;

	Rubix::heapSort(theArray, Rubix::SMALL_BIG);
	cout << "HeapSort: ";
	printVector(theArray);
	cout << endl;

	cout << endl << "Randomizing...";
	for (int x = 0; x < theArray.size(); x++)
		theArray[x] = rand() % 200;
	cout << "Complete" << endl << endl;

	cout << "Unsorted: ";
	printVector(theArray);
	cout << endl;

	Rubix::countingSort(theArray, Rubix::BIG_SMALL);
	cout << "CountingSort: ";
	printVector(theArray);
	cout << endl;

	Rubix::countingSort(theArray, Rubix::SMALL_BIG);
	cout << "CountingSort: ";
	printVector(theArray);
	cout << endl;

	cout << endl << "Shuffling...";
	shuffle(theArray);
	cout << "Complete" << endl << endl;

	cout << "Unsorted: ";
	printVector(theArray);
	cout << endl;

	Rubix::radixSort(theArray, Rubix::BIG_SMALL);
	cout << "RadixSort: ";
	printVector(theArray);
	cout << endl;

	Rubix::radixSort(theArray, Rubix::SMALL_BIG);
	cout << "RadixSort: ";
	printVector(theArray);
	cout << endl;

	cout << endl << "Shuffling...";
	shuffle(theArray);
	cout << "Complete" << endl << endl;

	cout << "Unsorted: ";
	printVector(theArray);
	cout << endl;

	Rubix::mergeSort(theArray, Rubix::BIG_SMALL);
	cout << "MergeSort: ";
	printVector(theArray);
	cout << endl;

	Rubix::mergeSort(theArray, Rubix::SMALL_BIG);
	cout << "MergeSort: ";
	printVector(theArray);
	cout << endl << endl;

	Rubix::pattern(7);

	cout << endl << "Press ENTER to continue...";
	cin.ignore();

	return 0;
}