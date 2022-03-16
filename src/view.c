#include "debug.h"
#include "types.h"
#include "controller.h"

#define NODE_R 5

static void set_hex_color(cairo_t *cr, int color)
{
  gdouble blue	= (gdouble)(color & 0xFF) / 0xFF ;
  color >>= 8;
  gdouble green	= (gdouble)(color & 0xFF) / 0xFF ;
  color >>= 8;
  gdouble red	= (gdouble)(color & 0xFF) / 0xFF ;
  cairo_set_source_rgb(cr, red, green, blue);
}

// TODO implement for edges too
static void mark_node(Node *node[2], gpointer data)
{
  cairo_t *cr = (cairo_t *)data;
  cairo_arc(cr, node[0]->p.x, node[0]->p.y, NODE_R, 0, 2*M_PI);
  cairo_fill(cr);
}

static void draw_node(Node *node, gpointer data)
{
  cairo_t *cr = (cairo_t *)data;
  cairo_arc(cr, node->p.x, node->p.y, NODE_R, 0, 2*M_PI);
  cairo_fill(cr);
}

static void draw_edge(Node *from, Node *to, UNUSED int weight, gpointer data)
{
  cairo_t *cr = (cairo_t *)data;
  cairo_move_to(cr, from->p.x, from->p.y);
  cairo_line_to(cr, to->p.x, to->p.y);
  cairo_stroke(cr);
}

void draw_cb(UNUSED	GtkDrawingArea	*dawing_area,
	     cairo_t		*cr,
	     UNUSED	int		 width,
	     UNUSED	int		 height,
	     gpointer	 ctl_data)
{
  Ctl *ctl = (Ctl*)ctl_data;
  Graph *graph = ctl->graph;
  cairo_surface_t *surface = ctl->surface;

  cairo_set_source_surface(cr, surface, 0, 0);
  set_hex_color(cr, 0x000000);
  cairo_paint(cr);

  /* draw edges */
  cairo_save(cr);
  set_hex_color(cr, 0x909090);
  // TODO check how to restore linewidth
  cairo_set_line_width(cr, 1);
  edges_call(draw_edge, ctl->graph, cr);
  cairo_restore(cr);
  /* update curr edge */
  if(ctl->mode == END_EDGE){
    cairo_save(cr);
    set_hex_color(cr, 0xFFEEEE);
    Node curr_pos = {0};
    curr_pos.p.x = ctl->pos.x;
    curr_pos.p.y = ctl->pos.y;
    draw_edge(ctl->selected->elem[0], &curr_pos, 0, (gpointer) cr);
    cairo_restore(cr);
  }

  /* draw nodes */
  cairo_save(cr);
  set_hex_color(cr, 0xFFFFFF);
  nodes_call(draw_node, graph, (gpointer) cr);
  cairo_restore(cr);

  // TODO implement this part for edges too
  /* mark hovered node */
  cairo_save(cr);
  set_hex_color(cr, 0x00FF00);
  marked_call(mark_node, ctl->hovered, NODE, (gpointer) cr);
  cairo_restore(cr);

  /* mark selected node */
  cairo_save(cr);
  /* selected red - edge start purple */
  if(ctl->mode == END_EDGE) {
    /* edge origin and hovered */
    if(marked_equals(ctl->selected, ctl->hovered)){
      set_hex_color(cr, 0xff0ff3);
    } else {
      set_hex_color(cr, 0x8300bf);
    }
  } else {
    set_hex_color(cr, 0xFF0000);
  }
  marked_call(mark_node, ctl->selected, NODE, (gpointer) cr);
  cairo_restore(cr);

}

// TODO ratinalize this function (it was copy-paste)
void resize_cb(       GtkWidget *widget,
		      UNUSED int	 width,
		      UNUSED int	 height,
	              gpointer	 ctl_data)
{
  Ctl *ctl = (Ctl*)ctl_data;
  cairo_surface_t *surface = ctl->surface;
  if(surface){
    cairo_surface_destroy(surface);
    surface = NULL;
  }
  
  if (gtk_native_get_surface(gtk_widget_get_native(widget))){
    surface = gdk_surface_create_similar_surface
      (gtk_native_get_surface(gtk_widget_get_native(widget)),
       CAIRO_CONTENT_COLOR,
       gtk_widget_get_width(widget),
       gtk_widget_get_height(widget));
    ctl->surface = surface;
    /* initialize the surface to white */
    gtk_widget_queue_draw(widget);
  }
}

