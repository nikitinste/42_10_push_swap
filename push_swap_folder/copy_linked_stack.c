/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_linked_stack.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:29:14 by uhand             #+#    #+#             */
/*   Updated: 2019/07/18 13:14:09 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	*free_lists_r(t_dllist *list)
{
	if (!list)
		return (NULL);
	free_lists_r(list->right);
	free(list);
	return (list = NULL);
}

static void	make_normas_magic(t_cpy_lstk *cpy)
{
	cpy->tmp->content = cpy->ptr->content;
	cpy->tmp->content_size = cpy->ptr->content_size;
	cpy->prev->right = cpy->tmp;
	cpy->tmp->left = cpy->prev;
	cpy->prev = cpy->prev->right;
	cpy->ptr = cpy->ptr->right;
}

t_dllist	*copy_linked_stack(t_dllist **src, t_dllist **dst)
{
	t_cpy_lstk	cpy;

	if (!src[0])
		return (NULL);
	if (!(dst[0] = (t_dllist*)malloc(sizeof(t_dllist))))
		return (NULL);
	cpy.ptr = src[0];
	dst[0]->content = cpy.ptr->content;
	dst[0]->content_size = cpy.ptr->content_size;
	dst[0]->left = NULL;
	cpy.prev = dst[0];
	cpy.ptr = cpy.ptr->right;
	while (cpy.ptr)
	{
		if (!(cpy.tmp = (t_dllist*)malloc(sizeof(t_dllist))))
			return (free_lists_r(dst[0]));
		make_normas_magic(&cpy);
	}
	cpy.prev->right = NULL;
	return (dst[0]);
}
