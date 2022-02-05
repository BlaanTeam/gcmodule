/**
 * @file gc.c
 * @author BlaanTeam (blaanteam@gmail.com)
 * @brief The garabage collector source file.
 * @version 0.1
 * @date 2022-01-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "gc.h"

/**
 * @brief Initialize the garbage collector.
 * 
 * @return t_gc*	an instance of t_gc.
 */
t_gc	*gc_init(void)
{
	t_gc	*gc;

	gc = (t_gc *)malloc(sizeof(t_gc));
	if (!gc)
		return (NULL);
	gc->dustbin = NULL;
	gc->tmp_dustbin = NULL;
	gc->append = &gc_append;
	gc->clean = &gc_clean;
	return (gc);
}

/**
 * @brief Append grabage to dustbin.
 * 
 * @param t_gc	self		an instance of t_gc. 
 * @param void	*garbage	a void pointer of garbage.
 * @return t_gc*			an instance of t_gc.
 */
t_gc	*gc_append(t_gc *self, void *garbage)
{
	t_dustbin	*new;

	if (!self || !garbage)
		return (NULL);
	new = (t_dustbin *)malloc(sizeof(t_dustbin));
	if (!new)
		return (gc_clean(self), NULL);
	new->garbage = garbage;
	new->next = self->dustbin;
	self->dustbin = new;
	return (self);
}

/**
 * @brief Clean all dustbin grabages.
 * 
 * @param t_gc	self	an instance of t_gc. 
 */
void	gc_clean(t_gc *self)
{
	t_dustbin	*to_free;

	if (!self)
		return ;
	while (self->dustbin)
	{
		to_free = self->dustbin;
		self->dustbin = self->dustbin->next;
		free(to_free->garbage);
		free(to_free);
	}
	free(self);
	self = NULL;
}