#include "debug.h"
#include "model.h"

static void walk_nodes(Node **curr, const Graph *graph)
{
  /* if called with graph */
  if(graph){
    *curr = graph->head;
    /* if called with NULL */
  } else {
    *curr = (*curr)->next;
  }
}

Node *get_node_by_id(Graph *graph, int id){
  Node *curr = NULL;
  walk_nodes(&curr, graph);
  while(curr){
    if(curr->id == id){
      break;
    }
    walk_nodes(&curr, NULL);
  }
  return curr;
}

// TODO see model.h
Node *nodes_filter_all(UNUSED gboolean (*f)(Node *n, gpointer d),
		       UNUSED Graph *g,
		       UNUSED gpointer d)
{
  UNIMPLEMENTED;
  return 0;
}

Node *nodes_filter_one(int (*f)(Node *n, gpointer d),
		       Graph *g,
		       gpointer d)
{
  Node	*curr_node = NULL;
  int	 curr_int  = -1;
  Node	*min_node  = NULL;
  /* INT_MAX ~ INFINITY */
  int	 min_int   = INT_MAX;

  walk_nodes(&curr_node, g);
  while(curr_node){
    curr_int = f(curr_node, d);
    DEBUG_NEGINT(curr_int);
    if(curr_int < min_int) {
      min_node = curr_node;
      min_int = curr_int;
    }
    walk_nodes(&curr_node, NULL);
  }

  return min_node;
}

void nodes_call(void (*f)(Node *n, gpointer d),
		Graph *g,
		gpointer d)
{
  Node *curr = NULL;
  walk_nodes(&curr, g);
  while(curr){
    f(curr, d);
    walk_nodes(&curr, NULL);
  }
}


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
