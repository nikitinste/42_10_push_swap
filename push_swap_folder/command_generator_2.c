/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_generator_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:02:13 by uhand             #+#    #+#             */
/*   Updated: 2019/06/28 16:06:53 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	if (p->len_a >= 3)
	{
		if ((m->c_a->pos - m->c_a->sort_pos) > (p->len_a / 2) + 1)
			return (1);
		if ((m->c_a->pos - m->c_a->sort_pos) >= (p->len_a / 2) + 1 && !p->a)
			return (1);
	}
	return (0);
}

int		rrb_condition(t_ps_prms *p, t_get_cmd *m)
{
	if (p->len_b >= 3)
	{
		if ((m->c_b->pos - m->c_b->sort_pos) * -1 > (p->len_b / 2) + 1)
			return (1);
		if ((m->c_b->pos - m->c_b->sort_pos) * -1 >= (p->len_b / 2) + 1 && !p->b)
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
