//
// Created by tmiles on 4/09/18.
//

#include "utils.h"



FILE* safe_open(const char * filename, const char * mode) {
    /**
     * Opens a file safely or prints error message and exits
     * @param filename: Path to file
     * @param mode: open mode
     * @return file: FILE pointer
     */
    FILE* file = fopen(filename, mode);

    if (file == NULL) {
        printf("ERROR: File %s failed to open!\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

Coord* init_coord(bool max) {
    /**
     * Does a safe malloc and initializes velocities to max or min sentinel value
     * @param max: initialize for max comparison (use min sentinel)
     * @return: Coordinate pointer
     */
    Coord* coord = (Coord*) malloc(sizeof(Coord));

    if (coord == NULL) {
        printf("ERROR: malloc failure when initializing a Coord!\n");
        exit(EXIT_FAILURE);

    } else {
        coord->x = ORIGIN;
        coord->y = ORIGIN;

        if (max == TRUE) {
            coord->u = DBL_MIN;
            coord->v = DBL_MIN;

        } else {
            coord->u = DBL_MAX;
            coord->v = DBL_MAX;
        }
    }
    return coord;
}


char * create_buffer (size_t buffer_size) {
    /**
    Creates the buffer for scanning data from the CSV file and returns a
    pointer to it
    */
    char *buffer;
    buffer = (char*) malloc (buffer_size);

    if (buffer == NULL) {
        printf("--> ERROR: ERROR: In create_buffer: malloc failure.");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

int get_index(double val, int resolution, int range_min,  int range_max) {
    /**
     *  Returns the grid index for a value
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
     * average the values in a grid square and compute score
     * @return avg: coord for average of square
     */

//	printf("computing average\n");

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

ListNode* insertion_sort(ListNode* list, Coord* coord) {
    /**
     * Inserts a coordinate into a list sorting by coord->S
     */
//    printf("insertion sort\n");
    if (list == NULL) {

	    printf("list==NULL\n");

    } else if (list->coord == NULL){

	    list->coord = coord;
	    list->child = NULL;
	    list->parent = NULL;
	    return list;

    } else if (list->coord->S < coord->S) {

//	    printf("Found position, inserting\n");
        // list has lower score than coord, insert
        ListNode * tmp = list;
        ListNode * tmp_parent = NULL;

        if (list->parent != NULL) {
            tmp_parent = list->parent;
        }

        list = malloc(sizeof(ListNode));
        if (list == NULL) {
            printf("ERROR: malloc failed in insertion_sort\n");
            exit(EXIT_FAILURE);
        }
        list->coord = coord;
        list->child = tmp;
        list->parent= tmp_parent;

        list->child->parent = list;

    } else if (list->child != NULL) {
//	    printf("there is a child, recursing\n");
        // otherwise recursively drop through the list
        insertion_sort(list->child, coord);

    } else {
//	    printf("else\n");
        list->child = malloc(sizeof(ListNode));
        if (list->child == NULL) {
            printf("ERROR: malloc failed in insertion_sort\n");
            exit(EXIT_FAILURE);
        }
    }
//	printf("endinsertion\n");
    return list;
}

Coord * pop(ListNode** list) {

//    printf("pop\n");
    ListNode* tmp = *list;

	if ((*list)->child != NULL) {
		*list = tmp->child;
		return tmp->coord;

	} else {
		return NULL;
	}

}

void merge_sort(Coord **arr, int l, int r) {
	if (l < r) {
		// find mid point
		int m = l+(r-l)/2;

		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

void merge(Coord** arr, int l, int m, int r) {

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