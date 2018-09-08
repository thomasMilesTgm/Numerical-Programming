/***************************************************************************
 *
 * 	Header file for #include's, #defines, function prototypes, and typdefs.
 * 	This is included by all other utility headers, so it contains all the
 * 	includes needed
 *
 *   File        	: utils.h
 *   Student Id  	: 626263
 *   Name        	: Thomas Miles
 *   Last Modified	: 08/09/18
 *
 ***************************************************************************/

#ifndef ASSIGNMENT_1_UTILS_H
#define ASSIGNMENT_1_UTILS_H
/*_________________________________  Include  _________________________________*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <sys/time.h>
/*_________________________________  Defines  _________________________________*/
#define ORIGIN 0
#define BUFFER_LEN 256
#define X_MIN_VD 20         // minimum x value to consider for velocity difference
#define DIMS 2

/*_________________________________  Typedefs _________________________________*/

typedef struct {
    /** Coordinate (x, y, u, v) */
    double x;
    double y;
    double u;
    double v;
    double S;
	double w;
} Coord;



typedef enum {
    /** Booleans */
    TRUE,
    FALSE
} bool;

/*_________________________________ Functions _________________________________*/


FILE* safe_open(const char * filename, const char * mode);
Coord* init_coord(bool max);
char * create_buffer (size_t buffer_size);
double calculate_w(double v0, double v1, double u0, double u1, double x0, double x1, double y0, double y1);
int* calc_n_m(const char* filepath);


#endif //ASSIGNMENT_1_UTILS_H
