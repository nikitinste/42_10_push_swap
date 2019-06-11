/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:45:59 by uhand             #+#    #+#             */
/*   Updated: 2019/06/11 19:54:07 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		close_checker(void *prm)
{
	t_check_prms	*p;

	p = (t_check_prms*)prm;
	mlx_destroy_image (p->v->mlx_ptr, p->v->img_ptr);
	mlx_destroy_window(p->v->mlx_ptr, p->v->win_ptr);
	//free all v data
	exit(p->v->cmd_ret);
	return (0);
}

/*void	set_grad_color(t_grad *g, t_grad_prms *clr, int pos)
{
	g->a = (unsigned char*)&clr->a;
	g->b = (unsigned char*)&clr->b;
	g->d_alpha = (int)g->b[g->alpha] - (int)g->a[g->alpha];
	g->d1 = (int)g->b[g->start] - (int)g->a[g->start];
	g->d2 = (int)g->b[g->start + 1] - (int)g->a[g->start + 1];
	g->d3 = (int)g->b[g->start + 2] - (int)g->a[g->start + 2];
	g->color = 0;
	g->c = (unsigned char*)&(g->color);
	g->c[g->start] = ((g->d1 * pos) / clr->delta) + g->a[g->start];
	g->c[g->start + 1] = ((g->d2 * pos) / clr->delta) + g->a[g->start + 1];
	g->c[g->start + 2] = ((g->d3 * pos) / clr->delta) + g->a[g->start + 2];
	g->c[g->alpha] = ((g->d_alpha * pos) / clr->delta) + g->a[g->alpha];
}

int			get_grad_color(t_img_data *img, t_grad_prms *clr, int pos)
{
	t_grad			grad;

	if (clr->a == clr->b || pos == 0)
		return (clr->a);
	if (img->ndn == 0)
	{
		grad.start = 0;
		grad.alpha = 3;
	}
	else
	{
		grad.start = 1;
		grad.alpha = 0;
	}
	set_grad_color(&grad, clr, pos);
	return (grad.color);
}*/

char	*make_string(t_check_prms *p, int step)
{
	char	*str;
	char	*str_1;
	char	*buf;

	if (!(buf = ft_itoa(step)))
		return (NULL);
	if (!(str = ft_strjoin("Step ", buf)))
		return (NULL);
	free(buf);
	if (!(str_1 = ft_strjoin(str, "/")))
		return (NULL);
	free(str);
	if (!(buf = ft_itoa(p->v->count)))
		return (NULL);
	if (!(str = ft_strjoin(str_1, buf)))
		return (NULL);
	free(buf);
	free(str_1);
	if (!(str_1 = ft_strjoin(str, " ")))
		return (NULL);
	free(str);
	if (!(str = ft_strjoin(str_1, p->command)))
		return (NULL);
	free(str_1);
	return (str);
}
