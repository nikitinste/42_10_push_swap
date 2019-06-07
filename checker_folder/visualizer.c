/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:01:27 by uhand             #+#    #+#             */
/*   Updated: 2019/06/07 17:42:03 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	set_limits(t_check_prms *p)
{
	t_list		*ptr;

	ptr = p->stack_a;
	p->v->max_val = 0;
	//p->v->min_val = 0;
	while (ptr != NULL)
	{
		if (ft_abs(*((int*)ptr->content)) > p->v->max_val)
			p->v->max_val = ft_abs(*((int*)ptr->content));
		/*if (ft_abs((int)ptr->content) < p->v->min_val)
			p->v->min_val = ft_abs((int)ptr->content);*/
		ptr = ptr->next;
	}
	//p->v->delta = p->v->max_val - p->v->min_val;
	p->v->scale_index = (((WIN_X / 2) - 2) * 100) / p->v->max_val;
}

int			window_init(t_check_prms *p)
{
	t_vis_prms	*v;

	p->v = NULL;
	p->result = -1;
	if (!p->flag)
		return (1);
	if (!(v = (t_vis_prms*)malloc(sizeof(t_vis_prms))))
		return (0);
	v->el_hight = WIN_Y / p->len;
	v->el_width = WIN_X / 2;
	p->v = v;
	set_limits(p);
	p->v->mlx_ptr = mlx_init();
	p->v->win_ptr = mlx_new_window(v->mlx_ptr, WIN_X, WIN_Y, "Checker");
	p->v->img_ptr = mlx_new_image(v->mlx_ptr, WIN_X, WIN_Y);
	//v->bkg_ptr = mlx_new_image(v->mlx_ptr, WIN_X, WIN_Y);
	p->v->img_addr = mlx_get_data_addr(v->img_ptr, &v->bpp, &v->lsz, &v->ndn);
	//v->bkg_addr = mlx_get_data_addr(v->bkg_ptr, &v->bpp, &v->lsz, &v->ndn);
	return (1);
}

static void	put_pix_to_img(void *img_addr, int x, int y, int color)
{
	int	*image;

	if (x < 0 || y < 0 || x >= WIN_X || y >= WIN_Y)
		return ;
	image = (int*)img_addr;
	image[(y * WIN_X) + x] = color;
}

static void	draw_rectangle(t_check_prms *p, int x, int y, int value)
{
	int		x_i;
	int		y_i;
	int		color;

	y_i = 1;
	if (value < 0)
	{
		value *= -1;
		color = NEG_CLR;
	}
	else
		color = POS_CLR;
	while (++y_i < (p->v->el_hight - 1))
	{
		x_i = 1 + ((((p->v->max_val * p->v->scale_index) / 100) - value) / 2);
		while (++x_i < (p->v->el_width - (1 + ((((p->v->max_val * \
			p->v->scale_index) / 100) - value) / 2))))
			put_pix_to_img(p->v->img_addr, (x +  x_i), (y + y_i), color);
	}
}

void		visualize_command(t_check_prms *p)
{
	t_list	*stack_ptr;
	int		x;
	int		y;

	if (!p->flag)
		return ;
	clear_image(p);
	stack_ptr = p->stack_a;
	x = 0;
	while (x < WIN_X)
	{
		y = 0;
		while (stack_ptr)
		{
			draw_rectangle(p, x, y, \
				(*((int*)stack_ptr->content) * p->v->scale_index) / 100);
			stack_ptr = stack_ptr->next;
			y += p->v->el_hight;
		}
		x += p->v->el_width;
		stack_ptr = p->stack_b;
	}
	mlx_put_image_to_window(p->v->mlx_ptr, p->v->win_ptr, p->v->img_ptr, 0, 0);
}
