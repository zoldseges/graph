#ifndef CONTROLLER_H__
#define CONTROLLER_H__

#include "types.h"
#include "view.h"

void init_ctl(Ctl *ctl);

void ctl_handler(Ctl *ctl,
	     gdouble x,
	     gdouble y);

void free_ctl(Ctl *ctl);

#endif /* CONTROLLER_H__ */
