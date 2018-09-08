/***************************************************************************
 *
 *	General utility functions for common tasks.
 *
 *   File        	: utils.c
 *   Student Id  	: 626263
 *   Name        	: Thomas Miles
 *   Last Modified	: 08/09/18
 *
 ***************************************************************************/

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
	 * Safely creates the buffer for scanning data from the CSV file and returns a
	 * pointer to it
	 * @param buffer_size: length of buffer (bytes)
	 * @return buffer: pointer to memory allocated
	 */
    char *buffer;
    buffer = (char*) malloc (buffer_size);

    if (buffer == NULL) {
        printf("--> ERROR: ERROR: In create_buffer: malloc failure.");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

double calculate_w(double v0, double v1, double u0, double u1, double x0, double x1, double y0, double y1) {
	return (v1 - v0) / (x1 - x0) - (u1 - u0) / (y1 - y0);
}


int* calc_n_m(const char* filepath) {
	/**
	 * Calculates the dimensionality of a data file
	 * @param filepath: to data file
	 * @return: int array [n,m] representing size of the data in [x,y]
	 */

	int* n_m = malloc(DIMS*sizeof(int));
	n_m[0] = 0;
	n_m[1] = 0;
	double x_last=DBL_MIN, y_last=DBL_MIN;
	bool n_found = FALSE;

	FILE* file = safe_open(filepath, "r");
	char * buffer = create_buffer(BUFFER_LEN);
	bool first_line = TRUE;

	while (fgets(buffer, BUFFER_LEN, file)) {

		char * ptr; // Pointer used in strtod()
		double x, y;

		// get the values of the point from buffer
		x = strtod(strtok(buffer, ","), &ptr);
		y = strtod(strtok(NULL, ","), &ptr);

		// First line does not contain data, pass
		if (first_line == TRUE) {
			first_line = FALSE;

		} else {

			if (n_found == FALSE && x_last > x) {
				n_found = TRUE;

			} else if (n_found == FALSE && x_last < x) {
				x_last = x;
				n_m[0] ++;
			}
			if (y_last < y) {
				y_last = y;
				n_m[1] ++;
			}
		}
	}
	fclose(file);
	return n_m;
}


