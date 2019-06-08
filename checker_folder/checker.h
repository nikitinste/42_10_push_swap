/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:57:12 by uhand             #+#    #+#             */
/*   Updated: 2019/06/08 19:29:46 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# define A !ft_strcmp
# define WIN_X 600
# define WIN_Y 1395
# define BKG_CLR 0xcce5ff
# define POS_CLR 0x37b6af
# define NEG_CLR 0xf15f75

typedef struct s_check_prms t_check_prms;
typedef	void				(*t_command)(t_check_prms *p);

/*
**	visualizer params: v
*/

typedef struct	s_vis_prms
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	//void		*bkg_ptr;
	char		*img_addr;
	//char		*bkg_addr;
	int			bpp;
	int			lsz;
	int			ndn;
	int			el_hight;
	int			el_width;
	int			max_val;
	int			scale_index;
	//int			delta;
	t_list		*commands;
	t_list		*crnt_cmd;
	int			run;
	//int			err_msg;
}				t_vis_prms;

/*
**	checker params: p
*/

struct			s_check_prms
{
	t_list		*stack_a;
	t_list		*stack_b;
	int			len;
	int			flag;
	int			ret;
	char		*command;
	t_command	command_arr[11];
	char		*rule_list[11];
	int			result;
	t_vis_prms	*v;
};

int			check_flags(int argv, char **argc);
int			error_msg(int prm, t_check_prms *p);
long long	ps_atoi(const char *str);
int			checker_init(t_check_prms *p);
int			window_init(t_check_prms *p);
int			check_duplicates(t_check_prms *p);
int			check_command(t_check_prms *p);
int			check_stacks(t_check_prms *p);
void		visualize_command(t_check_prms *p);
void		clear_image(t_check_prms *p);
int			vis_waiting(t_check_prms *p);
int			deal_key(int key, void *prm);
int			close_checker(void *prm);

void		swap_a(t_check_prms *p);
void		swap_b(t_check_prms *p);
void		swap_ab(t_check_prms *p);
void		push_a(t_check_prms *p);
void		push_b(t_check_prms *p);
void		rotate_a(t_check_prms *p);
void		rotate_b(t_check_prms *p);
void		rotate_ab(t_check_prms *p);
void		rev_rot_a(t_check_prms *p);
void		rev_rot_b(t_check_prms *p);
void		rev_rot_ab(t_check_prms *p);

#endif
