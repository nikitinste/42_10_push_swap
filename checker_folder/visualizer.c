/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:01:27 by uhand             #+#    #+#             */
/*   Updated: 2019/06/04 17:06:13 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		window_init(t_check_prms *p)
{
	t_vis_prms	*v;

	p->v = NULL;
	if (!p->flag)
		return (1);
	if (!(v = (t_vis_prms*)malloc(sizeof(t_vis_prms))))
		return (0);
	v->mlx_ptr = mlx_init();
	v->win_ptr = mlx_new_window(v->mlx_ptr, 1200, 600, "Push_swap Checker");
	v->img_ptr = mlx_new_image(v->mlx_ptr, 1200, 600);
	v->addr = mlx_get_data_addr(v->img_ptr, &v->bpp, &v->lsz, &v->ndn);
	p->v = v;
	return (1);
}
