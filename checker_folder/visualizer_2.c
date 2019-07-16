/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:05:43 by uhand             #+#    #+#             */
/*   Updated: 2019/07/16 14:57:54 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	step_command(t_check_prms *p)
{
	int			ret;
	static int	step;
	char		*str;

	if (p->v->crnt_cmd)
	{
		p->command = (char*)p->v->crnt_cmd->content;
		ret = check_command(p);
		if (!(str = make_string(p, ++step)))
			return (0);
		mlx_string_put(MLX, WIN, 4, 4, 0x0c5c8a, str);
		free(str);
		if (!ret)
		{
			p->result = 3;
			return (error_msg(0, p));
		}
		p->v->crnt_cmd = p->v->crnt_cmd->next;
	}
	if (!p->v->crnt_cmd && p->result == -1)
		p->result = check_stacks(p);
	return (1);
}

static int	deal_key(int key, void *prm)
{
	t_check_prms	*p;

	p = (t_check_prms*)prm;
	if (key == 53)
		return (close_checker(prm));
	if (p->result != 2)
	{
		if (key == 36)
		{
			if (p->v->crnt_cmd)
				p->v->run = 1;
		}
		else if (key == 124)
			if ((p->v->cmd_ret = step_command(p)) != 1)
				return (p->v->cmd_ret);
	}
	return (0);
}

static int	get_command(void *prm)
{
	t_check_prms	*p;

	p = (t_check_prms*)prm;
	if (p->v->run && p->result == -1)
	{
		if ((p->v->cmd_ret = step_command(p)) != 1)
			return (p->v->cmd_ret);
		else if (!p->v->run || p->result != -1)
			p->v->run = 0;
		usleep(2000000 / p->len);
	}
	if (p->result == 1 && p->v->cmd_ret && p->result != 2)
		mlx_string_put(MLX, WIN, 545, 4, 0x2c8a0c, "OK!)");
	else if (p->result == 0 && p->v->cmd_ret && p->result != 2)
		mlx_string_put(MLX, WIN, 545, 4, 0xba1414, "KO!(");
	else if (p->v->cmd_ret == -1 && p->result != 2)
		mlx_string_put(MLX, WIN, 530, 4, 0xba1414, "Error!");
	if (p->result != -1)
		p->result = 2;
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

int			put_start_string(t_check_prms *p)
{
	char		*str;
	char		*steps;
	char		*elems;

	if (!(steps = ft_itoa(p->v->count)) || !(elems = ft_itoa(p->len)))
		return (0);
	if(!(str = ft_nstrjoin(8, "Press \"Enter\" for run or \"Right\" for step", \
		": ", (char*)p->v->commands->content, " 1/", steps, " (", elems, ")")))
	{
		free(steps);
		free(elems);
		return (0);
	}
	free(steps);
	free(elems);
	mlx_string_put(p->v->mlx_ptr, p->v->win_ptr, 5, 5, 0x0c608a, str);
	free(str);
	return (1);
}

int			vis_waiting(t_check_prms *p)
{
	if (!p->flag)
		return (0);
	visualize_command(p);
	while ((p->ret = get_next_line(p->fd, &p->command)))
	{
		if (!ft_lstaddnext(&p->v->commands, (void*)p->command, \
			ft_strlen(p->command) + 1))
			return (error_msg(1, p));
		p->v->count++;
		free(p->command);
	}
	if (p->v->commands)
	{
		if (!put_start_string(p))
			return (0);
	}
	else
		p->result = check_stacks(p);
	p->v->crnt_cmd = p->v->commands;
	mlx_hook(p->v->win_ptr, 2, 0, &deal_key, (void*)(p));
	mlx_hook(p->v->win_ptr, 17, 0, &close_checker, (void*)(p));
	mlx_loop_hook (p->v->mlx_ptr, &get_command, (void*)(p));
	mlx_loop(p->v->mlx_ptr);
	return (0);
}
