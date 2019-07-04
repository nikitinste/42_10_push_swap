/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_drums.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:48:22 by uhand             #+#    #+#             */
/*   Updated: 2019/07/04 19:55:54 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void drum_way_shortening(t_ps_prms *p, t_drums *d)
{
	//
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
			return (b->rotation);
	}
	return (0);
}

static int	find_b_way(t_ps_prms *p, int val)
{
	t_b_way	b;

	b.rotation = 0;
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

	d.rot = 0;
	d.ptr = p->stack_a;
	while (d.ptr)
	{
		d.content = (t_content*)p->stack_a->content;
		d.val = d.content->val;
		d.cur_b = find_b_way(p, d.val);
		if (d.cur_b > (p->len_b / 2))
			d.cur_b -= p->len_b;
		d.cur_a = d.rot;
		if (d.rot > (p->len_a / 2))
			d.rot -= p->len_a;
		drum_way_shortening(p, &d);
		d.rot++;
		d.ptr = d.ptr->right;
	}
	//-->get_command
}
