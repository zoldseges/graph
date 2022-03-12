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

void select_node(Node **node, Graph *graph, int id){
  Node *curr = NULL;
  walk_nodes(&curr, graph);
  while(curr){
    if(curr->id == id){
      *node = curr;
      break;
    }
    walk_nodes(&curr, NULL);
  }
}

// TODO see model.h
int nodes_filter_all(gboolean (*f)(Node *n, gpointer d),
		     Graph *g,
		     gpointer d)
{
  UNIMPLEMENTED;
  return 0;
}

int nodes_filter_one(int (*f)(Node *n, gpointer d),
			       Graph *g,
			       gpointer d)
{
  /* return -1 if no match */
  int id	   = -1;
  Node	*curr_node = NULL;
  int	 curr_int  = -1;
  Node	*min_node  = NULL;
  /* INT_MAX ~ INFINITY */
  int	 min_int   = INT_MAX;

  walk_nodes(&curr_node, g);
  while(curr_node){
    curr_int = f(curr_node, d);
    walk_nodes(&curr_node, NULL);

    DEBUG_NEGINT(curr_int);
    if(curr_int < min_int) {
      min_node = curr_node;
      min_int = curr_int;
    }
  }

  if(min_node){
    id = min_node->id;
  }
  return id;
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


// TODO update adj_matrix
void add_node(Graph *graph, gdouble x, gdouble y)
{
  Node *new = calloc(1, sizeof(Node));
  
  new->x = x;
  new->y = y;
  new->next = NULL;

  graph->node_cnt++;

  if(!graph->head){
    new->id = 1;
    graph->head = new;
    graph->tail = new;
  } else {
    new->id = graph->node_cnt;
    graph->tail->next = new;
    graph->tail = new;
  }
}

void delete_node(Graph *graph, gdouble id)
{
  UNIMPLEMENTED;
}

void move_node(Graph *graph, gdouble id, gdouble x, gdouble y)
{
  UNIMPLEMENTED;
}

void add_edge(Graph *graph, gdouble id_from, gdouble id_to)
{
  UNIMPLEMENTED;
}

void delete_edge(Graph *graph, gdouble id_from, gdouble id_to)
{
  UNIMPLEMENTED;
}

