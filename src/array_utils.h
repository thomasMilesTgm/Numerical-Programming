/***************************************************************************
 *
 * 	Header file for array_utils.c
 *
 *   File        	: array_utils.h
 *   Student Id  	: 626263
 *   Name        	: Thomas Miles
 *   Last Modified	: 08/09/18
 *
 ***************************************************************************/

#ifndef ASSIGNMENT_1_ARRAY_UTILS_H
#define ASSIGNMENT_1_ARRAY_UTILS_H

#include "utils.h"


/*_________________________________ Functions _________________________________*/

void merge_sort(Coord **arr, int l, int r) ;
void merge(Coord** arr, int l, int m, int r);
void linear_search(Coord** array, double key, FILE* out);
void binary_search(Coord** array, double key, FILE* out, int l, int r, bool first);

#endif //ASSIGNMENT_1_ARRAY_UTILS_H
