#ifndef MODEL_H__
#define MODEL_H__

#include "types.h"

void add_node(Graph *graph, double x, double y);
void delete_node(Graph *graph, double id);
void move_node(Graph *graph, double id, double x, double y);

void add_edge(Graph *graph, double id_from, double id_to);
void delete_edge(Graph *graph, double id_from, double id_to);

/* runs a function on all nodes of a graph
 * function signature:
 *   void f(Node *node, gpointer data);
 */
void run_function_on_nodes(void (*f)(Node *n, gpointer d),
			   Graph *g,
			   gpointer d);

#endif /* MODEL_H__ */
