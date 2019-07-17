/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:50:16 by uhand             #+#    #+#             */
/*   Updated: 2019/07/17 15:16:26 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int			check_stacks(t_check_prms *p)
{
	t_list	*ptr;

	if (p->stack_b != NULL)
	{
		ft_printf("KO\n");
		return (0);
	}
	ptr = p->stack_a;
	while (ptr->next != NULL)
	{
		if (*((int*)ptr->content) > *((int*)ptr->next->content))
		{
			ft_printf("KO\n");
			return (0);
		}
		ptr = ptr->next;
	}
	ft_printf("OK\n");
	return (1);
}

int			check_command(t_check_prms *p)
{
	int		i;

	i = -1;
	while (++i < 11)
	{
		if (!ft_strcmp(p->command, p->rule_list[i]))
		{
			p->command_arr[i](p);
			visualize_command(p);
			return (1);
		}
	}
	visualize_command(p);
	return (0);
}

static int	set_args(char ***args, t_check_prms *p)
{
	int			i;
	int			content;
	long long	buf;

	p->len = 0;
	while (args[0][p->len] != NULL)
		p->len++;
	i = -1;
	while (++i < p->len)
	{
		buf = ps_atoi(args[0][i]);
		content = (int)buf;
		free(args[0][i]);
		if (buf != (long long)content || \
			ft_lstaddnext(&p->stack_a, (void*)&content, sizeof(int)) == -1)
		{
			ft_lstdel(&p->stack_a, &ft_lstfree);
			while (++i < p->len)
				free(args[0][i]);
			return (0);
		}
	}
	return (1);
}

static int	check_n_put_args(int argc, char **argv, char ***args, \
	t_check_prms *p)
{
	int		i;
	int		j;
	char	*buf_str;

	i = p->flag;
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

int			main(int argc, char **argv)
{
	char			**args;
	t_check_prms	p;

	p.file = NULL;
	if (argc < 2 || ((p.flag = check_flags(argc, argv, &p)) && argc < \
		(2 + p.flag)))
		return (display_usage());
	if (!check_n_put_args(argc, argv, &args, &p) || !check_duplicates(&p))
		return (error_msg(0, NULL));
	if (!checker_init(&p))
		return (error_msg(1, &p));
	if (p.flag == 1 || p.flag == 3)
		return (vis_waiting(&p));
	while ((p.ret = get_next_line(p.fd, &p.command)) > 0)
	{
		if (!check_command(&p))
			return (error_msg(1, &p));
		free(p.command);
	}
	if (p.ret == -1)
		return (error_msg(1, &p));
	if (p.flag == 2 || p.flag == 3)
		close(p.fd);
	check_stacks(&p);
	return (0);
}
