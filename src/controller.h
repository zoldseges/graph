#ifndef CONTROLLER_H__
#define CONTROLLER_H__

#include "types.h"

void ctl_init(Ctl *ctl);
void ctl_handler(Ctl *ctl);
void free_ctl(Ctl *ctl);

enum MARKED marked_type(Marked *marked);
gboolean marked_equals(Marked *a, Marked *b);

/* calls `f` on every node in `marked` 
 * which is of type `type`
 * function signature:
 *   void f(Node *n[2], gpointer d);
 */
void marked_call(void (*f)(Node *node[2], gpointer d),
		 Marked *marked,
		 enum MARKED type,
		 gpointer d);


Node *get_node_by_id(Graph *graph, int id);

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
 * POSITIVE integer and returns a pointer
 * to it.
 * function signature:
 *   int f(Node *node, gpointer data);
 */
Node *nodes_filter_one(int (*f)(Node *n, gpointer d),
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
Node *nodes_filter_all(gboolean (*f)(Node *n, gpointer d),
		       Graph *g,
		       gpointer d);

/* runs a function on all edges of a graph
 * function signature:
 *   void f(Node *from, Node *to, int weight, gpointer d);
 */
void edges_call(void (*f)(Node *from, Node *to, int weight, gpointer d),
		Graph *graph,
		gpointer d);

#endif /* CONTROLLER_H__ */
