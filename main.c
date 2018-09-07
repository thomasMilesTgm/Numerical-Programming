/***************************************************************************
 *
 *   File        : main.c
 *   Student Id  : <INSERT STUDENT ID HERE>
 *   Name        : <INSERT STUDENT NAME HERE>
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>
#include "src/tasks.h"

int main(int argc, char *argv[]) {

    char* flow_file = NULL;
    int resolution = 0;
    char * ptr; // pointer for strtol to use
    int points;

	// parse command line input
    if (argc != 3) {
        printf("ERROR: not enough input arguments\n");
        exit(EXIT_FAILURE);

    } else {
        flow_file = argv[1];
        resolution = atoi(argv[2]);
    }

	
	struct timeval start;
	struct timeval stop;

	/* Task 1: Find the maximum velocity difference */
	gettimeofday(&start, NULL);
	points = maxveldiff(flow_file);
	gettimeofday(&stop, NULL);
	double elapsed_ms = (stop.tv_sec - start.tv_sec) * 1000.0;
	elapsed_ms += (stop.tv_usec - start.tv_usec) / 1000.0;
	printf("TASK 1:  %.2f milliseconds\n", elapsed_ms);

	/* Task 2: Coarser Grid */
	gettimeofday(&start, NULL);
	coarsegrid(flow_file, resolution, points);
	gettimeofday(&stop, NULL);
    	elapsed_ms = (stop.tv_sec - start.tv_sec) * 1000.0;
    	elapsed_ms += (stop.tv_usec - start.tv_usec) / 1000.0;
    	printf("TASK 2:  %.2f milliseconds\n", elapsed_ms);

	/* Task 3: Searching */
	gettimeofday(&start, NULL);
	searching(flow_file);
	gettimeofday(&stop, NULL);
    	elapsed_ms = (stop.tv_sec - start.tv_sec) * 1000.0;
    	elapsed_ms += (stop.tv_usec - start.tv_usec) / 1000.0;
   	printf("TASK 3:  %.2f milliseconds\n", elapsed_ms);
    
	/* Task 4: Statistics */
	gettimeofday(&start, NULL);
	vortcalc(flow_file, points);
	gettimeofday(&stop, NULL);
    	elapsed_ms = (stop.tv_sec - start.tv_sec) * 1000.0;
    	elapsed_ms += (stop.tv_usec - start.tv_usec) / 1000.0;
    	printf("TASK 4:  %.2f milliseconds\n", elapsed_ms);
	
    
	return (EXIT_SUCCESS);
}
