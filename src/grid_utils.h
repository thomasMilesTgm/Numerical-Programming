/***************************************************************************
 *
 * 	Header file for grid_utils.c
 *
 *   File        	: grid_utils.h
 *   Student Id  	: 626263
 *   Name        	: Thomas Miles
 *   Last Modified	: 08/09/18
 *
 ***************************************************************************/

#ifndef ASSIGNMENT_1_GRID_UTILS_H
#define ASSIGNMENT_1_GRID_UTILS_H

#include "utils.h"

#define MIN_X_COARSE 10
#define MAX_X_COARSE 70
#define MIN_Y_COARSE (-20)
#define MAX_Y_COARSE 20

typedef struct GridSquare {
	int n_coords;
	Coord* coords[];
} GridSquare;

/*_________________________________ Functions _________________________________*/

int get_index(double val, int resolution, int range_min,  int range_max);
Coord* average(GridSquare* g);

#endif //ASSIGNMENT_1_GRID_UTILS_H
