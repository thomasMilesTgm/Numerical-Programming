//
// Created by tmiles on 4/09/18.
//

#ifndef ASSIGNMENT_1_UTILS_H
#define ASSIGNMENT_1_UTILS_H
/*_________________________________  Include  _________________________________*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
/*_________________________________  Defines  _________________________________*/
#define ORIGIN 0
#define BUFFER_LEN 256
#define X_MIN_VD 20         // minimum x value to consider for velocity difference
#define PARAMS 5            // number of params in avg array

/*_________________________________  Typedefs _________________________________*/

typedef struct {
    /** Coordinate (x, y, u, v) */
    double x;
    double y;
    double u;
    double v;
    double S;
} Coord;

typedef struct GridSquare {
    int n_coords;
    Coord* coords[];
} GridSquare;

typedef struct ListNode {
    Coord* coord;
    struct ListNode* child;
    struct ListNode* parent;
} ListNode;

typedef enum {
    /** Booleans */
    TRUE,
    FALSE
} bool;

/*_________________________________ Functions _________________________________*/
FILE* safe_open(const char * filename, const char * mode);
Coord* init_coord(bool max);
char * create_buffer (size_t buffer_size);
int get_index(double val, int resolution, int range_min,  int range_max);
Coord* average(GridSquare* g);
ListNode* insertion_sort(ListNode* list, Coord* coord);
Coord * pop(ListNode** list);
void merge_sort(Coord **arr, int l, int r) ;
void merge(Coord** arr, int l, int m, int r);
#endif //ASSIGNMENT_1_UTILS_H
