/***************************************************************************
 *
 * 	Header file for necessary #include's and function prototypes for tasks.c
 *
 *   File        	: tasks.h
 *   Student Id  	: 626263
 *   Name        	: Thomas Miles
 *   Last Modified	: 08/09/18
 *
 ***************************************************************************/

#ifndef TASKS_H

/*_________________________________  Include  _________________________________*/

#include "array_utils.h"
#include "bst_utils.h"
#include "grid_utils.h"
#include "list_utils.h"

/*_________________________________ Functions _________________________________*/

int maxveldiff(const char* flow_file);

void coarsegrid(const char* flow_file, int resolution, int num_points);

void searching(const char* flow_file);

void vortcalc(const char* flow_file);

#endif
