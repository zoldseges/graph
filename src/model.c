#define DEBUG

#include "debug.h"
#include "model.h"

void walk_nodes(const Graph *graph, Node **curr)
{
  /* if called with graph */
  if(graph){
    *curr = graph->head;
    /* if called with NULL */
  } else {
    *curr = (*curr)->next;
  }
}

void run_function_on_nodes(void (*f)(Node *n, gpointer d),
			   Graph *g,
			   gpointer d)
{
  Node *curr = NULL;
  walk_nodes(g, &curr);
  while(curr){
    f(curr, d);
    walk_nodes(NULL, &curr);
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

