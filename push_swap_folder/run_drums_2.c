/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_drums_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 16:00:55 by uhand             #+#    #+#             */
/*   Updated: 2019/07/08 15:16:59 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	set_drums_way(t_drums *d, int way_a, int way_b)
{
	if (ft_abs(way_a) > ft_abs(way_b))
	{
		d->cur_ab = way_b;
		d->cur_a = way_a - way_b;
		d->cur_b = 0;
	}
	else
	{
		d->cur_ab = way_a;
		d->cur_b = way_b - way_a;
		d->cur_a = 0;
	}
}

void	set_short_way(t_drums *d)
{
	d->a_way = d->cur_a;
	d->b_way = d->cur_b;
	d->ab_way = d->cur_ab;
	d->short_way = ft_abs(d->cur_a) + ft_abs(d->cur_b) + ft_abs(d->cur_ab);
}

void	run_drum_commands(t_ps_prms *p, t_cmd_gen *g, t_drums *d)
{
	t_execute	cmd;

	cmd.i = ft_abs(d->ab_way);
	cmd.command = 3;
	execute_command(p, g, &cmd, d->ab_way);
	cmd.i = ft_abs(d->a_way);
	cmd.command = 4;
	execute_command(p, g, &cmd, d->a_way);
	cmd.i = ft_abs(d->b_way);
	cmd.command = 5;
	execute_command(p, g, &cmd, d->b_way);
	g->command_arr[9](p, g->rule_list[9]);
}

void	drums_init(t_drums *d, t_ps_prms *p)
{
	d->rot = 0;
	d->ptr = p->stack_a;
	d->short_way = p->len_a + p->len_b;
	d->a_way = 0;
	d->b_way = 0;
	d->ab_way = 0;
}
