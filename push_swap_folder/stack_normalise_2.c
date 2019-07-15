/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_normalise_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 15:01:12 by uhand             #+#    #+#             */
/*   Updated: 2019/07/15 14:32:16 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_dllist **stack)
{
	t_dllist	*last;
	t_dllist	*tmp;

	if (stack[0]->right)
		if (!stack[0]->right->right)
		{
			norm_swap(stack);
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

void	set_way_params(t_way *w, int *way, int len)
{
	int		rot;

	check_direction(w, len);
	if (w->pos > w->neg)
		w->max = w->pos;
	else
		w->max = w->neg;
	if ((unsigned int)w->max <= w->min)
	{
		if ((unsigned int)w->max < w->min)
		{
			w->min = (unsigned int)w->max;
			*way = w->rot;
		}
		else
		{
			rot = w->rot;
			if (rot > (len / 2))
				rot -= len;
			if (ft_abs(rot) < ft_abs(*way))
				*way = w->rot;
		}
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

void		execute_command(t_ps_prms *p, t_cmd_gen *g, t_execute *cmd, int way)
{
	while (cmd->i)
	{
		if (way > 0)
			g->command_arr[cmd->command](p, g->rule_list[cmd->command]);
		else
			g->command_arr[cmd->command - 3](p, g->rule_list[cmd->command - 3]);
		cmd->i--;

		if (!p->norm)
			p->norm = 1;
		if (!p->check)
			p->check = 1;
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
