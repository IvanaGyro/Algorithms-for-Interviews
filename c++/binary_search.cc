// C++ program to variants of Binary Search
#include <iostream>
#include <vector>
#include "test.h"

using namespace std;

int n = 8; // array size
int a[] { 2, 3, 3, 5, 5, 5, 6, 6 }; // Sorted array

/* Find if key is in array
* Returns: True if key belongs to array,
*		 False if key doesn't belong to array */
bool contains(int low, int high, int key)
{
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (a[mid] < key) low = mid + 1;
		else high = mid - 1;
	}
	return low < n && a[low] == key;
}

/* Find first occurrence index of key in array
* Returns: an index in range [0, n-1] if key belongs 
*		 to array, -1 if key doesn't belong to array
*/
int first(int low, int high, int key)
{
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (a[mid] < key) low = mid + 1;
		else high = mid - 1;
	}
	return low < n && a[low] == key ? low : -1;
}

/* Find last occurrence index of key in array
* Returns: an index in range [0, n-1] if key 
			belongs to array,
*		 -1 if key doesn't belong to array
*/
int last(int low, int high, int key)
{
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (key < a[mid]) high = mid - 1;
		else low = mid + 1;
	}

	return high >= 0 && a[high] == key ? high : -1;
}

/* Find index of first occurrence of least element 
greater than key in array
* Returns: an index in range [0, n-1] if key is not
			the greatest element in array,
*		 -1 if key is the greatest element in array */
int leastgreater(int low, int high, int key)
{
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (key < a[mid]) high = mid - 1;
		else low = mid + 1;
	}

	return low < n ? low : -1;
}

/* Find index of last occurrence of greatest element
less than key in array
* Returns: an index in range [0, n-1] if key is not 
			the least element in array,
*		 -1 if key is the least element in array */
int greatestlesser(int low, int high, int key)
{
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (a[mid] < key) low = mid + 1;
		else high = mid - 1;
	}

	return high >= 0 ? high : -1;
}

int main()
{
	vector<int> ans(10);

	cout << "Contains" << endl;
	for (int i = 0; i < 10; i++)
		ans[i] = contains(0, n -1, i);
	test(ans, {0, 0, 1, 1, 0, 1, 1, 0, 0, 0});

	cout << "First occurrence of key" << endl;
	for (int i = 0; i < 10; i++)
		ans[i] = first(0, n -1, i);
	test(ans, {-1, -1, 0, 1, -1, 3, 6, -1, -1, -1});

	cout << "Last occurrence of key" << endl;
	for (int i = 0; i < 10; i++)
		ans[i] = last(0, n -1, i);
	test(ans, {-1, -1, 0, 2, -1, 5, 7, -1, -1, -1});

	cout << "Least integer greater than key" << endl;
	for (int i = 0; i < 10; i++)
		ans[i] = leastgreater(0, n -1, i);
	test(ans, {0, 0, 1, 3, 3, 6, -1, -1, -1, -1});

	cout << "Greatest integer lesser than key" << endl;
	for (int i = 0; i < 10; i++)
		ans[i] = greatestlesser(0, n -1, i);
	test(ans, {-1, -1, -1, 0, 2, 2, 5, 7, 7, 7});
}
