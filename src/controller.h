#ifndef CONTROLLER_H__
#define CONTROLLER_H__

#include "types.h"
#include "view.h"

void init_ctl(Ctl *ctl);

enum MARKED marked_type(Marked *marked);

/* calls `f` on every node in `marked` 
 * which is of type `type`
 * function signature:
 *   void f(Node *n[2], gpointer d);
 */
void marked_call(void (*f)(Node *node[2], gpointer d),
		 Marked *marked,
		 enum MARKED type,
		 gpointer d);


void ctl_handler(Ctl *ctl);

void free_ctl(Ctl *ctl);

#endif /* CONTROLLER_H__ */
