/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_linked_stack.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:29:14 by uhand             #+#    #+#             */
/*   Updated: 2019/06/30 19:43:42 by uhand            ###   ########.fr       */
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

t_dllist	*copy_linked_stack(t_dllist *src, t_dllist *dst)
{
	t_dllist	*tmp;
	t_dllist	*prev;

	if (!src)
		return (NULL);
	if (!(dst = (t_dllist*)malloc(sizeof(t_dllist))))
		return (NULL);
	dst->content = src->content;
	dst->content_size = src->content_size;
	dst->left = src->left;
	prev = dst;
	src = src->right;
	while (src)
	{
		if (!(tmp = (t_dllist*)malloc(sizeof(t_dllist))))
			return (free_lists_r(dst));
		tmp->content = src->content;
		tmp->content_size = src->content_size;
		prev->right = tmp;
		tmp->left = prev;
		tmp = tmp->right;
		prev = prev->right;
		src = src->right;
	}
	return (dst);
}
