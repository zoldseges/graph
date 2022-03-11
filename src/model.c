#define DEBUG

#include "debug.h"
#include "model.h"

Node *walk_nodes(const Graph *graph)
{
  static Node *next_node = NULL;
  Node *curr_node = NULL;

  if(graph) {
    curr_node = graph->head;
  } else if (next_node) {
    curr_node = next_node;
  }

  if(curr_node) {
    next_node = curr_node->next;
  }
  
  return curr_node;
}

// TODO update adj_matrix
void add_node(Graph *graph, double x, double y)
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

void delete_node(Graph *graph, double id)
{
  UNIMPLEMENTED;
}

void move_node(Graph *graph, double id, double x, double y)
{
  UNIMPLEMENTED;
}

void add_edge(Graph *graph, double id_from, double id_to)
{
  UNIMPLEMENTED;
}

void delete_edge(Graph *graph, double id_from, double id_to)
{
  UNIMPLEMENTED;
}

