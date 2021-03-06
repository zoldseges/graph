#include "debug.h"
#include "controller.h"
#include "view.h"

static void motion_handler(UNUSED GtkEventControllerMotion	*self,
			          gdouble			 x,
			          gdouble			 y,
                                  gpointer			 ctl_data)
{
  Ctl *ctl = (Ctl*)ctl_data;
  ctl->pos.x = x;
  ctl->pos.y = y;
  ctl->event = MOTION;
  ctl_handler(ctl);
}

    /*************************************************/
    /* 1 = left button.				     */
    /* 2 = middle button (pressing the scroll wheel) */
    /* 3 = right button.			     */
    /* 4 = turn scroll wheel up.		     */
    /* 5 = turn scroll wheel down.		     */
    /* 6 = push scroll wheel left.		     */
    /* 7 = push scroll wheel right.		     */
    /* 8 = 4th button (aka browser backward button)  */
    /*************************************************/
static void click_handler(	 GtkGestureClick	*gesture,
			  UNUSED int			 n_press,
			         gdouble		 x,
			         gdouble		 y,
				 gpointer		 ctl_data)  
{
  guint button = gtk_gesture_single_get_current_button
    (GTK_GESTURE_SINGLE(gesture));
  Ctl *ctl = (Ctl*)ctl_data;

  ctl->pos.x = x;
  ctl->pos.y = y;
  switch (button) {
  case 1:
    ctl->event = L_CLICK;
    break;
  case 2:
    ctl->event = M_CLICK;
    break;
  case 3:
    ctl->event = R_CLICK;
    break;
  case 4:
    ctl->event = SCROLL_UP;
    break;
  case 5:
    ctl->event = SCROLL_DOWN;
    break;
  default:
    fprintf(stderr, "case: %d\n", button);
    UNIMPLEMENTED;
    break;
  }
  ctl_handler(ctl);
}
 
			  

static void activate(GtkApplication *app, gpointer ctl_data)
{
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *drawing_area;
  GtkGesture *click;
  GtkEventController *motion;
  
  Ctl *ctl = (Ctl*)ctl_data;
  
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Draw");

  g_signal_connect(window, "destroy", G_CALLBACK(free_ctl), NULL);

  frame = gtk_frame_new(NULL);
  gtk_window_set_child(GTK_WINDOW(window), frame);

  drawing_area = gtk_drawing_area_new();
  ctl->drawing_area = drawing_area;
  /* set a minimum size */
  gtk_widget_set_size_request(drawing_area, 800, 600);

  gtk_frame_set_child(GTK_FRAME(frame), drawing_area);

  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area),
				 draw_cb,
				 ctl_data,
				 NULL);

  g_signal_connect(drawing_area, "resize", G_CALLBACK(resize_cb), ctl_data);

  /* leftclick */
  click = gtk_gesture_click_new();
  gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(click),
				GDK_BUTTON_PRIMARY);
  gtk_widget_add_controller(drawing_area,
			    GTK_EVENT_CONTROLLER(click));
  g_signal_connect(click,
		   "pressed",
		   G_CALLBACK(click_handler),
		   ctl_data);

  /* motion */
  motion = gtk_event_controller_motion_new();
  gtk_widget_add_controller(drawing_area,
			    GTK_EVENT_CONTROLLER(motion));
  g_signal_connect(motion,
		   "motion",
		   G_CALLBACK(motion_handler),
		   ctl_data);
  
  gtk_widget_show(window);
}

int main(int argc, char *argv[]) {
  GtkApplication *app;
  int status;
  Ctl ctl = {0};
  ctl_init(&ctl);

  app = gtk_application_new("hu.plkvcs.graph", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), (gpointer) &ctl);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
