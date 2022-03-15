#ifndef VIEWER_H__
#define VIEWER_H__

void draw_cb(GtkDrawingArea	*dawing_area,
	     cairo_t		*cr,
	     int		 width,
	     int		 height,
	     gpointer		 ctl_data);

void resize_cb(GtkWidget *widget,
	       int	 width,
	       int	 height,
	       gpointer	 ctl_data);

#endif /* VIEWER_H__ */
