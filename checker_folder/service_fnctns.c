/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_fnctns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:55:05 by uhand             #+#    #+#             */
/*   Updated: 2019/06/04 16:57:16 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		error_msg(int prm, t_check_prms *p)
{
	if (prm)
	{
		ft_lstdel(&p->stack_a, &ft_lstfree);
		ft_lstdel(&p->stack_b, &ft_lstfree);
		if (p->command)
			free (p->command);
	}
	ft_putstr_fd("Error\n", 2);
	return (-1);
}

int		check_flags(int argv, char **argc)
{
	if (argv < 2)
		return (0);
	if (!ft_strcmp(argc[1], "-v"))
		return (1);
	return (0);
}

int		checker_init(t_check_prms *p)
{
	p->stack_b = NULL;
	p->command = NULL;
	p->command_arr[0] = &swap_a;
	p->command_arr[1] = &swap_b;
	p->command_arr[2] = &swap_ab;
	p->command_arr[3] = &push_a;
	p->command_arr[4] = &push_b;
	p->command_arr[5] = &rotate_a;
	p->command_arr[6] = &rotate_b;
	p->command_arr[7] = &rotate_ab;
	p->command_arr[8] = &rev_rot_a;
	p->command_arr[9] = &rev_rot_b;
	p->command_arr[10] = &rev_rot_ab;
	p->rule_list[0] = "sa";
	p->rule_list[1] = "sb";
	p->rule_list[2] = "ss";
	p->rule_list[3] = "pa";
	p->rule_list[4] = "pb";
	p->rule_list[5] = "ra";
	p->rule_list[6] = "rb";
	p->rule_list[7] = "rr";
	p->rule_list[8] = "rra";
	p->rule_list[9] = "rrb";
	p->rule_list[10] = "rrr";
	return (window_init(p));
}

int		check_duplicates(t_check_prms *p)
{
	t_list	*ptr;
	t_list	*ptr_2;

	ptr = p->stack_a;
	while (ptr != NULL)
	{
		ptr_2 = p->stack_a;
		while (ptr_2 != NULL)
		{
			if ((int)ptr->content == (int)ptr_2->content && ptr != ptr_2)
			{
				ft_lstdel(&p->stack_a, &ft_lstfree);
				return (0);
			}
			ptr_2 = ptr_2->next;
		}
		ptr = ptr->next;
	}
	return (1);
}

void	rev_rot_ab(t_check_prms *p)
{
	rev_rot_a(p);
	rev_rot_b(p);
}