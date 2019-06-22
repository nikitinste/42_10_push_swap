/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 13:17:19 by uhand             #+#    #+#             */
/*   Updated: 2019/06/22 13:43:17 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpy(t_list *src, t_list *dst)
{
	t_list	*tmp;

	if (src)
		if (!(dst = ft_lstnew(src->content, src->content_size)))
			return (NULL);
	tmp = dst->next;
	src = src->next;
	while (src)
	{
		if (!(tmp = ft_lstnew(src->content, src->content_size)))
		{
			ft_lstdel(&dst, &ft_lstfree);
			return (NULL);
		}
		tmp = tmp->next;
		src = src->next;
	}
	return (dst);
}
