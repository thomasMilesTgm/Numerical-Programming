/***************************************************************************
 *
 * 	Header file for bst_utils.c
 *
 *   File        	: bst.h
 *   Student Id  	: 626263
 *   Name        	: Thomas Miles
 *   Last Modified	: 08/09/18
 *
 ***************************************************************************/

#ifndef ASSIGNMENT_1_BST_H
#define ASSIGNMENT_1_BST_H

#include "utils.h"

typedef struct BstNode {
	Coord* coord;
	struct BstNode* left_child;
	struct BstNode* right_child;
	struct BstNode* parent;
	int height;
}BstNode;

/*_________________________________ Functions _________________________________*/


BstNode * init_bst_node (Coord* coord);
BstNode* bst_insert (BstNode** root, BstNode *orphan, char key);
BstNode* balance_tree (BstNode **root);
int max(int a, int b);
int height(BstNode *N);
BstNode *left_rotate (BstNode** node);
BstNode *right_rotate (BstNode** node);
int get_bf(BstNode* node);
void bst_search (BstNode *root, double search_key, FILE *output,  bool found);
BstNode * copy_bst_node(BstNode* node);
void descending(BstNode *root, FILE *out);
void free_tree(BstNode *root);


#endif //ASSIGNMENT_1_BST_H
