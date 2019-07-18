/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 15:59:47 by uhand             #+#    #+#             */
/*   Updated: 2019/07/18 12:17:15 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int			display_usage(void)
{
	ft_printf("%s\n%s\n\n", \
		"Usage: ./checker [options] <args ...>\n  options:", \
		"\t-v\t\tvisualizer\n\t-f [file_name]\tread instructions from a file");
	ft_printf("%s\n\t%s\n\t%s\n", "Example:", \
		"./push_swap <args ...> | ./checker <args ...>", \
		"./checker -f [file_name] <args ...>");
	return (0);
}

void		clear_image(t_check_prms *p)
{
	int			*image;
	int			i;
	int			lenth;

	image = (int*)p->v->img_addr;
	i = -1;
	lenth = WIN_X * WIN_Y;
	while (++i < (lenth))
		image[i] = BKG_CLR;
}

/*
**	^^^ Norma placed functions
**	vvv Atoi functions
*/

static void	skip_starters(size_t *i, char *s, int *sign)
{
	while (s[*i] == ' ' || (s[*i] >= 9 && s[*i] <= 13))
		*i = *i + 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign = -1;
		*i = *i + 1;
	}
	while (s[*i] == '0')
		*i = *i + 1;
}

static void	check_digits(size_t i, char *s, long long *res)
{
	size_t			len;
	long long		order;
	unsigned int	max;

	len = 0;
	while (ft_isdigit(s[i + len]))
		len++;
	order = 1;
	while (len > 0)
	{
		if (!(*res <= *res + ((s[i + len - 1] - 48) * order)))
		{
			max = -1;
			*res = (long long)max;
			break ;
		}
		*res = *res + ((s[i + len - 1] - 48) * order);
		order *= 10;
		len--;
	}
}

long long	ps_atoi(const char *str)
{
	size_t		i;
	char		*s;
	long long	res;
	int			sign;

	i = 0;
	s = (char*)str;
	res = 0;
	sign = 1;
	if (ft_strlen(str) == 0)
		return (0);
	skip_starters(&i, s, &sign);
	if (!(ft_isdigit(s[i])))
		return (0);
	check_digits(i, s, &res);
	return (res * sign);
}
