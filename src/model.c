#include "debug.h"

void grow_matrix(Graph *graph)
{
  int *new_m = NULL;
  // crash on overflow
  DEBUG_ZERO(graph->row_sz < (graph->row_sz * 2));
  // double both directions
  graph->row_sz *= 2;
  new_m = realloc(graph->adj_m,
		  graph->row_sz * graph->row_sz * sizeof(int));
  DEBUG_NULL(new_m);

  // initialize newly allocated memory
  for(int i = graph->node_cnt; i < graph->row_sz; i++){
    for(int j = graph->node_cnt; j < graph->row_sz; j++){
      *(new_m + (graph->row_sz * i) + j) = -1;
    }
  }
  
  graph->adj_m = new_m;
}

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
  DEBUG_ZERO(!(graph->node_cnt > graph->row_sz));

  if(graph->node_cnt == graph->row_sz) {
     grow_matrix(graph);
  }
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

void set_edge_weight(Graph *graph,
		     Node *node_from,
		     Node *node_to,
		     int weight)
{
  
}
