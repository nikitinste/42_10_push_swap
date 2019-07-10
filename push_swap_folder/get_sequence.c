/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sequence.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 14:57:27 by uhand             #+#    #+#             */
/*   Updated: 2019/07/10 20:28:42 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	mark_sorted_el(t_ps_prms *p)
{
	t_marc_el	mrk;

	mrk.ptr = p->stack_a;
	mrk.max_ptr = p->stack_a;
	if (!mrk.ptr)
		return;
	mrk.ind = 0;
	while (mrk.ptr->right)
	{
		mrk.content = mrk.ptr->content;
		if (mrk.content->index > mrk.ind)
		{
			mrk.ind = mrk.content->index;
			mrk.max_ptr = mrk.ptr;
		}
		mrk.ptr = mrk.ptr->right;
	}
	mrk.content = mrk.max_ptr->content;
	mrk.ind = mrk.content->index;
	mrk.content->index = 1;
	mrk.max_ptr = mrk.max_ptr->left;
	while (mrk.max_ptr->left)
	{
		mrk.content = mrk.max_ptr->content;
		if (mrk.content->index != (mrk.ind - 1))
			mrk.content->index = 0;
		else
		{
			mrk.ind = mrk.content->index;
			mrk.content->index = 1;
		}
		mrk.max_ptr = mrk.max_ptr->left;
	}
	// ^^^ - contraction needed
}

static int	check_val(t_list *ptr, t_lstcontent *content, int val)
{
	content = ptr->content;
	if (val < content->val)
	{
		content->val = val;
		return (1);
	}
	ptr = ptr->next;
		return (0);
}

static int	find_index(t_list *list, int val)
{
	t_find_index	fi;

	fi.lc.val = val;
	if (!list)
	{
		fi.lc.index = 0;
		if (!ft_lstaddnext(&list, &fi.lc, sizeof(t_lstcontent)))
			exit (0);
		return (0);
	}
	fi.ptr = list;
	while (fi.ptr->next)
		if (check_val(fi.ptr, fi.content, val))
			return(fi.content->index);
	fi.lc.index = fi.content->index + 1;
	if (check_val(fi.ptr, fi.content, val))
		return(fi.content->index);
	if (!ft_lstaddnext(&list, &fi.lc, sizeof(t_lstcontent)))
		exit (0);
	return (fi.lc.index);
}

static int	find_max_seq(t_ps_prms *p, t_dllist	*elem)
{
	t_max_seq		msq;

	msq.list = NULL;
	msq.ptr = elem;
	msq.content = msq.ptr->content;
	msq.content->index = find_index(msq.list, msq.content->val);
	msq.max_len = msq.content->index;
	msq.ptr = elem->right;
	if (!msq.ptr)
		msq.ptr = p->stack_a;
	while (msq.ptr != elem)
	{
		msq.content = msq.ptr->content;
		msq.content->index = find_index(msq.list, msq.content->val);
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
	t_execute		cmd;

	sq.ptr = p->stack_a;
	sq.rot = 0;
	sq.max = 0;
	while (sq.ptr)
	{
		sq.seq = find_max_seq(p, sq.ptr);
		if (sq.seq > sq.max)
		{
			sq.max = sq.seq;
			sq.rot_max = sq.rot;
		}
		sq.ptr = sq.ptr->right;
	}
	if (sq.rot_max > (p->len_a / 2))
		sq.rot_max -= p->len_a;
cmd.i = ft_abs(sq.rot_max);
cmd.command = 4;
execute_command(p, g, &cmd, sq.rot_max);
find_max_seq(p, p->stack_a);
mark_sorted_el(p);
}
