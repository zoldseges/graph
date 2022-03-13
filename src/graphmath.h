#ifndef GEOMETRY_H__
#define GEOMETRY_H__

#include "types.h"

/* rounded distance */
int rdist(Point p1, Point p2);

/* doubles matrix size */
void grow_matrix(Matrix *old);
/* add edge: set matrix weight to 0 or else
 * del edge: set matrix weight to INT_MAX
 */
void set_matrix(Matrix m, int row, int col, int weight);

#endif /* GEOMETRY_H__ */
