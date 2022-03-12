#include <math.h>
#include "debug.h"
#include "types.h"
#include "view.h"
#include "model.h"
#include "geometry.h"

int node_cursor_distance(Node *node, gpointer mouse_pos)
{
  /* pos[0] = x, pos[1] = y */
  gdouble *pos = (gpointer)mouse_pos;
  return rdist(node->x, node->y, pos[0], pos[1]);
}

// TODO implement for edges too
void set_hovered(Ctl *ctl,
		 gdouble x,
		 gdouble y)
{
  const int hover_dist = 40;
  double packed_pos[2] = {x, y};

  Node *node = NULL;
  
  int node_id = -1;
  int edge_id = -1;

  /* INT_MAX ~ INFINITY */
  int node_dist = INT_MAX;
  int edge_dist = INT_MAX;
  
  node_id = nodes_filter_one(node_cursor_distance,
			     ctl->graph,
			     packed_pos);
  select_node(&node, ctl->graph, node_id);
  if(node){
    node_dist = rdist(node->x, node->y, x, y);
  }
  // TODO implement for edges too
  if((node_dist < hover_dist) && (node_id != -1)){
    ctl->hovered[0] = node_id;
    ctl->hovered[1] = 0;
  } else {
    ctl->hovered[0] = 0;
    ctl->hovered[1] = 0;
  }
  DEBUG_NEGINT(node_dist);
}

void init_ctl(Ctl *ctl)
{
  ctl->graph = calloc(1, sizeof(Graph));
  DEBUG_NULL(ctl->graph);
}

void ctl_handler(Ctl		*ctl,
		 gdouble	 x,
		 gdouble	 y)
{
  /* state */
  switch (ctl->state) {
  case ADD_N:
    add_node(ctl->graph, x, y);
    set_hovered(ctl, x, y);
    break;
  default:
    break;
  }

  /* event */
  switch (ctl->event) {
  case MOTION:
    set_hovered(ctl, x, y);
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
