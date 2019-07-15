/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_generator_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:02:13 by uhand             #+#    #+#             */
/*   Updated: 2019/07/15 13:49:48 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			check_sort_state(t_ps_prms *p, int a, int b)
{
	t_dllist	*ptr;
	t_content	*content;

	if (p->check)
		p->check = 0;
	ptr = p->stack_a;
	if (!ptr)
		return (0);
	while (ptr && a)
	{
		content = ptr->content;
		if ((content->pos - content->sort_pos) != 0)
			return (0);
		ptr = ptr->right;
	}
	ptr = p->stack_b;
	while (ptr && b)
	{
		content = ptr->content;
		if ((content->pos - content->sort_pos) != 0)
			return (0);
		ptr = ptr->right;
	}
	return (1);
}

int		rra_condition(t_ps_prms *p, t_get_cmd *m)
{
	int		bias;

	if (p->len_a >= 3)
	{
		bias = m->c_a->pos - m->c_a->sort_pos;
		if (bias > (p->len_a / 2) && bias < p->len_a)
			return (1);
	}
	return (0);
}

int		rrb_condition(t_ps_prms *p, t_get_cmd *m)
{
	int		bias;

	if (p->len_b >= 3)
	{
		bias = m->c_b->pos - m->c_b->sort_pos;
		if (bias * -1 > (p->len_b / 2) && bias * -1 < p->len_b)
			return (1);
	}
	return (0);
}

int		rrr_condition(t_ps_prms *p, t_get_cmd *m)
{
	if (p->len_a >= 3 && p->len_b >= 3)
		if (rra_condition(p, m) && rrb_condition(p, m))
			return (1);
	return (0);
}
