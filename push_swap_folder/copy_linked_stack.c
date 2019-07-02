/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_linked_stack.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:29:14 by uhand             #+#    #+#             */
/*   Updated: 2019/07/02 12:22:44 by stepa            ###   ########.fr       */
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

t_dllist	*copy_linked_stack(t_dllist **src, t_dllist **dst)
{
	t_dllist	*tmp;
	t_dllist	*prev;
	t_dllist	*ptr;


	if (!src[0])
		return (NULL);
	if (!(dst[0] = (t_dllist*)malloc(sizeof(t_dllist))))
		return (NULL);
	ptr = src[0];
	dst[0]->content = ptr->content;
	dst[0]->content_size = ptr->content_size;
	dst[0]->left = NULL;
	prev = dst[0];
	ptr = ptr->right;
	while (ptr)
	{
		if (!(tmp = (t_dllist*)malloc(sizeof(t_dllist))))
			return (free_lists_r(dst[0]));
		tmp->content = ptr->content;
		tmp->content_size = ptr->content_size;
		prev->right = tmp;
		tmp->left = prev;
		prev = prev->right;
		ptr = ptr->right;
	}
	prev->right = NULL;
	return (dst[0]);
}
