/***************************************************************************
 *
 * 	Functions for building and sorting linked lists
 *
 *   File        	: list_utils.c
 *   Student Id  	: 626263
 *   Name        	: Thomas Miles
 *   Last Modified	: 08/09/18
 *
 ***************************************************************************/

#include "list_utils.h"


ListNode* insertion_sort(ListNode** list, Coord* coord, char sort_by) {
	/**
	 * Inserts a coordinate into a list sorting by coord->S
	 * @param list: address of the pointer to first element in list
	 * @param coord: coordinate to insert
	 * @param sort_by: parameter to sort by, 'S'=Score, 'u'=x velocity
	 *
	 */
	int comp = 0;   // comparison value

	if (*list == NULL) {
		printf("list==NULL\n");

	// reached the end of the list
	} else if ((*list)->coord == NULL) {

		(*list)->coord = coord;
		(*list)->child = NULL;
		(*list)->parent = NULL;
		return (*list);


	} else if ((*list)->child == NULL) {

		if (sort_by == 'S') {
			comp = (*list)->coord->S < coord->S;

		} else if (sort_by == 'u') {
			comp = (*list)->coord->u < coord->u;

		} else {
			printf("ERROR: unrecognised key for insertion sort comparison\n");
		}
		if (comp) {

			// list has lower score than coord, insert
			ListNode *tmp = (*list);
			ListNode *tmp_parent = NULL;

			if ((*list)->parent != NULL) {
				tmp_parent = (*list)->parent;
			}

			(*list) = malloc(sizeof(ListNode));
			if ((*list) == NULL) {
				printf("ERROR: malloc failed in insertion_sort\n");
				exit(EXIT_FAILURE);
			}
			(*list)->coord = coord;
			(*list)->child = tmp;
			(*list)->parent = tmp_parent;

			(*list)->child->parent = (*list);

		}

	} else if ((*list)->child != NULL) {

		// otherwise recursively drop through the list
		insertion_sort(&(*list)->child, coord, sort_by);

	} else {

		(*list)->child = malloc(sizeof(ListNode));
		if ((*list)->child == NULL) {
			printf("ERROR: malloc failed in insertion_sort\n");
			exit(EXIT_FAILURE);
		}
	}
	return (*list);
}


Coord * pop(ListNode** list) {
	/**
	 * Returns the top value of the linked list and removes it from the list
	 */

	ListNode* tmp = *list;

	if ((*list)->child != NULL) {
		*list = tmp->child;
		return tmp->coord;

	} else {
		return NULL;
	}

}


void linked_list_search(ListNode* node, double key, FILE* out, double closest) {
	/**
	 * Recursively searches list for a value and prints all values compared against.
	 * @param node: node to compare
	 * @param key: u value you're looking for
	 * @param out: file to write to
	 * @param closest: nearest value found to know when to cutoff
	 */

	if (closest != DBL_MAX) {
		fprintf(out, ",");
	}
	if (node != NULL && fabs(node->coord->u - key)  < closest) {
		fprintf(out, "%.6f",node->coord->u);
		linked_list_search(node->child, key, out, fabs(node->coord->u - key));

	} else {
		fprintf(out, "\n");
	}
}
