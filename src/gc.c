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

void	gc_exit_error(t_gc *gc, char *msg)
{
	gc_clean(&gc, GC_DESTROY_SELF);
	perror(msg);
	exit(EXIT_FAILURE);
}

void	*gc_malloc(t_gc *gc, size_t size, t_gc_flag flag)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		gc_exit_error(gc, "malloc");
	if (gc)
		gc_append(gc, ptr, flag);
	return (ptr);
}

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
 * @param t_gc_flag flag	a flag describing which dustbin to be appended.
 * @return t_gc*			an instance of t_gc.
 */
t_gc	*gc_append(t_gc *self, void *garbage, t_gc_flag flag)
{
	t_dustbin	*new;

	if (!self || !garbage)
		return (NULL);
	new = (t_dustbin *)malloc(sizeof(t_dustbin));
	if (!new)
		return (gc_clean(&self, GC_DESTROY_SELF), NULL);
	new->garbage = garbage;
	if (flag & GC_ALL)
	{
		new->next = self->dustbin;
		self->dustbin = new;
	}
	else if (flag & GC_TMP)
	{
		new->next = self->tmp_dustbin;
		self->tmp_dustbin = new;
	}
	else
		return (gc_clean(&self, GC_DESTROY_SELF), NULL);
	return (self);
}

/**
 * @brief Clear list
 * 
 * @param t_dustbin *dustbin	a pointer to dustbin that shall to be cleared.
 */
void	gc_clear_dustbin(t_dustbin *dustbin)
{
	t_dustbin	*to_free;

	while (dustbin)
	{
		to_free = dustbin;
		dustbin = dustbin->next;
		free(to_free->garbage);
		free(to_free);
	}
}

/**
 * @brief Clean all dustbin grabages.
 * 
 * @param t_gc	**self		an instance of t_gc.
 * @param t_gc_flag flag	a flag describing which dustbin to be freed.
 */
void	gc_clean(t_gc **self, t_gc_flag flag)
{
	if (!self || !*self)
		return ;
	if (flag & GC_DESTROY_SELF || flag & GC_ALL)
	{
		gc_clear_dustbin((*self)->dustbin);
		gc_clear_dustbin((*self)->tmp_dustbin);
		if (flag & GC_DESTROY_SELF)
		{
			free(*self);
			*self = NULL;
		}
	}
	else if (flag & GC_TMP)
	{
		gc_clear_dustbin((*self)->tmp_dustbin);
		(*self)->tmp_dustbin = NULL;
	}
}
