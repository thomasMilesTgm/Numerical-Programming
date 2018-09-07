/***************************************************************************
 *
 *   File        : tasks.c
 *   Student Id  : <INSERT STUDENT ID HERE>
 *   Name        : <INSERT STUDENT NAME HERE>
 *
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>
#include "tasks.h"
#include "utils.h"

int maxveldiff(const char* flow_file)
{
    char * outfile = "out/task1.csv";

    int num_points = 0;

    char * buffer = create_buffer(BUFFER_LEN);
    char * ptr; // Pointer used in strtod()

    // initialize coordinates to keep track of min/max velocities
    Coord* v_max = init_coord(TRUE);
    Coord* v_min = init_coord(FALSE);
    Coord* u_max = init_coord(TRUE);
    Coord* u_min = init_coord(FALSE);

    FILE* file = safe_open(flow_file, "r");

    bool first_line = TRUE;
    while (fgets(buffer, BUFFER_LEN, file)) {

        double x, y, u, v;

        // get the values of the point from buffer
        x = strtod(strtok(buffer, ","), &ptr);
        y = strtod(strtok(NULL, ","), &ptr);
        u = strtod(strtok(NULL, ","), &ptr);
        v = strtod(strtok(NULL, ","), &ptr);

        // First line does not contain data, pass
        if (first_line == TRUE) {
            first_line = FALSE;

        } else if (x > X_MIN_VD) {
            // keep track of how many points in the data set for next task
            num_points ++;

            // Is this the min or max found for u/v, if so update relevant coords
            if (u > u_max->u) {
                u_max->x = x;
                u_max->y = y;
                u_max->u = u;
                u_max->v = v;
            }
            if (u < u_min->u) {
                u_min->x = x;
                u_min->y = y;
                u_min->u = u;
                u_min->v = v;
            }
            if (v > v_max->v) {
                v_max->x = x;
                v_max->y = y;
                v_max->u = u;
                v_max->v = v;
            }
            if (v < v_min->u) {
                v_min->x = x;
                v_min->y = y;
                v_min->u = u;
                v_min->v = v;
            }
        }
    }
    // it follows that the max velocity differences are u_max,u_min and v_max,v_min, so write output
    FILE* out = safe_open(outfile, "w");

    fprintf(out, "x,y,u,v\n");
    fprintf(out, "%.6f,%6f,%6f,%6f\n", u_max->x, u_max->y, u_max->u, u_max->v);
    fprintf(out, "%.6f,%6f,%6f,%6f\n", u_min->x, u_min->y, u_min->u, u_min->v);
    fprintf(out, "%.6f,%6f,%6f,%6f\n", v_max->x, v_max->y, v_max->u, v_max->v);
    fprintf(out, "%.6f,%6f,%6f,%6f\n", v_min->x, v_min->y, v_min->u, v_min->v);

    // close the file and free malloc's
    fclose(out);
    free(u_max);
    free(u_min);
    free(v_max);
    free(v_min);
    return num_points;
}

void coarsegrid(const char* flow_file, int resolution, int num_points)
/**
 *  @param flow_file: File path to data
 *  @param resolution: Grid resolution
 *  @param num_points: Number of data points in flow_file (max points in a single grid cell)
 */
{
    char * outfile = "out/task2.csv";

    int g_x;
    int g_y;

    GridSquare* grid[resolution][resolution];

    // initialize grid
    for (int i=0; i < resolution; i++) {
        for (int j=0; j < resolution; j++) {


            grid[i][j] = malloc(sizeof(GridSquare) + num_points * sizeof(Coord));
            if (grid[i][j] == NULL) {
                exit(EXIT_FAILURE);
            }
            grid[i][j]->n_coords = 0;
	        if (grid[i][j]->coords == NULL) {
                exit(EXIT_FAILURE);
            }
        }
    }
	FILE* file = safe_open(flow_file, "r");
    char * buffer = create_buffer(BUFFER_LEN);
    bool first_line = TRUE;

    while (fgets(buffer, BUFFER_LEN, file)) {
	    char * ptr; // Pointer used in strtod()
        double x, y, u, v;

        // get the values of the point from buffer
        x = strtod(strtok(buffer, ","), &ptr);
        y = strtod(strtok(NULL, ","), &ptr);
        u = strtod(strtok(NULL, ","), &ptr);
        v = strtod(strtok(NULL, ","), &ptr);
        // First line does not contain data, pass
        if (first_line == TRUE) {
            first_line = FALSE;

        // if point is in range
        } else if (x >= MIN_X_COARSE && x <= MAX_X_COARSE && y >= MIN_Y_COARSE && y <= MAX_Y_COARSE) {

            // initialize a coord for the point
            Coord* new_point = init_coord(TRUE);
            new_point->x = x;
            new_point->y = y;
            new_point->u = u;
            new_point->v = v;
            // get the grid index
            g_x = get_index(x, resolution, MIN_X_COARSE, MAX_X_COARSE);
            g_y = get_index(y, resolution, MIN_Y_COARSE, MAX_Y_COARSE);

            // put the point into the grid

	        int n = grid[g_x][g_y]->n_coords;
	        grid[g_x][g_y]->coords[n] = new_point;
	        grid[g_x][g_y]->n_coords ++;

        }
    }
    // now the grid is setup, compute averages
    ListNode* list = malloc(sizeof(ListNode));


    if (list == NULL) {
        printf("ERROR: malloc failed in coarsegrid\n");
        exit(EXIT_FAILURE);
    }
	list->coord = NULL;
	list->parent= NULL;
	list->child = NULL;

    for (int i=0; i < resolution; i++) {
        for (int j=0; j < resolution; j++) {
            insertion_sort(&list, average(grid[i][j]), 'S');
        }
    }
    FILE* out = safe_open(outfile, "w");

	Coord* c = pop(&list);

    // pop values from the list for printing
    while (c != NULL) {
	    fprintf(out, "%.6f,%.6f,%.6f,%.6f,%.6f\n", c->x, c->y, c->u, c->v, c->S);
	    c = pop(&list);
    }
}

void searching(const char* flow_file)
{

	char *outfile = "out/task3.csv";

	int n_center = 0;
	Coord** array = malloc(sizeof(Coord*) + 5*sizeof(double));
	if (array == NULL) {
		printf("ERROR: malloc failed in coarsegrid\n");
		exit(EXIT_FAILURE);
	}

	FILE* file = safe_open(flow_file, "r");
	char * buffer = create_buffer(BUFFER_LEN);
	bool first_line = TRUE;

	while (fgets(buffer, BUFFER_LEN, file)) {

		char * ptr; // Pointer used in strtod()
		double x, y, u, v;

		// get the values of the point from buffer
		x = strtod(strtok(buffer, ","), &ptr);
		y = strtod(strtok(NULL, ","), &ptr);
		u = strtod(strtok(NULL, ","), &ptr);
		v = strtod(strtok(NULL, ","), &ptr);
		// First line does not contain data, pass
		if (first_line == TRUE) {
			first_line = FALSE;

		// if point is on centre line
		}
		if (y == 0) {
			array=realloc(array, sizeof(Coord*) + (n_center+1) * 5*sizeof(double));  // add some more memory
			// initialize a coord and save data.
			array[n_center] = init_coord(TRUE);
			array[n_center]->x = x;
			array[n_center]->y = y;
			array[n_center]->u = u;
			array[n_center]->v = v;
			n_center ++;
		}
	}
	fclose(file);

	merge_sort(array, 0, n_center-1);

	// now the array is sorted, make the linked list
	ListNode* list = malloc(sizeof(ListNode));
	list->coord = NULL;
	list->parent= NULL;
	list->child = NULL;


	for (int i=0; i<n_center; i++) {
		insertion_sort(&list, array[i], 'u');
	}



	// Make the BST, since the array is sorted, to make sure the tree is balanced, make the middle root

	int mid = (n_center + 1) / 2;
	BstNode* bst_root = init_bst_node(array[mid]);

	// insert remaining coordinates
	for (int i=0; i<n_center; i++) {

		if (i != mid) {
			BstNode* new_node = init_bst_node(array[i]);
			bst_insert(&bst_root, new_node);
			balance_tree(&bst_root);
		}
	}
	FILE* out = safe_open(outfile, "w");

	struct timeval start;
	struct timeval stop;

	// Search for
	double find = 0.4*array[n_center-1]->u;

	gettimeofday(&start, NULL);
	linear_search(array, find, out);
	gettimeofday(&stop, NULL);
		double elapsed_ms = (stop.tv_sec - start.tv_sec) * 1000.0;
		elapsed_ms += (stop.tv_usec - start.tv_usec) / 1000.0;
	printf("TASK 3:  Array Linear Search: %.2f milliseconds\n", elapsed_ms);

	gettimeofday(&start, NULL);
	binary_search(array, find, out, 0, n_center-1, TRUE);
	gettimeofday(&stop, NULL);
		elapsed_ms = (stop.tv_sec - start.tv_sec) * 1000.0;
		elapsed_ms += (stop.tv_usec - start.tv_usec) / 1000.0;
	printf("TASK 3:  Array Binary Search: %.2f milliseconds\n", elapsed_ms);

	gettimeofday(&start, NULL);
	linked_list_search(list, find, out, DBL_MAX);
	gettimeofday(&stop, NULL);
		elapsed_ms = (stop.tv_sec - start.tv_sec) * 1000.0;
		elapsed_ms += (stop.tv_usec - start.tv_usec) / 1000.0;
	printf("TASK 3:  List Linear Search: %.2f milliseconds\n", elapsed_ms);

	gettimeofday(&start, NULL);
	bst_search(bst_root, find, out, FALSE);
	gettimeofday(&stop, NULL);
	elapsed_ms = (stop.tv_sec - start.tv_sec) * 1000.0;
	elapsed_ms += (stop.tv_usec - start.tv_usec) / 1000.0;
	printf("TASK 3:  BST Search: %.2f milliseconds\n", elapsed_ms);
	gettimeofday(&start, NULL);
}

void vortcalc(const char* flow_file, int num_points)
{
	int i = 0;
	int j = 0;
	int m_x;
	int m_y;
	bool calc_w = FALSE;

	double w[(int)sqrt(num_points)][(int)sqrt(num_points)];
	Coord* domain[(int)sqrt(num_points)][(int)sqrt(num_points)];

	FILE* file = safe_open(flow_file, "r");
	char * buffer = create_buffer(BUFFER_LEN);
	bool first_line = TRUE;

	while (fgets(buffer, BUFFER_LEN, file)) {
		char * ptr; // Pointer used in strtod()
		double x, y, u, v;
printf("%d, %d\n____\n", num_points,(int)sqrt(num_points));
		// get the values of the point from buffer
		x = strtod(strtok(buffer, ","), &ptr);
		y = strtod(strtok(NULL, ","), &ptr);
		u = strtod(strtok(NULL, ","), &ptr);
		v = strtod(strtok(NULL, ","), &ptr);
		// First line does not contain data, pass
		if (first_line == TRUE) {
			first_line = FALSE;

		} else {

			Coord* new_point = init_coord(TRUE);
			new_point->x = x;
			new_point->y = y;
			new_point->u = u;
			new_point->v = v;

			m_x = mask(x, X_MIN, X_MAX, num_points);
			m_y = mask(y, Y_MIN, Y_MAX, num_points);

			if (m_y > j) {
				j++;
			}
			if (m_x > i) {
				i++;
			}
			domain[i][j] = new_point;
			// every two points calculate w
			if (calc_w == TRUE) {
				double v0 = domain[i-1][i-1]->v;
				double v1 = domain[i][j]->v;
				double u0 = domain[i-1][i-1]->u;
				double u1 = domain[i][j]->u;
				double x0 = domain[i-1][i-1]->x;
				double x1 = domain[i][j]->x;
				double y0 = domain[i-1][i-1]->y;
				double y1 = domain[i][j]->y;
				w[i - 1][j - 1] = calculate_w(v0,v1,u0,u1,x0,x1,y0,y1);
				calc_w = FALSE;

			} else {
				calc_w = TRUE;
			}
		}
	}
}
