/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:01:27 by uhand             #+#    #+#             */
/*   Updated: 2019/07/18 15:22:32 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	set_limits(t_check_prms *p)
{
	t_list		*ptr;

	ptr = p->stack_a;
	p->v->max_val = 0;
	p->v->min_val = 0;
	while (ptr != NULL)
	{
		if (*((int*)ptr->content) > p->v->max_val)
			p->v->max_val = *((int*)ptr->content);
		if (*((int*)ptr->content) < p->v->min_val)
			p->v->min_val = *((int*)ptr->content);
		ptr = ptr->next;
	}
	set_colors_n_widh(p);
	p->v->scale_index = (((WIN_X / 2) - 2) * 100) / p->v->max_width;
}

int			window_init(t_check_prms *p)
{
	t_vis_prms	*v;

	p->v = NULL;
	p->result = -1;
	if (!(p->flag == 1 || p->flag == 3))
		return (1);
	if (!(v = (t_vis_prms*)malloc(sizeof(t_vis_prms))))
		return (0);
	v->el_width = WIN_X / 2;
	v->cmn_hight = WIN_Y - TOPLINE - 5;
	p->v = v;
	set_limits(p);
	p->v->mlx_ptr = mlx_init();
	p->v->win_ptr = mlx_new_window(v->mlx_ptr, WIN_X, WIN_Y, "Checker");
	p->v->img_ptr = mlx_new_image(v->mlx_ptr, WIN_X, WIN_Y);
	p->v->img_addr = mlx_get_data_addr(v->img_ptr, &v->bpp, &v->lsz, &v->ndn);
	p->v->commands = NULL;
	p->v->run = 0;
	p->v->cmd_ret = 1;
	p->v->count = 0;
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

static void	draw_rectangle(t_check_prms *p, int value)
{
	t_rectangle	r;

	r.y_i = 0;
	r.grad.a = NUL_CLR;
	if (value < 0)
	{
		value *= -1;
		r.grad.b = p->v->neg_clr;
		r.grad.delta = (ft_abs(p->v->min_val) * p->v->scale_index) / 100;
	}
	else
	{
		r.grad.b = p->v->pos_clr;
		r.grad.delta = (ft_abs(p->v->max_val) * p->v->scale_index) / 100;
	}
	r.color = get_grad_color(p, &r.grad, value);
	while (++r.y_i <= p->v->el_hight)
	{
		r.x_i = 1 + ((((p->v->max_width * p->v->scale_index) / 100) - value) \
			/ 2);
		while (++r.x_i < (p->v->el_width - (1 + ((((p->v->max_width * \
			p->v->scale_index) / 100) - value) / 2))))
			put_pix_to_img(p->v->img_addr, (X + r.x_i), (Y + r.y_i), r.color);
	}
}

void		visualize_command(t_check_prms *p)
{
	t_list	*stack_ptr;

	if (!(p->flag == 1 || p->flag == 3))
		return ;
	clear_image(p);
	stack_ptr = p->stack_a;
	X = 0;
	while (p->v->x < WIN_X)
	{
		Y = TOPLINE + 1;
		I = 0;
		while (stack_ptr)
		{
			set_el_high(p);
			draw_rectangle(p, \
				(*((int*)stack_ptr->content) * p->v->scale_index) / 100);
			stack_ptr = stack_ptr->next;
			Y += p->v->el_hight;
			I++;
		}
		X += p->v->el_width;
		stack_ptr = p->stack_b;
	}
	mlx_put_image_to_window(p->v->mlx_ptr, p->v->win_ptr, p->v->img_ptr, 0, 0);
}
