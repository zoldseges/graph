#define DEBUG

#include <gtk/gtk.h>

#include "debug.h"
#include "types.h"
#include "model.h"

static const int node_r = 5;

static void draw_node(Node *node, cairo_t *cr)
{
  cairo_arc(cr, node->x, node->y, node_r, 0, 2*M_PI);
  cairo_fill(cr);
}

void draw_cb(UNUSED	GtkDrawingArea	*dawing_area,
	     		cairo_t		*cr,
	     UNUSED	int		 width,
	     UNUSED	int		 height,
	     		gpointer	 data)
{
  Ctl *ctl = (Ctl*)data;
  Graph *graph = ctl->graph;
  cairo_surface_t *surface = ctl->surface;

  cairo_set_source_surface(cr, surface, 0, 0);
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_paint(cr);

  cairo_set_source_rgb(cr, 0, 0, 0);

  for(Node *curr = walk_nodes(graph);
      curr;
      curr = walk_nodes(NULL))
    {
      draw_node(curr, cr);
    }
}

// TODO ratinalize this function (it was copy-paste)
void resize_cb(       GtkWidget *widget,
	       UNUSED int	 width,
	       UNUSED int	 height,
	              gpointer	 data)
{
  Ctl *ctl = (Ctl*)data;
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

