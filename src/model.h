#ifndef MODEL_H__
#define MODEL_H__

#include "types.h"

void add_node(Graph *graph, Point p);
void delete_node(Graph *graph, Node *node);
void move_node(Graph *graph, Node *node, Point p);

void set_edge_weight(Graph *graph, Node *from, Node *to, int weight);

#endif /* MODEL_H__ */
