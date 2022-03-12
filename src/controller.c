#include <math.h>
#include "debug.h"
#include "types.h"
#include "view.h"
#include "model.h"
#include "geometry.h"

enum MARKED marked_type(Marked *marked)
{
  enum MARKED ret = NONE;

  if(marked->elem[0]) {
    ret = NODE;
  }

  if(marked->elem[1]) {
    ret = EDGE;
  }

  return ret;
}

void marked_call(void (*f)(Node *node[2], gpointer d),
		 Marked *marked,
		 enum MARKED type,
		 gpointer d)
{
  Marked *curr = marked;
  
  while(curr){
    if((marked_type(curr) == type) || (ANY == type)){
      f(marked->elem, d);
    }
    curr = curr->next;
  }
}

void set_marked(Marked *m, Node *node1, Node *node2)
{
  m->elem[0] = node1;
  m->elem[1] = node2;
}

int node_cursor_distance(Node *node, gpointer mouse_pos)
{
  /* pos[0] = x, pos[1] = y */
  Point *pos = (Point *)mouse_pos;
  return rdist(node->p, *pos);
}

// TODO implement for edges too
void set_hovered(Ctl *ctl, Point mouse_pos)
{
  const int hover_dist = 40;

  Node *node = NULL;
  
  /* INT_MAX ~ INFINITY */
  int node_dist = INT_MAX;
  UNUSED int edge_dist = INT_MAX;
  
  node = nodes_filter_one(node_cursor_distance,
			  ctl->graph,
			  (gpointer) &mouse_pos);

  if(node){
    node_dist = rdist(node->p, mouse_pos);
  }
  // TODO implement for edges too
  if(node_dist < hover_dist){
    set_marked(ctl->hovered, node, NULL);
  } else {
    set_marked(ctl->hovered, NULL, NULL);
  }
  DEBUG_NEGINT(node_dist);
}

void init_ctl(Ctl *ctl)
{
  const int init_row_sz = 8;

  ctl->graph	= calloc(1, sizeof(Graph));
  ctl->hovered	= calloc(1, sizeof(Marked));
  ctl->selected = calloc(1, sizeof(Marked));

  DEBUG_NULL(ctl->graph);
  DEBUG_NULL(ctl->hovered);
  DEBUG_NULL(ctl->selected);

  ctl->hovered->next	= NULL;
  ctl->hovered->elem[0] = NULL;
  ctl->hovered->elem[1] = NULL;
  ctl->hovered->next	= NULL;

  ctl->selected->next	 = NULL;
  ctl->selected->elem[0] = NULL;
  ctl->selected->elem[1] = NULL;
  ctl->selected->next	 = NULL;

  ctl->graph->node_cnt = 0;

  ctl->graph->row_sz = init_row_sz;
  ctl->graph->adj_m = malloc(init_row_sz * init_row_sz * sizeof(int));
  DEBUG_NULL(ctl->graph->adj_m);
  for(int i = 0; i < init_row_sz; i++) {
    for(int j = 0; j < init_row_sz; j++) {
      *(ctl->graph->adj_m + (init_row_sz * i) + j) = -1;
    }
  }
}

// TODO merge ctl states and events
void ctl_handler(Ctl *ctl)
{
  switch(ctl->event) {
  case MOTION:
    switch(ctl->mode) {

    case ADD_NODE:
    case SELECT:
      set_hovered(ctl, ctl->pos);
      ctl->mode = SELECT;
      break;
      
    default:
      fprintf(stderr, "case: %d\n", ctl->event);
      UNIMPLEMENTED;
      break;
    }
    break;
    /* MOTION END */
  case L_CLICK:
    /* set mode */
    if(marked_type(ctl->hovered) == NONE) {
      ctl->mode = ADD_NODE;
    }

    /* act */
    switch(ctl->mode) {
      
    case ADD_NODE:
      add_node(ctl->graph, ctl->pos);
      set_marked(ctl->selected, NULL, NULL);
      set_hovered(ctl, ctl->pos);
      break;
      
    case SELECT:
      set_marked(ctl->selected,
		 ctl->hovered->elem[0],
		 ctl->hovered->elem[1]);
      break;
      
    default:
      fprintf(stderr, "case: %d\n", ctl->event);
      UNIMPLEMENTED;
      break;
    }
    break;
    /* L_CLICK END */
  default:
    fprintf(stderr, "case: %d\n", ctl->event);
    UNIMPLEMENTED;
    break;
  }
  gtk_widget_queue_draw(ctl->drawing_area);
}

void free_ctl(UNUSED Ctl *ctl)
{
  UNIMPLEMENTED;
}
