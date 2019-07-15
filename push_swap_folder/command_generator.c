/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_generator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:58:30 by uhand             #+#    #+#             */
/*   Updated: 2019/07/15 14:01:45 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_command_4(t_ps_prms *p, t_get_cmd *m)
{
	if (p->len_b >= 2 && m->c_b->val < m->c_br->val)
		return (m->cmd);
	m->cmd++;
	if (!p->push_direction && p->stack_a)
		return (m->cmd);
	if ((p->push_direction && !p->stack_b))
	{
		p->push_direction = 0;
		return (m->cmd);
	}
	m->cmd++;
	if (!p->push_direction && !p->stack_a)
		p->push_direction = 1;
	return (m->cmd);
}

static int	get_command_3(t_ps_prms *p, t_get_cmd *m)
{
	if (ra_condition(p, m) && !p->norm)
	{
		return (m->cmd);
		p->norm = 0;
	}
	m->cmd++;
	if (rb_condition(p, m) && !p->norm)
	{
		return (m->cmd);
		p->norm = 0;
	}
	m->cmd++;
	if (p->stack_a && p->stack_a->right)
		m->c_ar = p->stack_a->right->content;
	if (p->stack_b && p->stack_b->right)
		m->c_br = p->stack_b->right->content;
	if (p->len_a >= 2 && p->len_b >= 2 && m->c_a->val > m->c_ar->val \
		&& m->c_b->val < m->c_br->val)
		return (m->cmd);
	m->cmd++;
	if (p->len_a >= 2 && m->c_a->val > m->c_ar->val)
		return (m->cmd);
	m->cmd++;
	return (get_command_4(p, m));
}

static int	get_command_2(t_ps_prms *p, t_get_cmd *m)
{
	if (rra_condition(p, m) && !p->norm)
	{
		return (m->cmd);
		p->norm = 0;
	}
	m->cmd++;
	if (rrb_condition(p, m) && !p->norm)
	{
		return (m->cmd);
		p->norm = 0;
	}
	m->cmd++;
	if (p->stack_a)
		m->c_a = p->stack_a->content;
	if (p->stack_b)
		m->c_b = p->stack_b->content;
	if (rr_condition(p, m) && !p->norm)
	{
		return (m->cmd);
		p->norm = 0;
	}
	m->cmd++;
	return (get_command_3(p, m));
}

static int	get_command(t_ps_prms *p)
{
	t_get_cmd	m;

	p->check = 0;
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
	if (rrr_condition(p, &m) && !p->norm)
	{
		return (m.cmd);
		p->norm = 0;
	}
	m.cmd++;
	return (get_command_2(p, &m));
}

void		rotor(t_ps_prms *p)
{
	t_cmd_gen	g;
	int			command;

	commands_init(p, &g);
	p->cmd_count = 0;
	while (!check_sort_state(p, 1, 1))
	{
		if ((!p->push_direction && check_sort_state(p, 1, 0)) || \
			(p->push_direction && check_sort_state(p, 0, 1)))
		{
			if (!p->push_direction)
				p->push_direction = 1;
			else
				p->push_direction = 0;
		}
		normalise(p, &g);
		if (p->check)
			continue ;
		command = get_command(p);
		g.command_arr[command](p, g.rule_list[command]);
	}
	while (p->stack_b)
		g.command_arr[10](p, g.rule_list[10]);
}
