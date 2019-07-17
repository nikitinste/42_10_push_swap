/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:56:30 by uhand             #+#    #+#             */
/*   Updated: 2019/07/17 15:59:33 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		check_duplicates(t_ps_prms *p)
{
	t_dllist	*ptr;
	t_dllist	*ptr_2;

	ptr = p->stack_a;
	while (ptr != NULL)
	{
		ptr_2 = p->stack_a;
		while (ptr_2 != NULL)
		{
			if (*((int*)ptr->content) == *((int*)ptr_2->content) \
				&& ptr != ptr_2)
			{
				ft_dlldel(&p->stack_a, &ft_lstfree);
				return (0);
			}
			ptr_2 = ptr_2->right;
		}
		ptr = ptr->right;
	}
	p->mode = 1;
	return (1);
}

static int	set_args(char ***args, t_ps_prms *p)
{
	t_content	c;
	long long	buf;

	p->len_a = 0;
	p->len_b = 0;
	while (args[0][p->len_a] != NULL)
		p->len_a++;
	c.sort_pos = 0;
	c.pos = -1;
	while (++c.pos < p->len_a)
	{
		buf = ps_atoi(args[0][c.pos]);
		c.val = (int)buf;
		c.index = 0;
		free(args[0][c.pos]);
		if (buf != (long long)c.val || \
			ft_dlladdnextr(&p->stack_a, (void*)&c, sizeof(t_content)) == -1)
		{
			ft_dlldel(&p->stack_a, &ft_lstfree);
			while (++c.pos < p->len_a)
				free(args[0][c.pos]);
			return (0);
		}
	}
	return (1);
}

static int	check_n_put_args(int argc, char **argv, char ***args, \
	t_ps_prms *p)
{
	int			i;
	int			j;
	char		*buf_str;

	i = p->flag;
	p->stack_a = NULL;
	p->stack_b = NULL;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j] != '\0')
		{
			if (!ft_isdigit((int)argv[i][j]) && !ft_isspace((int)argv[i][j]))
				if (!((argv[i][j] == '+' || argv[i][j] == '-') && \
					ft_isdigit((int)argv[i][j + 1])))
					return (0);
		}
	}
	if (!(buf_str = ft_arrjoin(&argv[1 + p->flag], argc - (1 + p->flag))))
		return (0);
	args[0] = ft_strsplitspaces(buf_str);
	free(buf_str);
	if (args[0] == NULL)
		return (0);
	return (set_args(args, p));
}

static void	find_shortest_solution(t_ps_prms *p)
{
	if (!(p->copy_a = ft_dllcpy(p->stack_a, p->copy_a)))
		exit (0);
	p->mode = 0;
	rotor(p);
	p->prev_count = p->cmd_count;
	ft_dlldel(&p->stack_a, &ft_lstfree);
	p->stack_a = p->copy_a;
	if (!(p->copy_a = ft_dllcpy(p->stack_a, p->copy_a)))
		exit (0);
	drummer(p);
	ft_dlldel(&p->stack_a, &ft_lstfree);
	p->stack_a = p->copy_a;
	p->mode = 1;
	if (p->prev_count < p->cmd_count)
		rotor(p);
	else
		drummer(p);
}

int		main(int argc, char **argv)
{
	char		**args;
	t_ps_prms	p;

	if (argc < 2 || ((p.flag = check_flags(argc, argv, &p)) && argc < \
		(2 + p.flag)))
		return (display_usage());
	if (!check_n_put_args(argc, argv, &args, &p) || !check_duplicates(&p))
		return (error_msg(0, NULL));
	if(!stack_sorting(&p))
		return (error_msg(1, &p));
	if(check_sort_state(&p, 1, 0))
		exit (0);
	if (p.len_a <= 10)
		find_shortest_solution(&p);
	else
		drummer(&p);
	if (p.flag)
		close(p.fd);
	exit (0);
}
