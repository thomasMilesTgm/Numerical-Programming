/***************************************************************************
 *
 * 	Functions for sorting, searching, balancing, etc.. AVL binary search
 * 	tree
 *
 *   File        	: bst.c
 *   Student Id  	: 626263
 *   Name        	: Thomas Miles
 *   Last Modified	: 08/09/18
 *
 ***************************************************************************/

#include "bst_utils.h"

BstNode * init_bst_node (Coord* coord) {
	/**
	 * Safe node initializer
	 * @param coord: coordinate to initialize a bst node for
	 * @return node: pointer to the new node
	 */
	BstNode *node;

	node = (BstNode*) malloc(sizeof(BstNode));
	if (node == NULL) {
		printf("--> ERROR: ERROR: In initialize_node: malloc failure.");
		exit(EXIT_FAILURE);
	}
	node->coord = coord;
	node->height = 1;
	node->left_child = NULL;
	node->right_child = NULL;
	node->parent = NULL;

	return node;
}

BstNode* bst_insert (BstNode **root, BstNode *orphan, char key) {
	/**
	 * Inserts a node into the BST recursively
	 * @param root: root of tree or subtree
	 * @param orphan: node to insert
	 * @param key: which coordinate value to use in comparison. 'u'=x velocity, 'w'=vorticity
	 * @return: root of tree
	 */

	double cmp;

	if (root == NULL) {
		return (orphan);
	}
	// make comparison
	if (key == 'u') {
		cmp = (*root)->coord->u - orphan->coord->u;

	} else if (key == 'w') {
		cmp = (*root)->coord->w - orphan->coord->w;

	} else {
		printf("ERROR: unknown bst key\n");
		exit(EXIT_FAILURE);
	}

	(*root)->height = 1 + max(height((*root)->left_child), height((*root)->right_child)); // update height

	// Insert node
	if (cmp < 0) {        // if orphan's key > root's, go right
		if ((*root)->right_child == NULL) {
			(*root)->right_child = orphan;
			orphan->parent = *root;
		} else {
			bst_insert(&((*root)->right_child), orphan, key);
		}

	} else if (cmp >= 0) {// if orphan's key < root's, go left

		if ((*root)->left_child == NULL) {
			(*root)->left_child = orphan;
			orphan->parent = *root;
		} else {
			bst_insert(&((*root)->left_child), orphan, key);
		}
	}
	return (*root);
}

BstNode* balance_tree (BstNode **root) {
	/**
	 * Recursively balance the tree (AVL tree)
	 * @param root: Root of tree or subree
	 * @return: pointer to the root of the tree after balancing
	 */

	int balance = get_bf((*root));

	if (balance > 1) { //&& ( orphan->coord->u < (*root)->left_child->coord->u)) {
		right_rotate(root);
	}

	if (balance < -1) {// && ( orphan->coord->u > (*root)->right_child->coord->u)) {
		return left_rotate(root);

	} else {
		if((*root)->right_child != NULL) balance_tree(&(*root)->right_child);
		if((*root)->left_child != NULL) balance_tree(&(*root)->left_child);
	}

}

void bst_search (BstNode *root, double search_key, FILE *output,  bool found) {
	/**
	 * Recursively search for a key in the BST and saves all compared keys
	 * @param root: Root of tree or subtree
	 * @param search_key: key value to be found
	 * @param output: file to write to
	 * @param found: cutoff when key is matched
	 */

	double cmp = 0;

	if (root == NULL) {
		/* we are at the end of the tree */
		if (found == FALSE) {
			//printf ("NOTFOUND\n");
		}
		return;

	} else {
		fprintf (output, "%.6f,", root->coord->u);

		cmp = root->coord->u - search_key;
		if (cmp < 0){
			bst_search (root->right_child, search_key, output, found);

		} else {
			if (cmp == 0) {
				found = TRUE;
				fprintf(output, "\n");
			}
			bst_search (root->left_child, search_key, output, found);
		}
	}
}

BstNode *left_rotate (BstNode** node) {
	/**
	 * Performs right rotation about node and returns pointer which has replaced node
	 */

	BstNode *r = copy_bst_node((*node)->right_child);
	free((*node)->right_child);

	// original node gets the new root's former right child as it's left
	(*node)->right_child = r->left_child;

	// l becomes root
	r->parent = (*node)->parent;
	r->left_child = *node;

	*node = r;
	return *node;
}

BstNode *right_rotate (BstNode** node) {
	/**
	 * Performs left rotation about node and returns pointer which has replaced node
	 */

	BstNode *l = copy_bst_node((*node)->left_child);
	free((*node)->left_child);

	// original node gets the new root's former right child as it's left
	(*node)->left_child = l->right_child;

	// l becomes root
	l->parent = (*node)->parent;
	l->right_child = *node;

	*node = l;
	return *node;

}

BstNode * copy_bst_node(BstNode* node) {
	/**
	 * Duplicates a node
	 */

	if (node == NULL) {
		return NULL;
	}
	BstNode *cpy = init_bst_node(node->coord);
	cpy->left_child = node->left_child;
	cpy->right_child = node->right_child;
	cpy->height = node->height;
	cpy->parent = node->parent;
	return cpy;
}

int get_bf(BstNode* node) {
	/**
	 * Gets the balance factor of a node
	 */

	if (node == NULL) {
		return 0;
	}
	return height(node->left_child) - height(node->right_child);
}

int max(int a, int b) {
	/**
	 * Helper function to compare two ints
	 */
	return (a > b)? a : b;
}

int height(BstNode *N) {
	/**
	 * Safe get height function
	 */
	if (N == NULL){
		return 0;
	}
	return N->height;
}

void descending(BstNode *root, FILE *out) {
	/**
	 * Recursive descending traversal for printing w in decending order to file
	 */

	if (root == NULL) {
		return;
	}

	descending(root->right_child, out);
	fprintf(out,"%.6f\n",root->coord->w);
	descending(root->left_child, out);
}