/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlldeltoleft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:11:55 by uhand             #+#    #+#             */
/*   Updated: 2019/06/24 13:12:31 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlldeltoleft(t_dllist **alst, void (*del)(void*, size_t))
{
	t_dllist	**list;

	if (!alst || !*alst || !del)
		return ;
	list = alst;
	ft_dlldeltoleft(alst = &alst[0]->left, del);
	ft_dlldelone(list, del);
	list = alst;
}
