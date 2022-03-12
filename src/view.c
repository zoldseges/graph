#define DEBUG

#include <gtk/gtk.h>

#include "debug.h"
#include "types.h"
#include "model.h"

static const int node_r = 5;

static void draw_node(Node *node, gpointer data)
{
  cairo_t *cr = (cairo_t *)data;
  cairo_arc(cr, node->x, node->y, node_r, 0, 2*M_PI);
  cairo_fill(cr);
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
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_paint(cr);

  cairo_set_source_rgb(cr, 0, 0, 0);

  nodes_call(draw_node, graph, (gpointer) cr);
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

