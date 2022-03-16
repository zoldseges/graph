#ifndef TYPES_H__
#define TYPES_H__

#include <gtk/gtk.h>

/* Model
 */
typedef struct Marked Marked;
typedef struct Node Node;
typedef struct Graph Graph;
typedef struct Point Point;
typedef struct Matrix Matrix;
typedef struct Ctl Ctl;

/**************************************/
/* sm struct matrix		      */
/* it represents the adjecency matrix */
/* INF = INT_MAX => no connection     */
/* 				      */
/*           to to		      */
/*      [ INF xxx xxx INF ]	      */
/* from [ xxx INF xxx INF ]	      */
/* from [ xxx xxx INF INF ]	      */
/*      [ INF INF INF INF ]	      */
/**************************************/
struct Matrix {
  int *pm;
  int row_sz;
};

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
  int node_cnt;
  Matrix sm;
};

enum MARKED {
  NO_MARKED,
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
};

enum EVENT {
  MOTION,
  L_CLICK,
  /* M_CLICK, */
  /* R_CLICK, */
  /* SCROLL_UP, */
  /* SCROLL_DOWN, */
  /* L_DRAG_BEGIN, */
  /* R_DRAG_BEGIN, */
  /* L_DRAG_UPDATE, */
  /* R_DRAG_UPDATE, */
  /* L_DRAG_END, */
  /* R_DRAG_END, */
  /* DESTROY, */
  /* RESIZE, */
};

enum MODE {
  SELECT,
  START_EDGE,
  /* MOVE_NODE, */
  /* DELETE, */
};

struct Ctl {
  /* control */
  Marked *hovered;
  Marked *selected;
  Point pos;

  enum MODE mode;
  enum EVENT event;

  /* model */
  Graph *graph;

  /* view */
  cairo_surface_t *surface;
  GtkWidget *drawing_area;
};

#endif /* TYPES_H__ */
