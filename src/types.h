#ifndef TYPES_H__
#define TYPES_H__

#include <gtk/gtk.h>
#include <assert.h>

/* Model
 */
typedef struct Graph Graph;
typedef struct Node Node;

struct Node {
  int id;
  gdouble x;
  gdouble y;
  Node *next;
};

struct Graph {
  Node *head;
  Node *tail;
  int node_cnt; // node count
  int **adj_m;  // adjacency matrix
};

typedef struct Ctl Ctl;

/* Controller
 */

enum STATE {
  ADD_N,
  MOVE_N,
  SEL_N,
  DEL_N,
  STRT_E,
  END_E,
  SEL_E,
  DEL_E,
  PAN,
};

enum EVENT {
  MOTION,
  L_CLICK,
  R_CLICK,
  L_DRAG_BEGIN,
  R_DRAG_BEGIN,
  L_DRAG_UPDATE,
  R_DRAG_UPDATE,
  L_DRAG_END,
  R_DRAG_END,
  DESTROY,
  RESIZE,
};

struct Ctl {
  /* control
   * selected[0] if node,
   * selected[0] & selected[1] if edge
   */
  int selected[2];
  int hovered[2];
  enum STATE state;
  enum EVENT event;
  gdouble x;
  gdouble y;
  
  /* model
   */
  Graph *graph;

  /* view
   */
  cairo_surface_t *surface;
  GtkWidget *drawing_area;
};

#endif /* TYPES_H__ */
