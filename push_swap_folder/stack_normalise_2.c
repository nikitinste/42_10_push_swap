/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_normalise_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 15:01:12 by uhand             #+#    #+#             */
/*   Updated: 2019/06/30 21:00:23 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	set_way_params(t_way *w, int *way, int len)
{
		if (w->pos > w->neg)
			w->max = w->pos;
		else
			w->max = w->neg;
		if (w->max < (int)w->min)
		{
			w->min = (unsigned int)w->max;
			*way = w->i;
		}
		if (*way > (len / 2))
			*way = *way - len;
}

void	way_shortening(t_normalise *n)
{
	if (ft_abs(n->way_a - n->rev_b) < ft_abs(n->way_b - n->rev_a))
	{
		if (ft_abs(n->way_a) > ft_abs(n->rev_b))
		{
			n->way_ab = n->rev_b;
			n->way_a -= n->rev_b;
			n->way_b = 0;
			return ;
		}
		n->way_ab = n->way_a;
		n->way_b = n->rev_b - n->way_a;
		n->way_a = 0;
		return ;
	}
		if (ft_abs(n->way_b) > ft_abs(n->rev_a))
		{
			n->way_ab = n->rev_a;
			n->way_b -= n->rev_a;
			n->way_a = 0;
			return ;
		}
		n->way_ab = n->way_b;
		n->way_a = n->rev_a - n->way_b;
		n->way_b = 0;
}

void 		linked_stack_free(void *content, size_t size)
{
	if (content && size)
		return ;
	return ;
}

static void	execute_command(t_ps_prms *p, t_cmd_gen *g, t_execute *cmd, int way)
{
	while (cmd->i)
	{
		if (way > 0)
			g->command_arr[cmd->command](p, g->rule_list[cmd->command]);
		else
			g->command_arr[cmd->command - 3](p, g->rule_list[cmd->command - 3]);
		cmd->i--;
	}
}

void	run_commands(t_ps_prms *p, t_cmd_gen *g, t_normalise *n)
{
	t_execute	cmd;

	cmd.i = ft_abs(n->way_ab);
	cmd.command = 3;
	execute_command(p, g, &cmd, n->way_ab);
	cmd.i = ft_abs(n->way_a);
	cmd.command = 4;
	execute_command(p, g, &cmd, n->way_a);
	cmd.i = ft_abs(n->way_b);
	cmd.command = 5;
	execute_command(p, g, &cmd, n->way_b);
	ft_dlldeltoright(&n->stack_a, &linked_stack_free);
	ft_dlldeltoright(&n->stack_b, &linked_stack_free);
}
