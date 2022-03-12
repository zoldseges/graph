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
  int *adj_m;  // adjacency matrix
  int m_size;
};

typedef struct Ctl Ctl;

enum MARKED {
  NONE,
  NODE,
  EDGE,
  ANY,
};

struct Marked {
  /* control
   * marked[0] if node,
   * marked[0] & marked[1] if edge
   */
  Node *elem[2];
  Marked *next;
};

enum EVENT {
  MOTION,
  L_CLICK,
  M_CLICK,
  R_CLICK,
  SCROLL_UP,
  SCROLL_DOWN,
  L_DRAG_BEGIN,
  R_DRAG_BEGIN,
  L_DRAG_UPDATE,
  R_DRAG_UPDATE,
  L_DRAG_END,
  R_DRAG_END,
  DESTROY,
  RESIZE,
};

enum MODE {
  ADD_NODE,
  MOVE_NODE,
  BEGIN_EDGE,
  END_EDGE,
  SELECT,
  DELETE,
};

struct Ctl {
  /* control */
  enum MODE mode;
  Marked *hovered;
  Marked *selected;
  Point pos;

  enum EVENT event;

  /* model */
  Graph *graph;

  /* view */
  cairo_surface_t *surface;
  GtkWidget *drawing_area;
};

#endif /* TYPES_H__ */
