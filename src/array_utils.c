/***************************************************************************
 *
 * 	Functions for searching and sorting arrays
 *
 *   File        	: array_utils.c
 *   Student Id  	: 626263
 *   Name        	: Thomas Miles
 *   Last Modified	: 08/09/18
 *
 ***************************************************************************/

#include "array_utils.h"

void merge_sort(Coord **arr, int l, int r) {
	/**
	 * Recursive mergesort algorithm
	 * @param arr: array of coordinates to be sorted
	 * @param l: left bound
	 * @param r: right bound
	 */

	if (l < r) {
		// find mid point
		int m = l+(r-l)/2;

		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}


void merge(Coord** arr, int l, int m, int r) {
	/**
	 * Merge operation for sorting, does the key comparisons
	 * @param arr: array of Coords being sorted
	 * @param l: left index
	 * @param m: middle index
	 * @param r: right index
	 */

	int i = 0;
	int j = 0;
	int k = l;

	int n_l = m - l + 1;    // size of left half
	int n_r = r - m;        // size of right half


	Coord* l_arr[n_l];      // Temporary arrays
	Coord* r_arr[n_r];

	// Copy each half to temp arrays
	for (i=0; i<n_l; i++) {
		l_arr[i] = arr[l+i];
	}
	for (j=0; j < n_r; j++) {
		r_arr[j] = arr[m + 1 + j];
	}
	i = 0;
	j = 0;

	// Do comparison and swap coordinates as needed
	while (i < n_l && j < n_r) {
		if (l_arr[i]->u <= r_arr[j]->u) {
			arr[k] = l_arr[i];
			i ++;
		} else {
			arr[k] = r_arr[j];
			j++;
		}
		k ++;
	}
	while (i < n_l) {

		arr[k] = l_arr[i];
		i++;
		k++;
	}
	while (j < n_r) {
		arr[k] = r_arr[j];
		j++;
		k++;
	}
}


void linear_search(Coord** array, double key, FILE* out) {
	/**
	 * Searches sorted array linearly and prints each u value compared against
	 * @param array: Array of coordinates to search
	 * @param key: u value to be found
	 * @param out: file to write to
	 */
	int i=0;
	double closest = DBL_MAX;

	while (fabs(array[i]->u - key) < closest) {
		if (closest != DBL_MAX) {
			fprintf(out, ",");
		}
		closest = fabs(array[i]->u - key);
		fprintf(out, "%.6f", array[i]->u);
		i++;
	}
	fprintf(out, "\n");
}


void binary_search(Coord** array, double key, FILE* out, int l, int r, bool first) {
	/**
	 * Recursive binary search algorithm, prints each u value compared against
	 * @param array: Array of coordinates to search
	 * @param key: u value to be found
	 * @param out: file to write to
	 * @param l: left bound
	 * @param r: right bound
	 * @param first: is this the first call; if true wont print the comma
	 */

	if (r > l+1) {
		int m = (l + r) / 2; // value to compare

		if (first == FALSE) {
			fprintf(out, ",");
		}
		// write to file
		fprintf(out, "%.6f", array[m]->u);

		if (array[r]->u > key && array[l]->u < key) {

			if (array[m]->u > key) {    // current value is to the right of key
				binary_search(array, key, out, l, m, FALSE);

			} else if (array[m]->u < key) { // current value is to the left of key
				binary_search(array, key, out, m, r, FALSE);
			}

		}
	} else {
		//done
		fprintf(out, "\n");
	}
}
