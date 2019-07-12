/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sequence_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 14:34:28 by uhand             #+#    #+#             */
/*   Updated: 2019/07/12 15:38:31 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void		sort_elems(t_ps_prms *p, t_cmd_gen *g)
{
	int			len;
	t_content	*content;

	len = p->len_a;
	while (len--)
	{
		content = p->stack_a->content;
		if (content->index)
			g->command_arr[4](p, g->rule_list[4]);
		else
		{
			g->command_arr[9](p, g->rule_list[9]);
			if (!normalise_b(p, g))
				exit (0);
		}
	}
}
