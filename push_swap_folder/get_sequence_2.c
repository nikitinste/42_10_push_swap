/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sequence_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 14:34:28 by uhand             #+#    #+#             */
/*   Updated: 2019/07/12 17:47:22 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	norm_b_rotation(t_ps_prms *p, t_cmd_gen *g, int *way)
{
	if (way[0] < 0)
	{
		while (way[0] < 0)
		{
			g->command_arr[2](p, g->rule_list[2]);
			*way = *way + 1;
		}
	}
	else
	{
		while (way[0] > 0)
		{
			g->command_arr[5](p, g->rule_list[5]);
			*way = *way - 1;
		}
	}
}

t_dllist	*find_last(t_ps_prms *p)
{
	t_dllist	*ptr;

	ptr = p->stack_a;
	while (ptr->right)
		ptr = ptr->right;
	return (ptr);
}

void		find_max_index(t_ps_prms *p, t_marc_el *mrk)
{
	mrk->ptr = p->stack_a;
	mrk->max_ptr = p->stack_a;
	if (!mrk->ptr)
		return;
	mrk->ind = 0;
	while (mrk->ptr->right)
	{
		mrk->content = mrk->ptr->content;
		if (mrk->content->index > mrk->ind)
		{
			mrk->ind = mrk->content->index;
			mrk->max_ptr = mrk->ptr;
		}
		mrk->ptr = mrk->ptr->right;
	}
}

static void check_norm_condition(t_ps_prms *p, t_cmd_gen *g, int *way)
{
		if (*way > 0)
		{
			g->command_arr[3](p, g->rule_list[3]);
			*way = *way - 1;
		}
		else
			g->command_arr[4](p, g->rule_list[4]);
}

void		sort_elems(t_ps_prms *p, t_cmd_gen *g)
{
	int			len;
	int			b_norm_way;
	t_content	*content;

	len = p->len_a;
	b_norm_way = 0;
	while (len--)
	{
		content = p->stack_a->content;
		if (content->index)
			check_norm_condition(p, g, &b_norm_way);
		else
		{
			if (b_norm_way != 0)
				norm_b_rotation(p, g, &b_norm_way);
			g->command_arr[9](p, g->rule_list[9]);
			b_norm_way = normalise_b(p, g, 1);
			if (b_norm_way < 0)
				norm_b_rotation(p, g, &b_norm_way);
		}
	}
}
