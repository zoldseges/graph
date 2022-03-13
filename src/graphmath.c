#include <math.h>
#include <limits.h>
#include "debug.h"
#include "types.h"

int rdist(Point p1, Point p2)
{
  return round(sqrt((pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)))); 
}  

void set_matrix(Matrix m,
		int row,
		int col,
		int weight)
{
  *(m.pm + (m.row_sz * row) + col) = weight;
}

void grow_matrix(Matrix *old)
{
  Matrix new = {0};
  //crash on overflow
  DEBUG_ZERO(old->row_sz < (old->row_sz * 2));
  new.row_sz = old->row_sz * 2;

  new.pm = calloc(new.row_sz * new.row_sz, sizeof(int));
  DEBUG_NULL(new.pm);

  for(int i = 0; i < old->row_sz; i++){
    for(int j = 0; j < old->row_sz; j++){
      set_matrix(new, i, j,
		 *(old->pm + (old->row_sz * i) + j));
    }
  }

  for(int i = 0; i < new.row_sz; i++){
    for(int j = old->row_sz; j < new.row_sz; j++){
      set_matrix(new, i, j, INT_MAX);
    }
  }

  for(int i = old->row_sz; i < new.row_sz; i++){
    for(int j = 0; j < old->row_sz; j++){
      set_matrix(new, i, j, INT_MAX);
    }
  }

  free(old->pm);
  old->pm = new.pm;
  old->row_sz = new.row_sz;
}

