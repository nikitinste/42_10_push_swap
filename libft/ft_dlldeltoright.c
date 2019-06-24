/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlldeltoright.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:58:58 by uhand             #+#    #+#             */
/*   Updated: 2019/06/24 13:13:17 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlldeltoright(t_dllist **alst, void (*del)(void*, size_t))
{
	t_dllist	**list;

	if (!alst || !*alst || !del)
		return ;
	list = alst;
	ft_dlldeltoright(alst = &alst[0]->right, del);
	ft_dlldelone(list, del);
	list = alst;
}
