/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_drums.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:48:22 by uhand             #+#    #+#             */
/*   Updated: 2019/07/09 17:11:53 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	set_rev_var(t_drums *d)
{
	if ((ft_abs(d->cur_a) + ft_abs(d->cur_b)) > ft_abs(d->cur_a - d->rev_b) && \
		ft_abs(d->cur_a - d->rev_b) <= ft_abs(d->cur_b - d->rev_a))
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

static int	check_place(t_b_way *b, int val)
{
	if (b->val_first > b->val_second)
	{
		if (val < b->val_first && val > b->val_second)
			return (1);
	}
	else
	{
		if (val < b->val_first || val > b->val_second)
			return (1);
	}
	return (0);
}

static int	find_b_way(t_ps_prms *p, int val)
{
	t_b_way	b;

	b.rotation = 1;
	if (!p->stack_b)
		return (0);
	b.ptr = p->stack_b;
	while (b.ptr->right)
	{
		b.content = b.ptr->content;
		b.val_first = b.content->val;
		b.content = b.ptr->right->content;
		b.val_second = b.content->val;
		if (check_place(&b, val))
			return (b.rotation);
		b.rotation++;
		b.ptr = b.ptr->right;
	}
	return (0);
}

void	run_drums(t_ps_prms *p, t_cmd_gen *g)
{
	t_drums	d;

	drums_init(&d, p);
	while (d.ptr)
	{
		d.rev_a = 0;
		d.rev_b = 0;
		d.content = d.ptr->content;
		d.val = d.content->val;
		d.cur_b = find_b_way(p, d.val);
		if (d.cur_b > (p->len_b / 2))
			d.cur_b -= p->len_b;
		d.cur_a = d.rot;
		if (d.cur_a > (p->len_a / 2))
			d.cur_a -= p->len_a;
		drum_way_shortening(p, &d);
		if ((ft_abs(d.cur_a) + ft_abs(d.cur_b) + ft_abs(d.cur_ab)) \
			< d.short_way)
			set_short_way(&d);
		if (d.short_way == d.rot && d.rot <= (p->len_a / 2))
			break ;
		d.rot++;
		d.ptr = d.ptr->right;
	}
	run_drum_commands(p, g, &d);
}
