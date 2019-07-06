/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_normalise_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 15:01:12 by uhand             #+#    #+#             */
/*   Updated: 2019/07/06 21:31:10 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	//ft_printf("%d ", w->max);//<--
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

void		execute_command(t_ps_prms *p, t_cmd_gen *g, t_execute *cmd, int way)
{
	//t_dllist	*ptr;
	//t_content	*c;
	//int			lala = 0;//<--

	/*if (cmd->i > 0)
	{
		ft_printf("norm commands:\n");
		lala = 1;
	}*///<--
	while (cmd->i)
	{
		if (p->len_b == 3 && check_stack_is_sorted(p->stack_b))
			return ;
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
	/*if(lala)
	{
		ptr = p->stack_a;
		ft_printf("norm len_a: %d\n", p->len_a);
		while (ptr)
		{
			c = (t_content*)ptr->content;
			ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
				c->pos - c->sort_pos);
			ptr = ptr->right;
		}
		ft_printf("\n\n");
		ptr = p->stack_b;
		ft_printf("norm len_b: %d\n", p->len_b);
		while (ptr)
		{
			c = (t_content*)ptr->content;
			ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
				c->pos - c->sort_pos);
			ptr = ptr->right;
		}
		ft_printf("\n");
	}*///<--
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
