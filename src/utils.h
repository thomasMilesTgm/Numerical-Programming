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
#define X_MIN 0
#define Y_MIN (-20)
#define X_MAX 90
#define Y_MAX 20
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

typedef struct GridSquare {
    int n_coords;
    Coord* coords[];
} GridSquare;

typedef struct ListNode {
    Coord* coord;
    struct ListNode* child;
    struct ListNode* parent;
} ListNode;

typedef struct BstNode {
	Coord* coord;
	struct BstNode* left_child;
	struct BstNode* right_child;
	struct BstNode* parent;
	int height;
}BstNode;

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
ListNode* insertion_sort(ListNode** list, Coord* coord, char sort_by);
Coord * pop(ListNode** list);
void merge_sort(Coord **arr, int l, int r) ;
void merge(Coord** arr, int l, int m, int r);
BstNode * init_bst_node (Coord* coord);
BstNode* bst_insert (BstNode** root, BstNode *orphan);
BstNode* balance_tree (BstNode **root);
int max(int a, int b);
int height(BstNode *N);
BstNode *left_rotate (BstNode** node);
BstNode *right_rotate (BstNode** node);
int get_bf(BstNode* node);
void linear_search(Coord** array, double key, FILE* out);
void binary_search(Coord** array, double key, FILE* out, int l, int r, bool first);
void linked_list_search(ListNode* node, double key, FILE* out, double closest);
void bst_search (BstNode *root, double search_key, FILE *output,  bool found);
void preOrder(BstNode *root);
BstNode * copy_bst_node(BstNode* node);
int mask(double x, double min, double max, int factor);
double calculate_w(double v0, double v1, double u0, double u1, double x0, double x1, double y0, double y1);
int* calc_n_m(const char* filepath);
#endif //ASSIGNMENT_1_UTILS_H
