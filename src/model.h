#ifndef MODEL_H__
#define MODEL_H__

#include "types.h"

void add_node(Graph *graph, gdouble x, gdouble y);
void delete_node(Graph *graph, gdouble id);
void move_node(Graph *graph, gdouble id, gdouble x, gdouble y);

void add_edge(Graph *graph, gdouble id_from, gdouble id_to);
void delete_edge(Graph *graph, gdouble id_from, gdouble id_to);

/* runs a function on all nodes of a graph
 * function signature:
 *   void f(Node *node, gpointer data);
 */
void run_function_on_nodes(void (*f)(Node *n, gpointer d),
			   Graph *g,
			   gpointer d);

#endif /* MODEL_H__ */
