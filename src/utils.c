//
// Created by tmiles on 4/09/18.
//

#include "utils.h"



FILE* safe_open(const char * filename, const char * mode) {
    /**
     * Opens a file safely or prints error message and exits
     * @param filename: Path to file
     * @param mode: open mode
     * @return file: FILE pointer
     */
    FILE* file = fopen(filename, mode);

    if (file == NULL) {
        printf("ERROR: File %s failed to open!\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

Coord* init_coord(bool max) {
    /**
     * Does a safe malloc and initializes velocities to max or min sentinel value
     * @param max: initialize for max comparison (use min sentinel)
     * @return: Coordinate pointer
     */
    Coord* coord = (Coord*) malloc(sizeof(Coord));

    if (coord == NULL) {
        printf("ERROR: malloc failure when initializing a Coord!\n");
        exit(EXIT_FAILURE);

    } else {
        coord->x = ORIGIN;
        coord->y = ORIGIN;

        if (max == TRUE) {
            coord->u = DBL_MIN;
            coord->v = DBL_MIN;

        } else {
            coord->u = DBL_MAX;
            coord->v = DBL_MAX;
        }
    }
    return coord;
}


char * create_buffer (size_t buffer_size) {
    /**
    Creates the buffer for scanning data from the CSV file and returns a
    pointer to it
    */
    char *buffer;
    buffer = (char*) malloc (buffer_size);

    if (buffer == NULL) {
        printf("--> ERROR: ERROR: In create_buffer: malloc failure.");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

int get_index(double val, int resolution, int range_min,  int range_max) {
    /**
     *  Returns the grid index for a value
     */
    int index;
	int total_range = range_max - range_min;
	double val_norm = resolution*(val - range_min)/total_range;

	index = (int) floor(val_norm);
	if (index == resolution) {
		index--;
	}
	return index;
}

Coord* average(GridSquare* g) {
    /**
     * average the values in a grid square and compute score
     * @return avg: coord for average of square
     */

//	printf("computing average\n");

    Coord * avg = init_coord(TRUE);
    double x_cumulative = 0;
    double y_cumulative = 0;
    double u_cumulative = 0;
    double v_cumulative = 0;

    int i = 0;
    for (i; i < g->n_coords; i++) {
        x_cumulative += g->coords[i]->x;
        y_cumulative += g->coords[i]->y;
        u_cumulative += g->coords[i]->u;
        v_cumulative += g->coords[i]->v;
    }

    // average the values
    avg->x = x_cumulative/(i+1);
    avg->y = y_cumulative/(i+1);
    avg->u = u_cumulative/(i+1);
    avg->v = v_cumulative/(i+1);
    // compute score
    avg->S = 100.0 * sqrt(pow(avg->u, 2) + pow(avg->v, 2)) / sqrt(pow(avg->x, 2) + pow(avg->y, 2));

    return avg;
}

ListNode* insertion_sort(ListNode** list, Coord* coord, char sort_by) {
    /**
     * TODO give input to work for sorting by u also!
     *
     * Inserts a coordinate into a list sorting by coord->S
     */
//    printf("insertion sort\n");
    if (*list == NULL) {

	    printf("list==NULL\n");

    } else if ((*list)->coord == NULL){

	    (*list)->coord = coord;
	    (*list)->child = NULL;
	    (*list)->parent = NULL;
	    return (*list);

    } else if ((*list)->child == NULL) {


	    if (sort_by == 'S' && (*list)->coord->S < coord->S) {

//		    printf("Found position, inserting\n");
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

        } else if (sort_by == 'u' && (*list)->coord->u < coord->u) {
		    //printf("Found position, inserting\n");
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
	    }

    } else if ((*list)->child != NULL) {
//	    printf("there is a child, recursing\n");
        // otherwise recursively drop through the list
        insertion_sort(&(*list)->child, coord, sort_by);

    } else {
//	    printf("else\n");
	    (*list)->child = malloc(sizeof(ListNode));
        if ((*list)->child == NULL) {
            printf("ERROR: malloc failed in insertion_sort\n");
            exit(EXIT_FAILURE);
        }
    }
//	printf("endinsertion\n");
    return (*list);
}

Coord * pop(ListNode** list) {

//    printf("pop\n");
    ListNode* tmp = *list;

	if ((*list)->child != NULL) {
		*list = tmp->child;
		return tmp->coord;

	} else {
		return NULL;
	}

}

void merge_sort(Coord **arr, int l, int r) {
	if (l < r) {
		// find mid point
		int m = l+(r-l)/2;

		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

void merge(Coord** arr, int l, int m, int r) {

	int i = 0;
	int j = 0;
	int k = l;

	int n_l = m - l + 1;    // size of left half
	int n_r = r - m;        // size of right half


	Coord* l_arr[n_l];      // Temporary arrays
	Coord* r_arr[n_r];

	// Copy each half to temp arrays

	for (i=0; i<n_l; i++) {
		l_arr[i] = arr[l+i];
	}
	for (j=0; j < n_r; j++) {
		r_arr[j] = arr[m + 1 + j];
	}
	i = 0;
	j = 0;


	while (i < n_l && j < n_r) {
		if (l_arr[i]->u <= r_arr[j]->u) {
			arr[k] = l_arr[i];
			i ++;
		} else {
			arr[k] = r_arr[j];
			j++;
		}
		k ++;
	}
	while (i < n_l) {

		arr[k] = l_arr[i];
		i++;
		k++;
	}
	while (j < n_r) {
		arr[k] = r_arr[j];
		j++;
		k++;
	}

}

BstNode * init_bst_node (Coord* coord) {
	/**
	Safe node initialization, returns the pointer to the new node
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

BstNode* bst_insert (BstNode **root, BstNode *orphan) {
	/**
	*
	*/
	if (root == NULL) {
		return (orphan);
	}
	double cmp = (*root)->coord->u - orphan->coord->u;
	(*root)->height = 1 + max(height((*root)->left_child), height((*root)->right_child)); // update height
	// Insert node

	if (cmp < 0) {        /* if orphan's key > root's, go right */
		if ((*root)->right_child == NULL) {
			(*root)->right_child = orphan;
			orphan->parent = *root;
		} else {
			bst_insert(&((*root)->right_child), orphan);
		}
	} else if (cmp >= 0) {

		if ((*root)->left_child == NULL) {
			(*root)->left_child = orphan;
			orphan->parent = *root;
		} else {
			bst_insert(&((*root)->left_child), orphan);
		}
	}




	return (*root);
}

BstNode* balance_tree (BstNode **root) {

	int balance = get_bf((*root));


	if (balance > 1) { //&& ( orphan->coord->u < (*root)->left_child->coord->u)) {
		right_rotate(root);
	}

	if (balance < -1) {// && ( orphan->coord->u > (*root)->right_child->coord->u)) {
		return left_rotate(root);
	}
	else {
		if((*root)->right_child != NULL) balance_tree(&(*root)->right_child);
		if((*root)->left_child != NULL) balance_tree(&(*root)->left_child);
	}

}

void bst_search (BstNode *root, double search_key, FILE *output,  bool found) {
	/**
	Finds all key mathces in the BST and prints them to 'output' file
	*/
//TODO add cutoff

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
//printf("rotating Left\n");

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
//	printf("rotating Rghnt\n");

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
	if (node == NULL) {
		return 0;
	}
	return height(node->left_child) - height(node->right_child);
}

int max(int a, int b) {
	return (a > b)? a : b;
}

int height(BstNode *N) {
	if (N == NULL){
		return 0;
		}
	return N->height;
}

void linear_search(Coord** array, double key, FILE* out) {
	/**
	 * Search sorted array linearly
	 */
	int i=0;
	double closest = DBL_MAX;

	while (fabs(array[i]->u - key) < closest) {
		if (closest != DBL_MAX) {
			fprintf(out, ",");
		}
		closest = fabs(array[i]->u - key);
		fprintf(out, "%.6f", array[i]->u);
		i++;
	}
	fprintf(out, "\n");
}

void binary_search(Coord** array, double key, FILE* out, int l, int r, bool first) {

	if (r > l+1) {
		int m = (l + r) / 2; // value to compare

		if (first == FALSE) {
			fprintf(out, ",");
		}

		fprintf(out, "%.6f", array[m]->u);

		if (array[r]->u > key && array[l]->u < key) {

			if (array[m]->u > key) {    // current value is to the right of key
				binary_search(array, key, out, l, m, FALSE);

			} else if (array[m]->u < key) { // current value is to the left of key
				binary_search(array, key, out, m, r, FALSE);
			}

		}
	} else {
		//done
		fprintf(out, "\n");
	}
}

void linked_list_search(ListNode* node, double key, FILE* out, double closest) {
//TODO Missing first node
//	printf("searching linked list\n");
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

void preOrder(BstNode *root)
{
	if(root != NULL)
	{
		printf("%f, ",root->coord->u);
		preOrder(root->left_child);
		preOrder(root->right_child);
	}
}

int mask(double x, double min, double max, int factor) {
	/**
	 * Converts a position value to an indexer for domain array
	 */
	return (int) trunc(factor * x / (max-min));
}

double calculate_w(double v0, double v1, double u0, double u1, double x0, double x1, double y0, double y1) {

}