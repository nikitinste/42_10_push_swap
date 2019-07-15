/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_normalise.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 18:22:36 by uhand             #+#    #+#             */
/*   Updated: 2019/07/15 14:15:59 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	find_norm_way_a(t_ps_prms *p, t_dllist *stack, int *way)
{
	t_way	w;

	w.rot = 0;
	w.min = -1;
	while (w.rot < p->len_a)
	{
		way_init(&w, stack, p->len_b);
		while (w.ptr)
		{
			w.c = (t_content*)w.ptr->content;
			w.bias = w.i - w.c->sort_pos;
			check_bias(&w);
			if (w.bias < 0)
				w.neg += ft_abs(w.bias);
			else
				w.pos += w.bias;
			w.i++;
			w.ptr = w.ptr->right;
		}
		set_way_params(&w, way, p->len_a);
		rotate(&stack);
		w.rot++;
	}
}

static void	find_norm_way_b(t_ps_prms *p, t_dllist *stack, int *way)
{
	t_way	w;

	w.rot = 0;
	w.min = -1;
	while (w.rot < p->len_b)
	{
		way_init(&w, stack, (p->len_b - 1));
		while (w.ptr)
		{
			w.c = (t_content*)w.ptr->content;
			w.bias = w.i - w.c->sort_pos;
			check_bias(&w);
			if (w.bias < 0)
				w.neg += ft_abs(w.bias);
			else
				w.pos += w.bias;
			w.i--;
			w.ptr = w.ptr->right;
		}
		set_way_params(&w, way, p->len_b);
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

void		normalise(t_ps_prms *p, t_cmd_gen *g)
{
	t_normalise	n;

	if (p->stack_a && p->len_a > 1)
	{
		if(!(n.stack_a = copy_linked_stack(&p->stack_a, &n.stack_a)))
			exit (0);
	}
	else
		n.stack_a = NULL;
	if (p->stack_b && p->len_b > 1)
	{
		if(!(n.stack_b = copy_linked_stack(&p->stack_b, &n.stack_b)))
			exit (0);
	}
	else
		n.stack_b = NULL;
	n.way_a = 0;
	n.way_b = 0;
	n.way_ab = 0;
	if (n.stack_a)
		find_norm_way_a(p, n.stack_a, &n.way_a);
	if (n.stack_b)
		find_norm_way_b(p, n.stack_b, &n.way_b);
	get_conclusion(p, &n);
	run_commands(p, g, &n);
}

int			normalise_b(t_ps_prms *p, t_cmd_gen *g, int ret)
{
	t_normalise	n;

	n.stack_a = NULL;
	if (p->stack_b && p->len_b > 1)
	{
		if(!(n.stack_b = copy_linked_stack(&p->stack_b, &n.stack_b)))
			exit (0);
	}
	else
		n.stack_b = NULL;
	n.way_a = 0;
	n.way_b = 0;
	n.way_ab = 0;
	if (n.stack_b)
		find_norm_way_b(p, n.stack_b, &n.way_b);
	if (!ret)
		run_commands(p, g, &n);
	else
	{
		ft_dlldeltoright(&n.stack_b, &linked_stack_free);
		return (n.way_b);
	}
	return (1);
}
