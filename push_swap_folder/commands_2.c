/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 18:10:29 by uhand             #+#    #+#             */
/*   Updated: 2019/07/01 22:52:04 by stepa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_a(t_ps_prms *p, char *command)
{
	t_dllist	*last;
	t_dllist	*tmp;

	if (!p->stack_a || !p->stack_a->right)
		return ;
	if (!p->stack_a->right->right)
	{
		swap_a(p, NULL);
		if (command)
			ft_printf("%s\n", command);
		return ;
	}
	last = p->stack_a;
	while (last->right)
		last = last->right;
	tmp = p->stack_a->right;
	tmp->left = NULL;
	p->stack_a->right = NULL;
	p->stack_a->left = last;
	last->right = p->stack_a;
	p->stack_a = tmp;
	reset_position_a(p);
	if (command)
		ft_printf("%s\n", command);
}

void	rotate_b(t_ps_prms *p, char *command)
{
	t_dllist	*last;
	t_dllist	*tmp;

	if (!p->stack_b || !p->stack_b->right)
		return ;
	if (!p->stack_b->right->right)
	{
		swap_b(p, NULL);
		if (command)
			ft_printf("%s\n", command);
		return ;
	}
	last = p->stack_b;
	while (last->right)
		last = last->right;
	tmp = p->stack_b->right;
	tmp->left = NULL;
	p->stack_b->right = NULL;
	p->stack_b->left = last;
	last->right = p->stack_b;
	p->stack_b = tmp;
	reset_position_b(p);
	if (command)
		ft_printf("%s\n", command);
}

void	swap_ab(t_ps_prms *p, char *command)
{
	swap_a(p, NULL);
	swap_b(p, NULL);
	if (command)
		ft_printf("%s\n", command);
}

void	swap_a(t_ps_prms *p, char *command)
{
	t_content	*content;
	size_t		content_size;

	if (!p->stack_a || !p->stack_a->right)
		return ;
	content = p->stack_a->content;
	content->pos--;
	p->stack_a->content = p->stack_a->right->content;
	p->stack_a->right->content = content;
	if (p->stack_a->content_size != p->stack_a->right->content_size)
	{
		content_size = p->stack_a->content_size;
		p->stack_a->content_size = p->stack_a->right->content_size;
		p->stack_a->right->content_size = content_size;
	}
	content = p->stack_a->content;
	content->pos++;//!!!
	if (command)
		ft_printf("%s\n", command);
}

void	swap_b(t_ps_prms *p, char *command)
{
	t_content	*content;
	size_t		content_size;

	if (!p->stack_b || !p->stack_b->right)
		return ;
	content = p->stack_b->content;
	content->pos--;
	p->stack_b->content = p->stack_b->right->content;
	p->stack_b->right->content = content;
	if (p->stack_b->content_size != p->stack_b->right->content_size)
	{
		content_size = p->stack_b->content_size;
		p->stack_b->content_size = p->stack_b->right->content_size;
		p->stack_b->right->content_size = content_size;
	}
	content = p->stack_b->content;
	content->pos++;//!!!
	if (command)
		ft_printf("%s\n", command);
}
