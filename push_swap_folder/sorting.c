/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 18:19:18 by uhand             #+#    #+#             */
/*   Updated: 2019/06/22 14:21:04 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	set_previous(t_list	*lst)
{
	//
}

int		sorting(t_ps_prms *p)
{
	t_shaker	s;

	set_previous(p->stack_a);
	if (!(s.stack = ft_lstcpy(p->stack_a, s.stack)))
		return (0);
	s.left = s.stack;
	return (1);
}
