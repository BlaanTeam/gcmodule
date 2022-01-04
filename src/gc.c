#include "gc.h"

t_gc	*gc_init(void)
{
	t_gc	*gc;

	gc = (t_gc*)malloc(sizeof(t_gc));
	if (!gc)
		return (NULL);
	gc->dustbin = NULL;
	gc->append = &gc_append;
	gc->clean = &gc_clean;
	return (gc);
}

t_gc	*gc_append(t_gc *self, void *garbage)
{
	t_dustbin	*new;

	new = (t_dustbin *)malloc(sizeof(t_dustbin));
	new->garbage = garbage;
	new->next = self->dustbin;
	self->dustbin = new;
	return (self);
}

t_gc	*gc_clean(t_gc *self)
{
	// clean all dustbin garbages.
	(void)self;
	return (self);
}
