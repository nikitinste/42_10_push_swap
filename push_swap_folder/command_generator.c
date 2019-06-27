/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_generator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:58:30 by uhand             #+#    #+#             */
/*   Updated: 2019/06/27 18:12:49 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*static int is_sorted(t_ps_prms *p, int stack)
{
	t_dllist	*ptr;
	t_content	*first;
	t_content	*second;

	if (!stack)
		ptr = p->stack_a;
	else
		ptr = p->stack_b;
	if (!stack)
	{
		while (ptr && ptr->right)
		{
			first = (t_content*)ptr->content;
			second = (t_content*)ptr->right->content;
			if (first->val < second->val)
				return (0);
			ptr = ptr->right;
		}
	}
	else
	{
		while (ptr && ptr->right)
		{
			first = (t_content*)ptr->content;
			second = (t_content*)ptr->right->content;
			if (first->val > second->val)
				return (0);
			ptr = ptr->right;
		}
	}
	return (1);
}*/

static int	check_sort_state(t_ps_prms *p)
{
	t_dllist	*ptr;
	t_content	*content;

	ptr = p->stack_a;
	if (!ptr)
		return (0);
	while (ptr)
	{
		content = ptr->content;
		if ((content->pos - content->sort_pos) != 0)
			return (0);
		ptr = ptr->right;
	}
	ptr = p->stack_b;
	while (ptr)
	{
		content = ptr->content;
		if ((content->pos - content->sort_pos) != 0)
			return (0);
		ptr = ptr->right;
	}
	return (1);
}

static int	get_command_3(t_ps_prms *p, t_get_cmd *m)
{
	if (p->len_a >= 2 && m->c_a->val > m->c_ar->val)
		return (m->cmd);// [7] - sa
	m->cmd++;
	if (p->len_b >= 2 && m->c_b->val < m->c_br->val)
		return (m->cmd);// [8] - sb
	m->cmd++;
	if (!p->push_direction && p->stack_a/* && !is_sorted(p, 0)*/)
		return (m->cmd);// [9] - pb
	if ((p->push_direction && !p->stack_b)/* || (p->push_direction && is_sorted(p, 1))*/)
	{
		p->push_direction = 0;
		return (m->cmd);// [9] - pb
	}
	m->cmd++;
	if (!p->push_direction && !p->stack_a)
		p->push_direction = 1;
	return (m->cmd);// [10] - pa
}

static int	get_command_2(t_ps_prms *p, t_get_cmd *m)
{
	if (p->stack_a)
		m->c_a = p->stack_a->content;
	if (p->stack_b)
		m->c_b = p->stack_b->content;
	if (p->len_a >= 2 && p->len_b >= 2 && \
		(m->c_a->pos - m->c_a->sort_pos) * -1 > (p->len_a / 2) && \
			(m->c_b->pos - m->c_b->sort_pos) > (p->len_b / 2))
		return (m->cmd);// [3] - rr
	m->cmd++;
	if (p->len_a >= 2 && \
		(m->c_a->pos - m->c_a->sort_pos) * -1 > (p->len_a / 2))
		return (m->cmd);// [4] - ra
	m->cmd++;
	if (p->len_b >= 2 && (m->c_b->pos - m->c_b->sort_pos) > (p->len_b / 2))
		return (m->cmd);// [5] - rb
	m->cmd++;
	if (p->stack_a && p->stack_a->right)
		m->c_ar = p->stack_a->right->content;
	if (p->stack_b && p->stack_b->right)
		m->c_br = p->stack_b->right->content;
	if (p->len_a >= 2 && p->len_b >= 2 && m->c_a->val > m->c_ar->val \
		&& m->c_b->val < m->c_br->val)
		return (m->cmd);// [6] - ss
	m->cmd++;
	return (get_command_3(p, m));
}

static int	get_command(t_ps_prms *p)
{
	t_get_cmd	m;

	m.cmd = 0;
	m.last_a = p->stack_a;
	m.last_b = p->stack_b;
	while (m.last_a && m.last_a->right)
		m.last_a = m.last_a->right;
	while (m.last_b && m.last_b->right)
		m.last_b = m.last_b->right;
	if (m.last_a)
		m.c_a = m.last_a->content;
	if (m.last_b)
		m.c_b = m.last_b->content;
	if (p->len_a >= 2 && p->len_b >= 2 && (m.c_a->pos - m.c_a->sort_pos) > \
		(p->len_a / 2) && (m.c_b->pos - m.c_b->sort_pos) * -1 > (p->len_b / 2))
		return (m.cmd);// [0] - rrr
	m.cmd++;
	if (p->len_a >= 2 && (m.c_a->pos - m.c_a->sort_pos) > (p->len_a / 2))
		return (m.cmd);// [1] - rra
	m.cmd++;
	if (p->len_b >= 2 && (m.c_b->pos - m.c_b->sort_pos) * -1 > (p->len_b / 2))
		return (m.cmd);// [2] - rrb
	m.cmd++;
	return (get_command_2(p, &m));
}

void		command_generator(t_ps_prms *p)
{
	t_cmd_gen	g;
	int			command;
	//int			i;
	t_dllist	*ptr;
	//t_content	*c;

	commands_init(&g);
	p->push_direction = 0;
	//i = -1;
	while (!check_sort_state(p))
	{
		//ft_printf("%d: ", ++i);
		command = get_command(p);
		g.command_arr[command](p, g.rule_list[command]);
		ptr = p->stack_a;
		/*while (ptr)
		{
			c = (t_content*)ptr->content;
			ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
				c->pos - c->sort_pos);
			ptr = ptr->right;
		}
		ft_printf("\n");
		ptr = p->stack_b;
		while (ptr)
		{
			c = (t_content*)ptr->content;
			ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
				c->pos - c->sort_pos);
			ptr = ptr->right;
		}
		ft_printf("\n");*/
	}
	while (p->stack_b)
	{
		//ft_printf("%d: ", ++i);
		g.command_arr[10](p, g.rule_list[10]);
		/*ptr = p->stack_a;
		while (ptr)
		{
			c = (t_content*)ptr->content;
			ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
				c->pos - c->sort_pos);
			ptr = ptr->right;
		}
		ft_printf("\n");
		ptr = p->stack_b;
		while (ptr)
		{
			c = (t_content*)ptr->content;
			ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
				c->pos - c->sort_pos);
			ptr = ptr->right;
		}
		ft_printf("\n");*/
	}
}
