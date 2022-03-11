#include "debug.h"
#include "types.h"
#include "view.h"
#include "model.h"

void init_ctl(Ctl *ctl)
{
  ctl->graph = calloc(1, sizeof(Graph));
  DEBUG_NULL(ctl->graph);
}

void ctl_handler(Ctl *ctl,
	     int x,
	     int y)
{
  switch (ctl->state) {
  case ADD_N:
    add_node(ctl->graph, x, y);
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
