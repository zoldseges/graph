#include <gtk/gtk.h>
#include <math.h>

int rdist(gdouble x1, gdouble y1, gdouble x2, gdouble y2)
{
  return round(sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)))); 
}  

