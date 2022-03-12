#ifndef MODEL_H__
#define MODEL_H__

#include "types.h"

void add_node(Graph *graph, gdouble x, gdouble y);
void delete_node(Graph *graph, gdouble id);
void move_node(Graph *graph, gdouble id, gdouble x, gdouble y);

void add_edge(Graph *graph, gdouble id_from, gdouble id_to);
void delete_edge(Graph *graph, gdouble id_from, gdouble id_to);

void select_node(Node **node, Graph *graph, int id);

/* runs a function on all nodes of a graph
 * function signature:
 *   void f(Node *node, gpointer data);
 */
void nodes_call(void (*f)(Node *n, gpointer d),
			   Graph *g,
			   gpointer d);

/* runs a function which returns an integer
 * on all nodes, selects the Node with which
 * the function returned with the smallest
 * POSITIVE integer and returns it's ID.
 * -1 if not found.
 * function signature:
 *   int f(Node *node, gpointer data);
 */
int nodes_select_one(int (*f)(Node *n, gpointer d),
		     Graph *g,
		     gpointer d);


// TODO
/*
 * runs a function which returns a bool
 * on all nodes, selects all Nodes with
 * which the function returned true and returns
 * their ID in an array structured as following
 * {number of matches; id 1; id 2... }
 * function signature:
 *   gboolean f(Node *node, gpointer data);
 */
int nodes_select_all(gboolean (*f)(Node *n, gpointer d),
		     Graph *g,
		     gpointer d);

#endif /* MODEL_H__ */
