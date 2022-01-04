#ifndef GC_H
#define GC_H
#include <stdlib.h>

typedef struct s_dustbin
{
	void				*garbage;
	struct s_dustbin	*next;
}	t_dustbin;

typedef struct s_gc
{
	t_dustbin	*dustbin;
	struct s_gc	*(*append)(struct s_gc *, void *);
	struct s_gc	*(*clean)(struct s_gc *);
}	t_gc;

t_gc	*gc_init(void);
t_gc	*gc_append(t_gc *self, void *garbage);
t_gc	*gc_clean(t_gc *self);

#endif
