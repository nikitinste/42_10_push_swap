/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_generator_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:02:13 by uhand             #+#    #+#             */
/*   Updated: 2019/06/28 23:34:23 by stepa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*int		check_pos_bias(t_dllist *stack, int len)
{
	t_dllist	*ptr;
	t_content	*c;
	int			bias;

	ptr = stack;
	while (ptr)
	{
		c = ptr->content;
		bias = c->pos - c->sort_pos;
		if (!(bias > (len / 2) && bias < len))
			return (1);
		ptr = ptr->right;
	}
	return (0);
}*/

void	set_even_odd(t_ps_prms *p)
{
	if ((p->len_a / 2) * 2 != p->len_a)
		p->a = 1;
	else
		p->a = 0;
	if ((p->len_b / 2) * 2 != p->len_b)
		p->b = 1;
	else
		p->b = 0;
}

int		rra_condition(t_ps_prms *p, t_get_cmd *m)
{
	int		bias;

	bias = m->c_a->pos - m->c_a->sort_pos;
	if (p->len_a >= 3)
	{
		if (bias > (p->len_a / 2) && bias < p->len_a)
			return (1);
		// if ((m->c_a->pos - m->c_a->sort_pos) >= (p->len_a / 2) && !p->a)
		// 	return (1);
	}
	return (0);
}

int		rrb_condition(t_ps_prms *p, t_get_cmd *m)
{
	int		bias;

	bias = m->c_b->pos - m->c_b->sort_pos;
	if (p->len_b >= 3)
	{
		if (bias * -1 > (p->len_b / 2) && bias * -1 < p->len_b)
			return (1);
		// if (bias * -1 >= (p->len_b / 2) && !p->b)
		// 	return (1);
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
