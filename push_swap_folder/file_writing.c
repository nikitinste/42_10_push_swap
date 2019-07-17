/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_writing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:00:17 by uhand             #+#    #+#             */
/*   Updated: 2019/07/17 19:49:36 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	file_error(void)
{
	ft_printf("File open/create/write error\n");
	exit(-1);
}

int		check_flags(int argc, char **argv, t_ps_prms *p)
{
	int		ret;

	ret = 0;
	p->fd = 1;
	if (argc < 3)
		return (0);
	if (!ft_strcmp(argv[1], "-f"))
	{
		ret = 2;
		p->file = argv[2];
	}
	if ((ret == 2 || ret == 3) && argc > 3)
	{
		if ((p->fd = open(p->file, \
		O_CREAT | O_RDWR | O_APPEND | O_TRUNC, S_IWRITE | S_IREAD)) == -1)
			file_error();
	}
	return (ret);
}

int		display_usage(void)
{
	ft_printf("%s\n%s\n\n", \
		"Usage: ./push_swap [options] <args ...>\n  options:", \
		"\t-f [file_name]\twrite instructions to file");
	ft_printf("%s\n\t%s\n\t%s\n", "Example:", \
		"./push_swap <args ...> | ./checker <args ...>", \
		"./push_swap -f [file_name] <args ...>");
	return (0);
}
