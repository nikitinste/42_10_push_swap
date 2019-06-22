/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:56:30 by uhand             #+#    #+#             */
/*   Updated: 2019/06/22 14:18:58 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		error_msg(int prm, t_ps_prms *p)
{
	if (prm)
	{
		ft_lstdel(&p->stack_a, &ft_lstfree);
		ft_lstdel(&p->stack_b, &ft_lstfree);
	}
	ft_putstr_fd("Error\n", 2);
	return (-1);
}

static int		check_duplicates(t_ps_prms *p)
{
	t_list	*ptr;
	t_list	*ptr_2;

	ptr = p->stack_a;
	while (ptr != NULL)
	{
		ptr_2 = p->stack_a;
		while (ptr_2 != NULL)
		{
			if (*((int*)ptr->content) == *((int*)ptr_2->content) \
				&& ptr != ptr_2)
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

static int	set_args(char ***args, t_ps_prms *p)
{
	t_content	c;
	long long	buf;

	p->len = 0;
	while (args[0][p->len] != NULL)
		p->len++;
	c.sort_pos = 0;
	c.pos = -1;
	c.prev = NULL;
	while (++c.pos < p->len)
	{
		buf = ps_atoi(args[0][c.pos]);
		c.val = (int)buf;
		free(args[0][c.pos]);
		if (buf != (long long)c.val || \
			ft_lstaddnext(&p->stack_a, (void*)&c, sizeof(t_content)) == -1)
		{
			ft_lstdel(&p->stack_a, &ft_lstfree);
			c.pos = -1;
			while (++c.pos < p->len)
				free(args[0][c.pos]);
			return (0);
		}
	}
	return (1);
}

static int	check_n_put_args(int argc, char **argv, char ***args, \
	t_ps_prms *p)
{
	int		i;
	int		j;
	char	*buf_str;

	i = 0;
	p->stack_a = NULL;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j] != '\0')
		{
			if (!(ft_isdigit((int)argv[i][j])) || ft_isspace((int)argv[i][j]))
				if (!((argv[i][j] == '+' || argv[i][j] == '-') && \
					ft_isdigit((int)argv[i][j + 1])))
					return (0);
		}
	}
	if (!(buf_str = ft_arrjoin(&argv[1], argc - 1)))
		return (0);
	args[0] = ft_strsplitspaces(buf_str);
	free(buf_str);
	if (args[0] == NULL)
		return (0);
	return (set_args(args, p));
}

int		main(int argc, char **argv)
{
	char		**args;
	t_ps_prms	p;

	if (argc < 2)
		return (0);
	if (!check_n_put_args(argc, argv, &args, &p) || !check_duplicates(&p))
		return (error_msg(0, NULL));
	if (argc < 3)
		return (0);
	if(!sorting(&p))
		return (error_msg(1, &p));
	//
	return (0);
}
