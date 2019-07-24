/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:45:59 by uhand             #+#    #+#             */
/*   Updated: 2019/07/24 20:50:05 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int			close_checker(void *prm)
{
	t_check_prms	*p;

	p = (t_check_prms*)prm;
	mlx_destroy_image(p->v->mlx_ptr, p->v->img_ptr);
	mlx_destroy_window(p->v->mlx_ptr, p->v->win_ptr);
	ft_lstdel(&p->stack_a, &ft_lstfree);
	ft_lstdel(&p->stack_b, &ft_lstfree);
	ft_lstdel(&p->v->commands, &ft_lstfree);
	exit(p->v->cmd_ret);
	return (0);
}

static void	set_grad_color(t_grad *g, t_grad_prms *clr, int pos)
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

int			get_grad_color(t_check_prms *p, t_grad_prms *clr, int pos)
{
	t_grad			grad;

	if (clr->a == clr->b || pos == 0)
		return (clr->a);
	if (p->v->ndn == 0)
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
}

void		set_colors_n_widh(t_check_prms *p)
{
	t_grad_prms	grad;

	grad.a = NUL_CLR;
	if (ft_abs(p->v->max_val) >= ft_abs(p->v->min_val))
	{
		p->v->max_width = ft_abs(p->v->max_val);
		p->v->pos_clr = POS_CLR;
		grad.delta = p->v->max_width;
		grad.b = NEG_CLR;
		p->v->neg_clr = get_grad_color(p, &grad, ft_abs(p->v->min_val));
	}
	else
	{
		p->v->max_width = ft_abs(p->v->min_val);
		p->v->neg_clr = NEG_CLR;
		grad.delta = p->v->max_width;
		grad.b = POS_CLR;
		p->v->pos_clr = get_grad_color(p, &grad, ft_abs(p->v->max_val));
	}
	if (p->v->max_width == 0)
		p->v->max_width++;
}

char		*make_string(t_check_prms *p, int step)
{
	t_make_str	m;

	if (p->v->crnt_cmd->next)
		m.next = (char*)p->v->crnt_cmd->next->content;
	else
		m.next = NULL;
	m.steps = ft_itoa(p->v->count);
	m.c_step = ft_itoa(step);
	m.elems = ft_itoa(p->len);
	if (!m.steps || !m.c_step || !m.elems)
		return (0);
	if (!(m.str = ft_nstrjoin(11, "Step: ", p->command, " ", m.c_step, "/", \
		m.steps, " -> ", m.next, " (", m.elems, ")")))
	{
		free(m.steps);
		free(m.elems);
		free(m.c_step);
		return (0);
	}
	free(m.steps);
	free(m.elems);
	free(m.c_step);
	return (m.str);
}
