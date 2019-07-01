/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_normalise.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 18:22:36 by uhand             #+#    #+#             */
/*   Updated: 2019/07/01 22:13:35 by stepa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void swap(t_dllist **stack)
{
	t_content	*content;
	size_t		content_size;

	content = stack[0]->content;
	content->pos++;
	stack[0]->content = stack[0]->right->content;
	stack[0]->right->content = content;
	if (stack[0]->content_size != stack[0]->right->content_size)
	{
		content_size = stack[0]->content_size;
		stack[0]->content_size = stack[0]->right->content_size;
		stack[0]->right->content_size = content_size;
	}
}

static void	rotate(t_dllist **stack)
{
	t_dllist	*last;
	t_dllist	*tmp;

	if (stack[0]->right)
		if (!stack[0]->right->right)
		{
			swap(stack);
			return ;
		}
	last = stack[0];
	while (last->right)
		last = last->right;
	tmp = stack[0]->right;
	tmp->left = NULL;
	stack[0]->right = NULL;
	stack[0]->left = last;
	last->right = stack[0];
	stack[0] = tmp;
}

static void	find_norm_way_a(int len, t_dllist *stack, int *way, int start)
{
	t_way	w;

	w.rot = 0;
	w.min = -1;
	while (w.rot < len)
	{
		w.i = 0;
		w.pos = 0;
		w.neg = 0;
		w.ptr = stack;
		while (w.ptr)
		{
			w.c = (t_content*)w.ptr->content;
			w.bias = (w.i + start) - w.c->sort_pos;
			if (w.bias < 0)
				w.neg += ft_abs(w.bias);
			else
				w.pos += w.bias;
			w.i++;
			w.ptr = w.ptr->right;
		}
		set_way_params(&w, way, len);
		rotate(&stack);
		w.rot++;
	}
}

static void	find_norm_way_b(int len, t_dllist *stack, int *way, int start)
{
	t_way	w;

	w.rot = 0;
	w.min = -1;
	while (w.rot < len)
	{
		w.i = start;
		w.pos = 0;
		w.neg = 0;
		w.ptr = stack;
		while (w.ptr)
		{
			w.c = (t_content*)w.ptr->content;
			w.bias = (w.i + start) - w.c->sort_pos;
			if (w.bias < 0)
				w.neg += ft_abs(w.bias);
			else
				w.pos += w.bias;
			w.i--;
			w.ptr = w.ptr->right;
		}
		set_way_params(&w, way, len);
		rotate(&stack);
		w.rot++;
	}
}

static void	get_conclusion(t_ps_prms *p, t_normalise *n)
{
	int		way_len;

	if ((n->way_a > 0 && n->way_b < 0) || (n->way_a < 0 && n->way_b > 0))
	{
		way_len = ft_abs(n->way_a) + ft_abs(n->way_b);
		n->rev_a = n->way_a - p->len_a;
		n->rev_b = n->way_b - p->len_b;
		if (way_len > ft_abs(n->way_a - n->rev_b) \
			|| way_len > ft_abs(n->way_b - n->rev_a))
			way_shortening(n);
		return ;
	}
	if (ft_abs(n->way_a) > ft_abs(n->way_b))
	{
		n->way_ab = n->way_b;
		n->way_a -= n->way_b;
		n->way_b = 0;
		return ;
	}
	n->way_ab = n->way_a;
	n->way_b -= n->way_a;
	n->way_a = 0;
}

int			normalise(t_ps_prms *p, t_cmd_gen *g)
{
	t_normalise	n;

	if (p->stack_a && p->len_a > 1)
	{
		if(!(n.stack_a = copy_linked_stack(p->stack_a, n.stack_a)))
			exit (0);
	}
	else
		n.stack_a = NULL;
	if (p->stack_b && p->len_b > 1)
	{
		if(!(n.stack_b = copy_linked_stack(p->stack_b, n.stack_b)))
			exit (0);
	}
	else
		n.stack_b = NULL;
	n.way_a = 0;
	n.way_b = 0;
	n.way_ab = 0;
	if (n.stack_a)
		find_norm_way_a(p->len_a, n.stack_a, &n.way_a, p->len_b);
	if (n.stack_b)
		find_norm_way_b(p->len_b, n.stack_b, &n.way_b, (p->len_b - 1));
	get_conclusion(p, &n);
	run_commands(p, g, &n);
	return (1);
}
