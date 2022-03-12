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
  ctl->graph	= calloc(1, sizeof(Graph));
  ctl->hovered	= calloc(1, sizeof(Marked));
  ctl->selected = calloc(1, sizeof(Marked));

  ctl->hovered->next	= NULL;
  ctl->hovered->elem[0] = NULL;
  ctl->hovered->elem[1] = NULL;
  ctl->hovered->next = NULL;

  ctl->selected->next	 = NULL;
  ctl->selected->elem[0] = NULL;
  ctl->selected->elem[1] = NULL;
  ctl->selected->next = NULL;


  DEBUG_NULL(ctl->graph);
  DEBUG_NULL(ctl->hovered);
  DEBUG_NULL(ctl->selected);
}

void ctl_handler(Ctl *ctl)
{
  /* state */
  switch (ctl->state) {
  case ADD_N:
    add_node(ctl->graph, ctl->pos);
    set_hovered(ctl, ctl->pos);
    break;
  default:
    break;
  }

  /* event */
  switch (ctl->event) {
  case MOTION:
    set_hovered(ctl, ctl->pos);
    break;
  default:
    break;
  }
  gtk_widget_queue_draw(ctl->drawing_area);
}

void free_ctl(UNUSED Ctl *ctl)
{
  UNIMPLEMENTED;
}
