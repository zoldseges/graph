#ifndef CONTROLLER_H__
#define CONTROLLER_H__

#include "types.h"
#include "viewer.h"

void init_ctl(Ctl *ctl);

void ctl_handler(Ctl *ctl,
	     int x,
	     int y);

void free_ctl(Ctl *ctl);

#endif /* CONTROLLER_H__ */
