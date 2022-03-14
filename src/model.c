#include "debug.h"
#include "graphmath.h"

void set_matrix(Matrix m,
		int row,
		int col,
		int weight)
{
  *(m.pm + (m.row_sz * row) + col) = weight;
}

static void grow_matrix(Matrix *old)
{
  Matrix new = {0};
  //crash on overflow
  DEBUG_ZERO(old->row_sz < (old->row_sz * 2));
  new.row_sz = old->row_sz * 2;

  new.pm = calloc(new.row_sz * new.row_sz, sizeof(int));
  DEBUG_NULL(new.pm);

  for(int i = 0; i < old->row_sz; i++){
    for(int j = 0; j < old->row_sz; j++){
      set_matrix(new, i, j,
		 *(old->pm + (old->row_sz * i) + j));
    }
  }

  for(int i = 0; i < new.row_sz; i++){
    for(int j = old->row_sz; j < new.row_sz; j++){
      set_matrix(new, i, j, INT_MAX);
    }
  }

  for(int i = old->row_sz; i < new.row_sz; i++){
    for(int j = 0; j < old->row_sz; j++){
      set_matrix(new, i, j, INT_MAX);
    }
  }

  free(old->pm);
  old->pm = new.pm;
  old->row_sz = new.row_sz;
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

void add_edge(Graph *graph, Node *from, Node *to)
{
  set_matrix(graph->sm, from->id, to->id, 0);
}
