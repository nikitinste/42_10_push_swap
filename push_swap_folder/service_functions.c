/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:31:23 by uhand             #+#    #+#             */
/*   Updated: 2019/07/18 20:20:18 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		error_msg(int prm, t_ps_prms *p)
{
	if (prm)
	{
		ft_dlldel(&p->stack_a, &ft_lstfree);
		ft_dlldel(&p->stack_b, &ft_lstfree);
	}
	ft_putstr_fd("Error\n", 2);
	exit(-1);
}

void	linked_stack_free(void *content, size_t size)
{
	if (content && size)
		return ;
	return ;
}
