/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_rev_drums.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 18:10:44 by uhand             #+#    #+#             */
/*   Updated: 2019/07/12 14:53:23 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	set_rev_var(t_drums *d)
{
	if ((ft_abs(d->cur_a) + ft_abs(d->cur_b)) > ft_abs(d->cur_a - d->rev_b) && \
		ft_abs(d->cur_a - d->rev_b) <= ft_abs(d->rev_a - d->cur_b))
		set_drums_way(d, d->cur_a, d->rev_b);
	else
		set_drums_way(d, d->rev_a, d->cur_b);
}

static void drum_way_shortening(t_ps_prms *p, t_drums *d)
{
	d->cur_ab = 0;
	if ((d->cur_a >= 0 && d->cur_b >= 0) || (d->cur_a <= 0 && d->cur_b <= 0))
	{
		set_drums_way(d, d->cur_a, d->cur_b);
		return ;
	}
	d->rev_a = d->cur_a - p->len_a;
	d->rev_b = d->cur_b - p->len_b;
	if ((ft_abs(d->cur_a) + ft_abs(d->cur_b)) > ft_abs(d->cur_a - d->rev_b) || \
		(ft_abs(d->cur_a) + ft_abs(d->cur_b)) > ft_abs(d->rev_a - d->cur_b))
		set_rev_var(d);
}

static int	check_a_place(t_b_way *a, int val)
{
	if (a->val_first < a->val_second)
	{
		if (val > a->val_first && val < a->val_second)
			return (1);
	}
	else
	{
		if (val > a->val_first || val < a->val_second)
			return (1);
	}
	return (0);
}

static int	find_a_way(t_ps_prms *p, int val)
{
	t_b_way	a;

	a.rotation = 1;
	if (!p->stack_a)
		return (0);
	a.ptr = p->stack_a;
	while (a.ptr->right)
	{
		a.content = a.ptr->content;
		a.val_first = a.content->val;
		a.content = a.ptr->right->content;
		a.val_second = a.content->val;
		if (check_a_place(&a, val))
			return (a.rotation);
		a.rotation++;
		a.ptr = a.ptr->right;
	}
	return (0);
}


void	run_rev_drums(t_ps_prms *p, t_cmd_gen *g)
{
	t_drums	d;

	rev_drums_init(&d, p);
	while (d.ptr)
	{
		d.rev_a = 0;
		d.rev_b = 0;
		d.content = d.ptr->content;
		d.val = d.content->val;
		d.cur_a = find_a_way(p, d.val);
		if (d.cur_a > (p->len_a / 2))
			d.cur_a -= p->len_a;
		d.cur_b = d.rot;
		if (d.cur_b > (p->len_b / 2))
			d.cur_b -= p->len_b;
		drum_way_shortening(p, &d);
		if ((ft_abs(d.cur_a) + ft_abs(d.cur_b) + ft_abs(d.cur_ab)) \
			< d.short_way)
			set_short_way(&d);
		/*if (d.short_way == d.rot && d.rot <= (p->len_b / 2))
			break ;*/
		d.rot++;
		d.ptr = d.ptr->right;
	}
	run_rev_drum_commands(p, g, &d);
}
