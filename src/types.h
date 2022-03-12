#ifndef TYPES_H__
#define TYPES_H__

#include <gtk/gtk.h>
#include <assert.h>

/* Model
 */
typedef struct Marked Marked;
typedef struct Node Node;
typedef struct Graph Graph;
typedef struct Point Point;

struct Point {
  gdouble x;
  gdouble y;
};

struct Node {
  int id;
  Point p;
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
  EMPTY,
  ADD_N,
  MOVE_N,
  SELECT_N,
  DEL_N,
  STRT_E,
  END_E,
  SELECT_E,
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

enum MARKED {
  NONE,
  NODE,
  EDGE,
};

struct Marked {
  /* control
   * marked[0] if node,
   * marked[0] & marked[1] if edge
   */
  Node *elem[2];
  Marked *next;
};

struct Ctl {
  Marked *hovered;
  Marked *selected;
  
  enum STATE state;
  enum EVENT event;
  
  Point pos;
  
  /* model
   */
  Graph *graph;

  /* view
   */
  cairo_surface_t *surface;
  GtkWidget *drawing_area;
};

#endif /* TYPES_H__ */
