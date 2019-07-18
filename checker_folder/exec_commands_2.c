/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 19:26:29 by uhand             #+#    #+#             */
/*   Updated: 2019/07/18 11:43:49 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	rotate_a(t_check_prms *p)
{
	t_list	*ptr;
	t_list	*last_ptr;

	if (!p->stack_a || !p->stack_a->next)
		return ;
	ptr = p->stack_a->next;
	last_ptr = p->stack_a;
	while (last_ptr->next != NULL)
		last_ptr = last_ptr->next;
	last_ptr->next = p->stack_a;
	p->stack_a->next = NULL;
	p->stack_a = ptr;
}

void	rotate_b(t_check_prms *p)
{
	t_list	*ptr;
	t_list	*last_ptr;

	if (!p->stack_b || !p->stack_b->next)
		return ;
	ptr = p->stack_b->next;
	last_ptr = p->stack_b;
	while (last_ptr->next != NULL)
		last_ptr = last_ptr->next;
	last_ptr->next = p->stack_b;
	p->stack_b->next = NULL;
	p->stack_b = ptr;
}

void	rotate_ab(t_check_prms *p)
{
	rotate_a(p);
	rotate_b(p);
}

void	rev_rot_a(t_check_prms *p)
{
	t_list	*ptr;
	t_list	*prelast_ptr;

	if (!p->stack_a || !p->stack_a->next)
		return ;
	prelast_ptr = p->stack_a;
	while (prelast_ptr->next->next != NULL)
		prelast_ptr = prelast_ptr->next;
	ptr = prelast_ptr->next;
	ptr->next = p->stack_a;
	prelast_ptr->next = NULL;
	p->stack_a = ptr;
}

void	rev_rot_b(t_check_prms *p)
{
	t_list	*ptr;
	t_list	*prelast_ptr;

	if (!p->stack_b || !p->stack_b->next)
		return ;
	prelast_ptr = p->stack_b;
	while (prelast_ptr->next->next != NULL)
		prelast_ptr = prelast_ptr->next;
	ptr = prelast_ptr->next;
	ptr->next = p->stack_b;
	prelast_ptr->next = NULL;
	p->stack_b = ptr;
}
