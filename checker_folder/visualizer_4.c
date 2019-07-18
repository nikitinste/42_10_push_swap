/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:42:37 by uhand             #+#    #+#             */
/*   Updated: 2019/07/18 16:38:17 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		display_usage(void)
{
	ft_printf("%s\n%s\n\n", \
		"Usage: ./checker [options] <args ...>\n  options:", \
		"\t-v\t\tvisualizer\n\t-f [file_name]\tread instructions from a file");
	ft_printf("%s\n\t%s\n\t%s\n", "Example:", \
		"./push_swap <args ...> | ./checker <args ...>", \
		"./checker -f [file_name] <args ...>");
	return (0);
}

void	clear_image(t_check_prms *p)
{
	int		*image;
	int		i;
	int		lenth;

	image = (int*)p->v->img_addr;
	i = -1;
	lenth = WIN_X * WIN_Y;
	while (++i < (lenth))
		image[i] = BKG_CLR;
}

void	set_el_high(t_check_prms *p)
{
	int		y_0;
	int		y_1;

	y_0 = ((HIGHT * I * 100) / p->len);
	if (y_0 % 100 >= 50)
		y_0 = (y_0 / 100) + 1;
	else
		y_0 = y_0 / 100;
	y_1 = ((HIGHT * (I + 1) * 100) / p->len);
	if (y_1 % 100 >= 50)
		y_1 = (y_1 / 100) + 1;
	else
		y_1 = y_1 / 100;
	p->v->el_hight = y_1 - y_0;
}

void	print_signature(t_check_prms *p)
{
	mlx_string_put(MLX, WIN, 380, WIN_Y - 52, 0xba1414, \
		"Stephan Nikitin");
	mlx_string_put(MLX, WIN, 350, WIN_Y - 26, 0xba1414, \
		"github.com/nikitinste");
}
