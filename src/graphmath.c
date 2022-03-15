#include "types.h"

int rdist(Point p1, Point p2)
{
  return round(sqrt((pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)))); 
}  

