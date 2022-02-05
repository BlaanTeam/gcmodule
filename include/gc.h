/**
 * @file gc.h
 * @author BlaanTeam (blaanteam@gmail.com)
 * @brief The garbage collector header file
 * @version 0.1
 * @date 2022-01-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
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
	t_dustbin	*tmp_dustbin;
	struct s_gc	*(*append)(struct s_gc *, void *);
	void		(*clean)(struct s_gc *);
}	t_gc;

t_gc	*gc_init(void);
t_gc	*gc_append(t_gc *self, void *garbage);
void	gc_clean(t_gc *self);

#endif
