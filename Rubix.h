#include <vector>
#include <array>

#ifndef RUBIX_H
#define RUBIX_H

//Sorting and manipulation algorithms namespace
namespace Rubix {

	enum sortType { BIG_SMALL, SMALL_BIG };

	//Takes a vector and return the maximum value
	template<class T>
	T getMax(const std::vector<T> thisVector) {
		int target = 0;

		for (int x = 1; x < thisVector.size(); x++) {
			if (thisVector[x] > thisVector[target]) 
				target = x;
		}

		return thisVector[target];
	}

	//Takes a vector and return the minimum value
	template<class T>
	T getMin(const std::vector<T> thisVector) {
		int target = 0;

		for (int x = 1; x < thisVector.size(); x++) {
			if (thisVector[x] < thisVector[target])
				target = x;
		}

		return thisVector[target];
	}

	/*
	Fully orders the input vector using a bubble sort procedure
	SortTypes: 0 = BIG->SMALL, 1 = SMALL->BIG*/
	template <class T>
	void bubbleSort(std::vector<T> &thisVector, const int sortType) {

		bool sorted = true;
		T temp;

		switch (sortType) {

		case BIG_SMALL:
			do {
				sorted = true;

				for (int x = 0; x < thisVector.size() - 1; x++) {

					if (thisVector[x] < thisVector[x + 1]) {
						sorted = false;

						temp = thisVector[x + 1];
						thisVector[x + 1] = thisVector[x];
						thisVector[x] = temp;
					}
				}
			} while (sorted == false);

			break;
		case SMALL_BIG:
			do {
				sorted = true;

				for (int x = 0; x < thisVector.size() - 1; x++) {

					if (thisVector[x] > thisVector[x + 1]) {
						sorted = false;

						temp = thisVector[x + 1];
						thisVector[x + 1] = thisVector[x];
						thisVector[x] = temp;
					}
				}
			} while (sorted == false);

			break;
		}
		return;
	}

	/*
	Fully orders the input vector using a quick sort procedure
	SortTypes: 0 = BIG->SMALL, 1 = SMALL->BIG*/
	template <class T>
	void quickSort(std::vector<T> &thisVector, const int low, const int high, const int sortType) {

		//recursion base case check
		if (low < high) {
			//sort the section
			int position = quickSection(thisVector, low, high, sortType);

			//recurse the left and right side of the vector
			quickSort(thisVector, low, position - 1, sortType);
			quickSort(thisVector, position + 1, high, sortType);
		}
		return;
	}

	/*
	Subfunction of quick sort that picks a pivot point and
	migrates values to the correct side of the vector
	SortTypes: 0 = BIG->SMALL, 1 = SMALL->BIG*/
	template<class T>
	int quickSection(std::vector<T> &thisVector, const int low, const int high, const int sortType) {

		T pivot = thisVector[high]; //set the pivot point to the highest value in this section.
		int i = low;//set the position where the sorting section will swap the value too

		switch (sortType) {
		case SMALL_BIG:
			//put all the elements of the section that are less than the pivot to the left side
			for (int j = low; j <= high - 1; j++) {
				if (thisVector[j] <= pivot) {
					std::swap(thisVector[i], thisVector[j]);
					i++; //incriment the position where we are swapping the value to the next position up
				}
			}

			//swap the pivot point to the next position
			std::swap(thisVector[i], thisVector[high]);

			break;
		case BIG_SMALL:
			//put all the elements of the section that are more than the pivot to the left side
			for (int j = low; j <= high - 1; j++) {
				if (thisVector[j] >= pivot) {
					std::swap(thisVector[i], thisVector[j]);
					i++; //incriment the position where we are swapping the value to the next position up
				}
			}

			//swap the pivot point to the next position
			std::swap(thisVector[i], thisVector[high]);

			break;
		}

		return i;

	}

	/*
	Fully orders the input vector using a merge sort procedure.
	This function sorts the whole array from 0 to (size - 1)
	SortTypes: 0 = BIG->SMALL, 1 = SMALL->BIG*/
	template<class T>
	void mergeSort(std::vector<T> &thisVector, const int sortType) {

		//establish midpoint
		int middle = thisVector.size() / 2;

		//recurse merge sort on both sections
		mergeSort(thisVector, 0, middle, sortType);
		mergeSort(thisVector, middle + 1, thisVector.size() - 1, sortType);

		//remerge
		merge(thisVector, 0, middle, thisVector.size() - 1, sortType);

		return;
	}

	/*Sub function for the main merge funciton*/
	template<class T>
	void mergeSort(std::vector<T> &thisVector, int left, int right, const int sortType) {

		int middle;

		//check if more than one item in this partition
		if (left < right) {
			//set midpoint for partition
			middle = left + (right - left) / 2;

			//recurse merge sort on both halves
			mergeSort(thisVector, left, middle, sortType);
			mergeSort(thisVector, middle + 1, right, sortType);

			merge(thisVector, left, middle, right, sortType);
		}

	}

	//merge two ranges of values back in the correct order
	template<class T>
	void merge(std::vector<T> & thisVector, int left, int middle, int right, const int sortType) {

		//Temporary Storage Arrays left and right
		std::vector<T> ArrayL;
		ArrayL.resize(middle - left + 1);
		std::vector<T> ArrayR;
		ArrayR.resize(right - middle);
	
		int countL = 0;
		int countR = 0;

		//populate the left and right storage arrays
		for (countL; left + countL <= middle; countL++)
			ArrayL[countL] = thisVector[countL + left];
		for (countR; middle + countR < right; countR++)
			ArrayR[countR] = thisVector[countR + middle + 1];

		int indexL = 0, indexR = 0, indexM = left;

		//sort and repopulate the range until one of the lists is empty
		switch (sortType) {
		case SMALL_BIG:
			while (indexL < countL && indexR < countR) {

				if (ArrayL[indexL] < ArrayR[indexR]) {
					thisVector[indexM] = ArrayL[indexL];
					indexL++;
				}
				else {
					thisVector[indexM] = ArrayR[indexR];
					indexR++;
				}
				indexM++;
			}
		case BIG_SMALL:
			while (indexL < countL && indexR < countR) {

				if (ArrayL[indexL] > ArrayR[indexR]) {
					thisVector[indexM] = ArrayL[indexL];
					indexL++;
				}
				else {
					thisVector[indexM] = ArrayR[indexR];
					indexR++;
				}
				indexM++;
			}
		}

		//copy final element(s) into the range
		while (indexL < countL) {
			thisVector[indexM] = ArrayL[indexL];
			indexL++;
			indexM++;
		}
		while (indexR < countR) {
			thisVector[indexM] = ArrayR[indexR];
			indexR++;
			indexM++;
		}

		return;
	}

	/*
	Fully orders the input vector using a heaping procedure
	SortTypes: 0 = BIG->SMALL, 1 = SMALL->BIG*/
	template <class T>
	void heapSort(std::vector<T> & thisVector, const int sortType) {

		//heapify the vector (first heaping)
		for (int i = (thisVector.size() / 2) - 1; i >= 0; i--)
			heapify(thisVector, thisVector.size(), i, sortType);

		//Extract and reheap remainder of heap in loop
		for (int i = thisVector.size() - 1; i >= 0; i--) {

			//Move current root to end of heap
			std::swap(thisVector[0], thisVector[i]);

			//re-establish heap integrity
			heapify(thisVector, i, 0, sortType);
		}

		return;
	}

	/*
	Heaping procedure
	"Root" should first be first element you need to run.
	Highest/lowest value item will float to position 0.
	*First run of the heaping procedure should be called in loop from (vector.size() - 1) to 0 to establish heap structure
	*Subsiquent runs, where position 0 is no longer the smallest/largest value should be called once from position 0 to maintain heap integrity
	limit = the last position that is still active in the heap
	SortTypes: 0 = BIG->SMALL, 1 = SMALL->BIG*/
	template <class T>
	void heapify(std::vector<T> &thisVector, const int limit ,const int root, const int sortType) {

		//establish what the left and right legs of the tree are
		int left = root * 2 + 1;
		int right = root * 2 + 2;

		//determine which if any two elements to swap
		T value = thisVector[root];
		int target = root;

		switch (sortType) {
		case BIG_SMALL:
			if (left < limit && thisVector[left] < thisVector[target]) {
				value = thisVector[left];
				target = left;
			}
			if (right < limit && thisVector[right] < thisVector[target]) {
				value = thisVector[right];
				target = right;
			}
			break;
		case SMALL_BIG:
			if (left < limit && thisVector[left] > thisVector[target]) {
				value = thisVector[left];
				target = left;
			}
			if (right < limit && thisVector[right] > thisVector[target]) {
				value = thisVector[right];
				target = right;
			}
			break;
		}

		//swap elements
		if (target != root) {
			std::swap(thisVector[root], thisVector[target]);

			//re-establish heap integrity from root downwards
			heapify(thisVector, limit, target, sortType);
		}
		return;
	}

	/*
	Fully orders the input vector using a selection sort procedure
	SortTypes: 0 = BIG->SMALL, 1 = SMALL->BIG*/
	template<class T>
	void selectionSort(std::vector<T> &thisVector, const int sortType) {

		int i = 0;
		T value;
		int target;

		do {
			//set the initial value to beat 
			value = thisVector[i];
			target = i;

			switch (sortType) {
			case SMALL_BIG:
				//find the next smallest value from the remainder of the list
				for (int y = i; y < thisvector.size(); y++) {
					if (thisVector[y] < value) {
						value = thisVector[y];
						target = y;
					}
				}
				break;
			case BIG_SMALL:
				//find the next largest value from the remaider of the list
				for (int y = i; y > thisvector.size(); y++) {
					value = thisVector[y];
					target = y;
				}
				break;
			}

			i++; //move up which position we are writting too
		} while (i < thisVector.size() - 1);
		
		return;
	}

	/*
	Fully orders the input vector using a counting sort procedure
	*time to complete this sort varies significantly based on the size of the range of possible variables
	*uses additional memory for the duration of the sort
	*ONLY USEABLE FOR NON-DECIMAL DATA-TYPES
	Inputs:
	1. The vector
	2. The range of possible values (LOW)
	3. The range of possible values (HIGH)
	4. the type of sort
	SortTypes: 0 = BIG->SMALL, 1 = SMALL->BIG*/
	template<class T> 
	void countingSort(std::vector<T> &thisVector, const int sortType) {

		//run through once too determine the high and low value
		T low = getMin(thisVector); 
		T high = getMax(thisVector);

		//setup the possible values the vector could hold
		std::vector<T> range;
		range.resize(high - low + 1);// {low, ..., high} all values start at 0

		//tally up how many times each number in the range appears
		for (int x = 0; x < thisVector.size(); x++) {
			range[thisVector[x] - low]++;
		}

		//rewrite the array in the right order.
		int position = 0; //relative position in the vector to write too.
		int Offset = 0; //the number being written as an offset from the low position.

		switch (sortType) {
		case SMALL_BIG:
			do {
				for (int x = 0; x < range[Offset]; x++) {
					thisVector[position] = low + Offset;
					position++;
				}
				Offset++; //iterate
			} while (Offset < (high - low + 1));
			break;
		case BIG_SMALL:
			do {
				for (int x = 0; x < range[Offset]; x++) {
					thisVector[position] = high - Offset;
					position++;
				}
				Offset++; //iterate
			} while (Offset < (high - low + 1));
			break;
		}

		return;
	}
	
	/*
	Fully orders the input vector using a radix sort procedure
	*time to complete DOES NOT vary based on the size of the range of possible variables
	*doubles input array's memory usage for duration of the sort
	SortTypes: 0 = BIG->SMALL, 1 = SMALL->BIG
	TO DO: CURRENTLY ONLY USABLE FOR NON-DECIMAL DATA-TYPES*/
	template<class T>
	void radixSort(std::vector <T> &thisVector, const int sortType) {

		T max = getMax(thisVector);
		int count[10] = { 0 };//component of sub-sort that tallys the number of occurences of 0-9 in the selected digit
		std::vector<T> output;//temporary vector written too before writing to the input vector
		output.resize(thisVector.size());

		//repeat sorting operation for each digit
		for (int digit = 1; (max / digit) > 0; digit *= 10) {
			//zero out count for next round
			for (int i = 0; i < 10; i++)
				count[i] = 0;

			//count the number of occurences of each number 0-9 in this digit
			for (int i = 0; i < thisVector.size(); i++)
				count[(thisVector[i] / digit) % 10]++;

			/*convert count into an array that calculates at what position the last value with the number 0-9 would be
			when building the array count also tracks what position in the array the next value will be added*/
			switch (sortType) {
			case BIG_SMALL:
				for (int i = 8; i >= 0; i--)
					count[i] += count[i + 1];
				break;
			case SMALL_BIG:
				for (int i = 1; i < 10; i++)
					count[i] += count[i - 1];
				break;
			}

			/*build output array based on the next position that a value ending in this number 0-9 can be placed
			*Decrimenting instead of incrimenting in order to preserve the relative position of previous iterations.
			*Since the counter is tracking next position right to left we need to read in positions right to left*/
			for (int i = thisVector.size() - 1; i >= 0; i--) {
				output[count[(thisVector[i] / digit) % 10] - 1] = thisVector[i];
				//decriment so count for that number 0-9 is now in the next position where a value of that number 0-9 should go
				count[(thisVector[i] / digit) % 10]--;
			}

			//copy output array to the original
			for (int i = 0; i < thisVector.size(); i++)
				thisVector[i] = output[i];
		}
		return;
	}

	/*
	Fully orders the input vector using bucket sort procedure
	Useful for sorting doubles/floats spread over a range of 0.0 to 1.0
	SortTypes: 0 = BIG->SMALL, 1 = SMALL->BIG*/
	template<class T>
	void bucketSort(std::vector<T> &thisVector, const int sortType) {



		return;
	}

	/*
	Fully order the input using gnome sort procedure
	best used on lists that are already partially sorted
	SortTypes: 0 = BIG->SMALL, 1 = SMALL->BIG*/
	template<class T>
	void gnomeSort(std::vector<T> &thisVector, const int sortType) {
		
		
		
		return;
	}

	void pattern(int num) {
		
		if (num == 0) {
			std::cout << "0 ";
		}
		else {
			pattern(num - 1);
			std::cout << num << " ";
			pattern(num - 1); 
		}
		
		return;
	}
}

#endif