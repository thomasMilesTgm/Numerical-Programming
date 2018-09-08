/***************************************************************************
 *
 * 	Header file for list_utils.c
 *
 *   File        	: list_utils.h
 *   Student Id  	: 626263
 *   Name        	: Thomas Miles
 *   Last Modified	: 08/09/18
 *
 ***************************************************************************/

#ifndef ASSIGNMENT_1_LIST_UTILS_H
#define ASSIGNMENT_1_LIST_UTILS_H

#include "utils.h"

typedef struct ListNode {
	Coord* coord;
	struct ListNode* child;
	struct ListNode* parent;
} ListNode;

/*_________________________________ Functions _________________________________*/
ListNode* insertion_sort(ListNode** list, Coord* coord, char sort_by);
Coord * pop(ListNode** list);
void linked_list_search(ListNode* node, double key, FILE* out, double closest);

#endif //ASSIGNMENT_1_LIST_UTILS_H
