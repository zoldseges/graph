#include "debug.h"
#include "graphmath.h"

void add_node(Graph *graph, Point pos)
{
  Node *new = calloc(1, sizeof(Node));
  
  new->p = pos;
  new->next = NULL;

  if(!graph->head){
    new->id = 0;
    graph->head = new;
    graph->tail = new;
  } else {
    new->id = graph->node_cnt;
    graph->tail->next = new;
    graph->tail = new;
  }

  // crash if node_cnt > row_sz
  graph->node_cnt++;

  if(graph->node_cnt == graph->sm.row_sz) {
     grow_matrix(&graph->sm);
  }

  DEBUG_ZERO(!(graph->node_cnt > graph->sm.row_sz));
}

void delete_node(UNUSED Graph *graph,
		 UNUSED Node *node)
{
  UNIMPLEMENTED;
}

void move_node(UNUSED Graph *graph,
	       UNUSED Node *node,
	       UNUSED Point pos)
{
  UNIMPLEMENTED;
}

