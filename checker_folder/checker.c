/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:50:16 by uhand             #+#    #+#             */
/*   Updated: 2019/06/04 17:06:54 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	check_stacks(t_check_prms *p)
{
	t_list	*ptr;

	if (p->stack_b != NULL)
		return (0);
	ptr = p->stack_a;
	ft_printf("---\n");
	while (ptr->next != NULL)
	{
		if (*((int*)ptr->content) > *((int*)ptr->next->content))
			return (0);
		ft_printf("%d\n", *((int*)ptr->content));
		ptr = ptr->next;
	}
	ft_printf("%d\n---\n", *((int*)ptr->content));
	//free stacks
	return (1);
}

static int	check_command(t_check_prms *p)
{
	int		i;

	i = -1;
	while (++i < 11)
	{
		if (!ft_strcmp(p->command, p->rule_list[i]))
		{
			p->command_arr[i](p);
			return (1);
			// visualizer
		}
	}
	return (0);
}

static int	set_args(char ***args, t_check_prms *p)
{
	int			i;
	int			content;
	long long	buf;

	p->len = 0;
	while (args[0][p->len] != NULL)
		p->len ++;
	i = -1;
	while (++i < p->len)
	{
		buf = ps_atoi(args[0][i]);
		content = (int)buf;
		free (args[0][i]);
		if (buf != (long long)content || \
			ft_lstaddnext(&p->stack_a, (void*)&buf, 4) == -1)
			{
				ft_lstdel(&p->stack_a, &ft_lstfree);
				while (++i < p->len)
					free (args[0][i]);
				return (0);
			}
	}
	return (1);
}

static int	check_n_put_args(int argv, char **argc, char ***args, \
	t_check_prms *p)
{
	int		i;
	int		j;
	char	*buf_str;

	i = 0;
	while (++i < argv)
	{
		j = -1;
		while(argc[i][++j] != '\0')
		{
			if (!(ft_isdigit((int)argc[i][j])) || ft_isspace((int)argc[i][j]))
				if (!((argc[i][j] == '+' || argc[i][j] == '-') && \
					ft_isdigit((int)argc[i][j + 1])))
					return (0);
		}
	}
	if (!(buf_str = ft_arrjoin(&argc[1], argv - 1)))
		return (0);
	args[0] = ft_strsplitspaces(buf_str);
	free (buf_str);
	if (args[0] == NULL)
		return (0);
	return (set_args(args, p));
}

int		main(int argv, char **argc)
{
	char			**args;
	int				ret;
	t_check_prms	p;

	if (argv < 2 || (argv < 3 && (p.flag = check_flags(argv, argc))))
		return (0);
	if (!check_n_put_args(argv, argc, &args, &p) || !check_duplicates(&p))
		return (error_msg(0, NULL));
	if (!checker_init(&p))
		return (error_msg(1, &p));
	while ((ret = get_next_line(0, &p.command)))
	{
		if (!check_command(&p))
			return (error_msg(1, &p));
		free (p.command);
	}
	if (ret == -1)
		return (error_msg(1, &p));
	if (check_stacks(&p))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	return (0);
}
