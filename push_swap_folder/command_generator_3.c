/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_generator_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:37:09 by uhand             #+#    #+#             */
/*   Updated: 2019/06/29 17:59:42 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*int		check_neg_bias(t_dllist *stack, int len)
{
	t_dllist	*ptr;
	t_content	*c;
	int			bias;

	ptr = stack;
	while (ptr)
	{
		c = ptr->content;
		bias = c->pos - c->sort_pos;
		if (!(bias * -1 > (len / 2) && bias < len))
			return (1);
		ptr = ptr->right;
	}
	return (0);
}*/

int		check_condition(t_ps_prms *p, t_get_cmd *m)
{
	t_content	*content;

	if (!p->push_direction && p->len_a > 1 && !check_sort_state(p, 1, 0))
	{
		content = p->stack_a->content;
		if ((content->pos - content->sort_pos) == 0)
		{
			m->cmd = 9;
			return (1);
		}
	}
	if (p->push_direction && p->len_b > 1 && !check_sort_state(p, 0, 1))
	{
		content = p->stack_a->content;
		if ((content->pos - content->sort_pos) == 0)
		{
			m->cmd = 10;
			return (1);
		}
	}
	return (0);
}

int		ra_condition(t_ps_prms *p, t_get_cmd *m)
{
	int		bias;

	bias = m->c_a->pos - m->c_a->sort_pos;
	if (p->len_a >= 3)
	{
		if (bias * -1 > (p->len_a / 2) && bias * -1 < p->len_a)
			return (1);
		// if (bias * -1 >= (p->len_a / 2) && !p->a)
		// 	return (1);
	}
	return (0);
}

int		rb_condition(t_ps_prms *p, t_get_cmd *m)
{
	int		bias;

	bias = m->c_b->pos - m->c_b->sort_pos;
	if (p->len_b >= 3)
	{
		if (bias > (p->len_b / 2) && bias < p->len_b)
			return (1);
		// if (bias >= (p->len_b / 2) && !p->b)
		// 	return (1);
	}
	return (0);
}

int		rr_condition(t_ps_prms *p, t_get_cmd *m)
{
	if (p->len_a >= 3 && p->len_b >= 3)
		if (ra_condition(p, m) && rb_condition(p, m))
			return (1);
	return (0);
}
