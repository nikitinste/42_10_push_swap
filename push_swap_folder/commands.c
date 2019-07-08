/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 17:03:46 by uhand             #+#    #+#             */
/*   Updated: 2019/07/08 18:50:03 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	commands_init(t_ps_prms *p, t_cmd_gen *g)
{
	g->command_arr[0] = &rev_rot_ab;
	g->command_arr[3] = &rotate_ab;
	g->command_arr[1] = &rev_rot_a;
	g->command_arr[2] = &rev_rot_b;
	g->command_arr[4] = &rotate_a;
	g->command_arr[5] = &rotate_b;
	g->command_arr[6] = &swap_ab;
	g->command_arr[7] = &swap_a;
	g->command_arr[8] = &swap_b;
	g->command_arr[9] = &push_b;
	g->command_arr[10] = &push_a;
	g->rule_list[0] = "rrr";
	g->rule_list[3] = "rr";
	g->rule_list[1] = "rra";
	g->rule_list[2] = "rrb";
	g->rule_list[4] = "ra";
	g->rule_list[5] = "rb";
	g->rule_list[6] = "ss";
	g->rule_list[7] = "sa";
	g->rule_list[8] = "sb";
	g->rule_list[9] = "pb";
	g->rule_list[10] = "pa";
	p->push_direction = 0;
	p->check = 0;
	p->norm = 0;
}

void	rev_rot_ab(t_ps_prms *p, char *command)
{
	rev_rot_a(p, NULL);
	rev_rot_b(p, NULL);
	if (command)
		ft_printf("%s\n", command);
}

void	rotate_ab(t_ps_prms *p, char *command)
{
	rotate_a(p, NULL);
	rotate_b(p, NULL);
	if (command)
		ft_printf("%s\n", command);
}

void	rev_rot_a(t_ps_prms *p, char *command)
{
	t_dllist	*last;

	if (!p->stack_a || !p->stack_a->right)
		return ;
	last = p->stack_a;
	while (last->right)
		last = last->right;
	last->left->right = NULL;
	last->left = NULL;
	last->right = p->stack_a;
	p->stack_a->left = last;
	p->stack_a = last;
	reset_position_a(p);
	if (command)
		ft_printf("%s\n", command);
}

void	rev_rot_b(t_ps_prms *p, char *command)
{
	t_dllist	*last;

	if (!p->stack_b || !p->stack_b->right)
		return ;
	last = p->stack_b;
	while (last->right)
		last = last->right;
	last->left->right = NULL;
	last->left = NULL;
	last->right = p->stack_b;
	p->stack_b->left = last;
	p->stack_b = last;
	reset_position_b(p);
	if (command)
		ft_printf("%s\n", command);
}
