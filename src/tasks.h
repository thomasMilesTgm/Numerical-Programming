/***************************************************************************
 *
 *   File        : tasks.h
 *   Student Id  : <INSERT STUDENT ID HERE>
 *   Name        : <INSERT STUDENT NAME HERE>
 *
 ***************************************************************************/

#ifndef TASKS_H

#define MIN_X_COARSE 10
#define MAX_X_COARSE 70
#define MIN_Y_COARSE (-20)
#define MAX_Y_COARSE 20


int maxveldiff(const char* flow_file);

void coarsegrid(const char* flow_file, int resolution, int num_points);

void searching(const char* flow_file);

void vortcalc(const char* flow_file, int num_points);

#endif
