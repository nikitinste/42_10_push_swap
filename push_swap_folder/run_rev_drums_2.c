/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_rev_drums_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 18:14:50 by uhand             #+#    #+#             */
/*   Updated: 2019/07/12 17:46:57 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	run_rev_drum_commands(t_ps_prms *p, t_cmd_gen *g, t_drums *d)
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
	g->command_arr[10](p, g->rule_list[10]);
}


void	rev_drums_init(t_drums *d, t_ps_prms *p)
{
	d->rot = 0;
	d->ptr = p->stack_b;
	d->short_way = p->len_a + p->len_b;
	d->a_way = 0;
	d->b_way = 0;
	d->ab_way = 0;
}

void	prepare_stack_a(t_ps_prms *p, t_cmd_gen *g)
{
	t_content	*first;
	t_content	*second;
	t_content	*third;

	while (p->len_a != 3 || p->stack_b)
	{
		g->command_arr[9](p, g->rule_list[9]);
		if (!normalise_b(p, g, 0))
			exit(0);
	}
	first = p->stack_a->content;
	second = p->stack_a->right->content;
	third = p->stack_a->right->right->content;
	if (third->val < second->val && second->val > first->val)
			g->command_arr[1](p, g->rule_list[1]);
	else if (first->val > third->val)
			g->command_arr[4](p, g->rule_list[4]);
	first = p->stack_a->content;
	second = p->stack_a->right->content;
	if (first->val > second->val)
		g->command_arr[7](p, g->rule_list[7]);
}
