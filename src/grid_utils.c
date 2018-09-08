/***************************************************************************
 *
 * 	Functions used for coarse grid creation and management
 *
 *   File        	: grid_utils.c
 *   Student Id  	: 626263
 *   Name        	: Thomas Miles
 *   Last Modified	: 08/09/18
 *
 ***************************************************************************/

#include "grid_utils.h"


int get_index(double val, int resolution, int range_min,  int range_max) {
	/**
	 *  Get the grid index for a value
	 *  @param val: value to get grid square index
	 *  @param resolution: grid resolution
	 *  @param range_min: lower bound for val
	 *  @param range_max: upper bound for val
	 *  @return index: coarse grid index
	 */
	int index;
	int total_range = range_max - range_min;
	double val_norm = resolution*(val - range_min)/total_range;

	index = (int) floor(val_norm);
	if (index == resolution) {
		index--;
	}
	return index;
}


Coord* average(GridSquare* g) {
	/**
	 * Average the values in a grid square and compute score
	 * @param g: square to compute the average of
	 * @return avg: coord for average of square
	 */


	Coord * avg = init_coord(TRUE);
	double x_cumulative = 0;
	double y_cumulative = 0;
	double u_cumulative = 0;
	double v_cumulative = 0;

	int i = 0;
	for (i; i < g->n_coords; i++) {
		x_cumulative += g->coords[i]->x;
		y_cumulative += g->coords[i]->y;
		u_cumulative += g->coords[i]->u;
		v_cumulative += g->coords[i]->v;
	}

	// average the values
	avg->x = x_cumulative/(i+1);
	avg->y = y_cumulative/(i+1);
	avg->u = u_cumulative/(i+1);
	avg->v = v_cumulative/(i+1);
	// compute score
	avg->S = 100.0 * sqrt(pow(avg->u, 2) + pow(avg->v, 2)) / sqrt(pow(avg->x, 2) + pow(avg->y, 2));

	return avg;
}