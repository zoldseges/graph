#ifndef MODEL_H__
#define MODEL_H__

#include "types.h"

void add_node(Graph *graph, gdouble x, gdouble y);
void delete_node(Graph *graph, gdouble id);
void move_node(Graph *graph, gdouble id, gdouble x, gdouble y);

void add_edge(Graph *graph, gdouble id_from, gdouble id_to);
void delete_edge(Graph *graph, gdouble id_from, gdouble id_to);

/* Pass NULL to get subsequent node
 * typical use:
 * for(Node *curr = walk_nodes(graph);
 *     curr;
 *     curr = walk_nodes(NULL)) 
 *   {
 *   do_stuff(curr);
 *   }
 */
Node *walk_nodes(const Graph *graph);

#endif /* MODEL_H__ */
