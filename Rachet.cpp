#include "Rachet.h"

//Rachet class implimentation
template <class T>
void bubbleSort(std::vector<T> &thisVector, int sortType) {

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

template <class T>
void quickSort(std::vector<T> &thisVector, int low, int high, int sortType) {

	T temp;
	//break recursion if only element
	if (low == high) return;

	/*break recursion if only 2 elements
	swap elements if out of order*/
	if (high - low == 1) {
		if (sortType == SMALL_BIG && thisVector[low] > thisVector[high]) {
			temp = thisVector[low];
			thisVector[low] = thisVector[high];
			thisVector[high] = temp;
		}
		else if (sortType == BIG_SMALL && thisVector[low] < thisVector[high]) {
			temp = thisVector[low];
			thisVector[low] = thisVector[high];
			thisVector[high] = temp;
		}
		return;
	}

	//pick a pivot point (first element in range
	int pivot = low;

	//put pivot in the right position in the vector
	int elementsSmaller = 0;

	for (int x = low; x <= high; x++) {
		if (thisVector[x] <= thisVector[pivot]) elementsSmaller++;
	}
	temp = thsVector[pivot];
	thisVector[pivot] = thisVector[low + elementsSmaller];
	thisVector[low + elementsSmaller] = temp;
	pivot = low + elementsSmaller;

	//migrate elements to the correct side of the pivot
	int index = low;

	for (int x = low; x <= high; x++) {
		if (thisVector[x] <= thisVector[pivot]) {
			temp = thisVector[x];
			thisVector[x] = thisVector[index];
			thisVector[index] = temp;
			index++;
		}
	}

	//Recurse
	quickSort(&thisVector, low, pivot, sortType);
	quickSort(&thisVector, pivot, high, sortType);

	return;
}



template <class T>
void heapSort(std::vector<T> & thisVector, const int sortType) {

	for (int x = thisVector.size() - 1; x >= 0; x--) {
		
		//heap remaining portion of vector
		for (int y = ((x / 2) - 1); y >= 0; y--) {
			heapSection(thisVector, y, sortType);
		}

		//swap head to last unlocked space
		std::swap(thisVector[0], thisVector[x]);

		//space isolated in next loop
	}
	return;
}