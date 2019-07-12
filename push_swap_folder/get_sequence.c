/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sequence.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 14:57:27 by uhand             #+#    #+#             */
/*   Updated: 2019/07/12 18:55:17 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	mark_sorted_el(t_ps_prms *p)
{
	t_marc_el	mrk;

	find_max_index(p, &mrk);
	mrk.content = mrk.max_ptr->content;
	mrk.ind = mrk.content->index;
	mrk.content->index = 1;
	mrk.ptr = mrk.max_ptr->left;
	if (!mrk.ptr)
		mrk.ptr = find_last(p);
	while (mrk.ptr != mrk.max_ptr)
	{
		mrk.content = mrk.ptr->content;
		if (mrk.content->index != (mrk.ind - 1))
			mrk.content->index = 0;
		else
		{
			mrk.ind = mrk.content->index;
			mrk.content->index = 1;
		}
		mrk.ptr = mrk.ptr->left;
		if (!mrk.ptr)
			mrk.ptr = find_last(p);
	}
}

static int	check_val(t_list **ptr, t_lstcontent *content, int val)
{
	content = ptr[0]->content;
	if (val < content->val)
	{
		content->val = val;
		return (1);
	}
		return (0);
}

static int	find_index(t_list **list, int val)
{
	t_find_index	fi;

	fi.lc.val = val;
	if (!list[0])
	{
		fi.lc.index = 0;
		if (!ft_lstaddnext(list, &fi.lc, sizeof(t_lstcontent)))
			exit (0);
		return (0);
	}
	fi.ptr = *list;
	while (fi.ptr)
	{
		fi.content = fi.ptr->content;
		if (check_val(&fi.ptr, fi.content, val))
			return(fi.content->index);
		if (fi.ptr->next)
			fi.ptr = fi.ptr->next;
		else
			break ;
	}
	fi.lc.index = fi.content->index + 1;
	if (!ft_lstaddnext(list, &fi.lc, sizeof(t_lstcontent)))
		exit (0);
	return (fi.lc.index);
}

static int	find_max_seq(t_ps_prms *p, t_dllist *elem)
{
	t_max_seq		msq;

	msq.list = NULL;
	msq.ptr = elem;
	msq.content = msq.ptr->content;
	msq.content->index = find_index(&msq.list, msq.content->val);
	msq.max_len = msq.content->index;
	msq.ptr = elem->right;
	if (!msq.ptr)
		msq.ptr = p->stack_a;
	while (msq.ptr != elem)
	{
		msq.content = msq.ptr->content;
		msq.content->index = find_index(&msq.list, msq.content->val);
		if (msq.content->index > msq.max_len)
			msq.max_len = msq.content->index;
		msq.ptr = msq.ptr->right;
		if (!msq.ptr)
			msq.ptr = p->stack_a;
	}
	ft_lstdel(&msq.list, &ft_lstfree);
	return (msq.max_len);
}

void		get_sequence(t_ps_prms *p, t_cmd_gen *g)
{
	t_sequence		sq;

	sq.ptr = p->stack_a;
	sq.max = 0;
	while (sq.ptr)
	{
		sq.seq = find_max_seq(p, sq.ptr);
		if (sq.seq > sq.max)
		{
			sq.max = sq.seq;
			sq.ptr_max = sq.ptr;
		}
		sq.ptr = sq.ptr->right;
	}
	if (sq.max == (p->len_a - 1))
		return ;
	find_max_seq(p, sq.ptr_max);
	mark_sorted_el(p);
	sort_elems(p, g);
}
