/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 19:23:39 by uhand             #+#    #+#             */
/*   Updated: 2019/07/18 11:43:02 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	swap_a(t_check_prms *p)
{
	t_list	*ptr;

	if (!p->stack_a || !p->stack_a->next)
		return ;
	ptr = p->stack_a->next;
	p->stack_a->next = p->stack_a->next->next;
	ptr->next = p->stack_a;
	p->stack_a = ptr;
}

void	swap_b(t_check_prms *p)
{
	t_list	*ptr;

	if (!p->stack_b || !p->stack_b->next)
		return ;
	ptr = p->stack_b->next;
	p->stack_b->next = p->stack_b->next->next;
	ptr->next = p->stack_b;
	p->stack_b = ptr;
}

void	swap_ab(t_check_prms *p)
{
	swap_a(p);
	swap_b(p);
}

void	push_a(t_check_prms *p)
{
	t_list	*ptr;

	if (!p->stack_b)
		return ;
	ptr = p->stack_b->next;
	p->stack_b->next = p->stack_a;
	p->stack_a = p->stack_b;
	p->stack_b = ptr;
}

void	push_b(t_check_prms *p)
{
	t_list	*ptr;

	if (!p->stack_a)
		return ;
	ptr = p->stack_a->next;
	p->stack_a->next = p->stack_b;
	p->stack_b = p->stack_a;
	p->stack_a = ptr;
}
