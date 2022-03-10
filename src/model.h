#ifndef MODEL_H__
#define MODEL_H__

#include "types.h"

void add_node(Graph *graph, double x, double y);
void delete_node(Graph *graph, double id);
void move_node(Graph *graph, double id, double x, double y);

void add_edge(Graph *graph, double id_from, double id_to);
void delete_edge(Graph *graph, double id_from, double id_to);

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
