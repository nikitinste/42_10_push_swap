/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:05:43 by uhand             #+#    #+#             */
/*   Updated: 2019/06/07 19:27:25 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int			close_checker(void *prm)
{
	t_check_prms	*p;

	p = (t_check_prms*)prm;
	mlx_destroy_image (p->v->mlx_ptr, p->v->img_ptr);
	mlx_destroy_window(p->v->mlx_ptr, p->v->win_ptr);
	//free all v data
	exit(0);
	return (0);
}

int			deal_key(int key, void *prm)
{
	t_check_prms	*p;

	p = (t_check_prms*)prm;
	if (key == 53)
		return (close_checker(prm));
	if (key == 36)
		while (p->v->crnt_cmd)
		{
			p->command = (char*)p->v->crnt_cmd->content;
			if (!check_command(p))
				return (error_msg(1, p));
			p->v->crnt_cmd = p->v->crnt_cmd->next;
		}
	else if (key == 124)
		if (p->v->crnt_cmd)
		{
			p->command = (char*)p->v->crnt_cmd->content;
			if (!check_command(p))
				return (error_msg(1, p));
			p->v->crnt_cmd = p->v->crnt_cmd->next;
		}
	return (0);
}

/*static int	get_command(void *prm)
{
	t_check_prms	*p;

	p = (t_check_prms*)prm;
	if (p->result != -1)
		return (0);
	if ((p->ret = get_next_line(0, &p->command)))
	{
		if (!check_command(p))
			return (error_msg(1, p));
		free(p->command);
	}
	else
	{
		if ((p->result = check_stacks(p)))
			mlx_string_put(p->v->mlx_ptr, p->v->win_ptr, 5, 5, 0x2c8a0c, "OK!)");
		else
			mlx_string_put(p->v->mlx_ptr, p->v->win_ptr, 5, 5, 0xba1414, "KO!(");
	}
	return (0);
}*/

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

int			vis_waiting(t_check_prms *p)
{
	if (!p->flag)
		return (0);
	visualize_command(p);
	mlx_string_put(p->v->mlx_ptr, p->v->win_ptr, 5, 5, 0x0c608a, "Press \
		\"Enter\" for run or \"Right\" for step.");
	while ((p->ret = get_next_line(0, &p->command)))
	{
		if (!ft_lstaddnext(&p->v->commands, (void*)p->command, \
			ft_strlen(p->command) + 1))
			return (error_msg(1, p));
		free(p->command);
	}
	p->v->crnt_cmd = p->v->commands;
	/*if (p->result)
		mlx_string_put(p->v->mlx_ptr, p->v->win_ptr, 5, 5, 0x2c8a0c, "OK!)");
	else
		mlx_string_put(p->v->mlx_ptr, p->v->win_ptr, 5, 5, 0xba1414, "KO!(");*/
	mlx_hook(p->v->win_ptr, 2, 0, &deal_key, (void*)(p));
	mlx_hook(p->v->win_ptr, 17, 0, &close_checker, (void*)(p));
	//mlx_loop_hook (p->v->mlx_ptr, &get_command, (void*)(p));
	mlx_loop(p->v->mlx_ptr);
	return (0);
}
