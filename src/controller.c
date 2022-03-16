#include "debug.h"
#include "types.h"
#include "graphmath.h"
#include "model.h"

gboolean marked_equals(Marked *a, Marked *b)
{
  gboolean ans = FALSE;
  if((a->elem[0] == b->elem[0]) &&
     (a->elem[1] == b->elem[1])) {
    ans = TRUE;
  }
  return ans;
}

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

Node *get_node_by_id(Graph *graph, int id)
{
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

void edges_call(void (*f)(Node *from, Node *to, int weight, gpointer d),
		Graph *graph,
		gpointer d)
{
  for(int from_i = 0; from_i < graph->node_cnt; from_i++) {
    for(int to_i = 0; to_i < graph->node_cnt; to_i++) {
      int weight = get_weight(graph->sm, from_i, to_i);
      if( weight != INT_MAX ){
	Node *from = get_node_by_id(graph, from_i); 
	Node *to = get_node_by_id(graph, to_i);
	f(from, to, weight, d);
      }
    }
  }
}



Node *select_node(UNUSED Graph *graph, UNUSED int id)
{
  UNIMPLEMENTED;
  Node *curr = NULL;
  return curr;
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

Node *nodes_filter_all(UNUSED gboolean (*f)(Node *n, gpointer d),
		       UNUSED Graph *g,
		       UNUSED gpointer d)
{
  UNIMPLEMENTED;
  return 0;
}

// TODO see controller.h
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

// TODO doesn't walk the list of marked elems
enum MARKED marked_type(Marked *marked)
{
  enum MARKED ret = NO_MARKED;

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
  if((marked_type(marked) == type) || (ANY == type)){
    f(marked->elem, d);
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

void ctl_init(Ctl *ctl)
{
  const int init_row_sz = 8;

  ctl->graph	= calloc(1, sizeof(Graph));
  ctl->hovered	= calloc(1, sizeof(Marked));
  ctl->selected = calloc(1, sizeof(Marked));

  DEBUG_NULL(ctl->graph);
  DEBUG_NULL(ctl->hovered);
  DEBUG_NULL(ctl->selected);

  ctl->hovered->elem[0] = NULL;
  ctl->hovered->elem[1] = NULL;

  ctl->selected->elem[0] = NULL;
  ctl->selected->elem[1] = NULL;

  ctl->graph->node_cnt = 0;

  ctl->graph->sm.row_sz = init_row_sz;
  ctl->graph->sm.pm =
    malloc(init_row_sz * init_row_sz * sizeof(int));
  DEBUG_NULL(ctl->graph->sm.pm);
  for(int i = 0; i < init_row_sz; i++) {
    for(int j = 0; j < init_row_sz; j++) {
      set_matrix(ctl->graph->sm, i, j, INT_MAX);
    }
  }
}

enum ACTION {
  ACT_NONE,
  ACT_ADD_NODE,
  ACT_SEL_NODE,
  ACT_START_EDGE,
  ACT_DRAW_EDGE,
  ACT_END_EDGE,
};

static void do_action(Ctl *ctl, enum ACTION action);

void ctl_handler(Ctl *ctl)
{
  /* CLS(); */
  /* PRINT_HOVERED(ctl); */
  /* PRINT_SELECTED(ctl); */
  /* PRINT_MODE(ctl); */
  /* PRINT_EVENT(ctl); */
  /* PRINT_MATRIX(ctl->graph->sm); */
  enum ACTION action = ACT_NONE;

  set_hovered(ctl, ctl->pos);
  if(ctl->event == MOTION) {
    gtk_widget_queue_draw(ctl->drawing_area);
  }
  switch(ctl->mode) {
  case SELECT:
    switch(ctl->event)
      {
      case L_CLICK:
	{
	  if(marked_type(ctl->hovered) == NO_MARKED) {
	    action = ACT_ADD_NODE;
	  } else if ((marked_equals(ctl->hovered, ctl->selected)) &&
		     (marked_type(ctl->hovered) == NODE)) {
	    action = ACT_START_EDGE;
	  } else {
	    action = ACT_SEL_NODE;
	  }
	} break;

      default:
	break;

      } break;

  case START_EDGE:
    switch (ctl->event)
      {
      case L_CLICK:
	action = ACT_DRAW_EDGE;
	break;

      default:
	break;

      } break;

  case END_EDGE:
    switch(ctl->event)
      {
      case L_CLICK:
	if((marked_type(ctl->hovered) == NODE) &&
	   (!marked_equals(ctl->hovered, ctl->selected))) {
	  action = ACT_END_EDGE;
	}

      default:
	break;

      } break;

  default:
    break;
  }
  if(action != ACT_NONE) do_action(ctl, action);
  gtk_widget_queue_draw(ctl->drawing_area);
}

static void do_action(Ctl *ctl, enum ACTION action)
{
  switch(action) {
  case ACT_NONE:
    break;
  case ACT_ADD_NODE:
    add_node(ctl->graph, ctl->pos);
    set_marked(ctl->selected, NULL, NULL);
    break;

  case ACT_START_EDGE:
    ctl->mode = START_EDGE;
    ctl_handler(ctl);
    break;

  case ACT_SEL_NODE:
    set_marked(ctl->selected,
	       ctl->hovered->elem[0],
	       ctl->hovered->elem[1]);
    break;
    
  case ACT_DRAW_EDGE:
    ctl->mode = END_EDGE;
    ctl_handler(ctl);
    break;

  case ACT_END_EDGE:
    add_edge(ctl->graph,
	     ctl->selected->elem[0],
	     ctl->hovered->elem[0]);
    set_marked(ctl->selected, NULL, NULL);
    ctl->mode = SELECT;
    break;
    
  }
}

void free_ctl(UNUSED Ctl *ctl)
{
  UNIMPLEMENTED;
}
