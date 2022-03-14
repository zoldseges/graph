#ifndef MODEL_H__
#define MODEL_H__

#include "types.h"

void add_node(Graph *graph, Point p);
void delete_node(Graph *graph, Node *node);
void move_node(Graph *graph, Node *node, Point p);

/* add edge: set matrix weight to 0 or else
 * del edge: set matrix weight to INT_MAX
 */
void set_matrix(Matrix m, int row, int col, int weight);

#endif /* MODEL_H__ */
