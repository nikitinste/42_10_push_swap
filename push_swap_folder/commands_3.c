/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 19:41:56 by uhand             #+#    #+#             */
/*   Updated: 2019/06/26 18:38:24 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_b(t_ps_prms *p, char *command)
{
	t_dllist	*second;

	if (!p->stack_a)
		return ;
	second = p->stack_a->right;
	if (second)
		second->left = NULL;
	p->stack_a->right = p->stack_b;
	if (p->stack_b)
		p->stack_b->left = p->stack_a;
	p->stack_b = p->stack_a;
	p->stack_a = second;
	p->len_a--;
	p->len_b++;
	if (command)
		ft_printf("%s\n", command);
}

void	push_a(t_ps_prms *p, char *command)
{
	t_dllist	*second;

	if (!p->stack_b)
		return ;
	second = p->stack_b->right;
	if (second)
		second->left = NULL;
	p->stack_b->right = p->stack_a;
	if (p->stack_a)
		p->stack_a->left = p->stack_b;
	p->stack_a = p->stack_b;
	p->stack_b = second;
	p->len_a++;
	p->len_b--;
	if (command)
		ft_printf("%s\n", command);
}

void	reset_position_a(t_ps_prms *p)
{
	t_dllist 	*ptr;
	t_content	*c;
	int			i;

	ptr = p->stack_a;
	i = p->len_b;
	while (ptr)
	{
		c = ptr->content;
		c->pos = i;
		i++;
		ptr = ptr->right;
	}
}

void	reset_position_b(t_ps_prms *p)
{
	t_dllist 	*ptr;
	t_content	*c;
	int			i;

	ptr = p->stack_b;
	i = p->len_b - 1;
	while (ptr)
	{
		c = ptr->content;
		c->pos = i;
		i--;
		ptr = ptr->right;
	}
}