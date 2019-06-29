/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_normalise.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 18:22:36 by uhand             #+#    #+#             */
/*   Updated: 2019/06/29 19:57:14 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void swap(t_dllist *stack)
{
	t_content	*content;
	size_t		content_size;

	content = stack->content;
	content->pos++;
	stack->content = stack->right->content;
	stack->right->content = content;
	if (stack->content_size != stack->right->content_size)
	{
		content_size = stack->content_size;
		stack->content_size = stack->right->content_size;
		stack->right->content_size = content_size;
	}
}

static void	rotate(t_dllist *stack)
{
	t_dllist	*last;
	t_dllist	*tmp;

	if (!stack->right->right)
	{
		swap(stack);
		return ;
	}
	last = stack;
	while (last->right)
		last = last->right;
	tmp = stack->right;
	tmp->left = NULL;
	stack->right = NULL;
	stack->left = last;
	last->right = stack;
	stack = tmp;
}

static void	find_norm_way(int len, t_dllist *stack, int *way)
{
	t_way	w;

	w.pos = 0;
	w.neg = 0;
	w.i = 0;
	while (w.i < len)
	{
		w.ptr = stack;
		while (w.ptr)
		{
			w.c = w.ptr->content;
			w.bias = w.i - w.c->sort_pos;
			if (w.bias < 0)
				w.neg += w.bias;
			else
				w.pos += w.bias;
				// - la la la
		}
		w.i++;
	}
}

static void	get_conclusion(t_ps_prms *p, t_normalise *n)
{
	//
}

int			normalise(t_ps_prms *p)
{
	t_normalise	n;

	if (p->stack_a && p->len_a > 1)
	{
		if(!(n.stack_a = copy_linked_stack(p->stack_a, n.stack_a)))
			return (0);
	}
	else
		n.stack_a = NULL;
	if (p->stack_b && p->len_b > 1)
	{
		if(!(n.stack_b = copy_linked_stack(p->stack_b, n.stack_b)))
			return (0);
	}
	else
		n.stack_b = NULL;
	n.way_a = 0;
	n.way_b = 0;
	n.way_ab = 0;
	if (n.stack_a)
		find_norm_way(p->len_a, n.stack_a, &n.way_a);
	if (n.stack_b)
		find_norm_way(p->len_b, n.stack_b, &n.way_b);
	get_conclusion(p, &n);
	return (1);
}
