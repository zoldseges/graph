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

/******************************/
/* adj_m: -1 => no connection */
/* 			      */
/*           to to	      */
/*      [ -1 xx xx -1 ]	      */
/* from [ xx -1 xx -1 ]	      */
/* from [ xx xx -1 -1 ]	      */
/*      [ -1 -1 -1 -1 ]	      */
/******************************/
struct Graph {
  Node *head;
  Node *tail;
  int node_cnt;
  /* ** beacuse of memory bug.
   * reproduce commit 8f063c1
   */
  int **adj_m;
  int row_sz;
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
