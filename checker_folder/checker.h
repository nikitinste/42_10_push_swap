/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:57:12 by uhand             #+#    #+#             */
/*   Updated: 2019/07/17 14:59:18 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# define A !ft_strcmp
# define WIN_X 600
# define WIN_Y 1575//1395//1035//1755
# define TOPLINE 26
# define BKG_CLR 0xcce5ff
# define POS_CLR 0x37b6af
# define NUL_CLR 0xffffff
# define NEG_CLR 0xf15f75
# define MLX p->v->mlx_ptr
# define WIN p->v->win_ptr

typedef struct s_check_prms t_check_prms;
typedef	void				(*t_command)(t_check_prms *p);

/*
** Make string params: m
*/

typedef struct	s_make_str
{
	char		*str;
	char		*steps;
	char		*c_step;
	char		*elems;
	char		*next;
}				t_make_str;

/*
** Input grad params: clr
*/

typedef struct	s_grad_prms
{
	int				delta;
	int				a;
	int				b;
}				t_grad_prms;

/*
** Operational grad params: grad
*/

typedef struct	s_grad
{
	unsigned char	*a;
	unsigned char	*b;
	unsigned char	*c;
	int				d_alpha;
	int				d1;
	int				d2;
	int				d3;
	int				color;
	int				start;
	int				alpha;
}				t_grad;

/*
**	Rectangle params: r
*/

typedef struct	s_rectangle
{
	int			x_i;
	int			y_i;
	int			color;
	t_grad_prms	grad;
}				t_rectangle;

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
	int			min_val;
	int			max_width;
	int			pos_clr;
	int			neg_clr;
	int			scale_index;
	int			count;
	t_list		*commands;
	t_list		*crnt_cmd;
	int			run;
	int			cmd_ret;
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
	int			fd;
	char		*file;
	int			ret;
	char		*command;
	t_command	command_arr[11];
	char		*rule_list[11];
	int			result;
	t_vis_prms	*v;
};

int			check_flags(int argv, char **argc, t_check_prms *p);
int			error_msg(int prm, t_check_prms *p);
int			error_file_msg(void);
int			display_usage();
long long	ps_atoi(const char *str);
int			checker_init(t_check_prms *p);
int			window_init(t_check_prms *p);
int			check_duplicates(t_check_prms *p);
int			check_command(t_check_prms *p);
int			check_stacks(t_check_prms *p);
void		visualize_command(t_check_prms *p);
void		clear_image(t_check_prms *p);
int			vis_waiting(t_check_prms *p);
void		set_colors_n_widh(t_check_prms *p);
int			get_grad_color(t_check_prms *p, t_grad_prms *clr, int pos);
//int			deal_key(int key, void *prm);
int			close_checker(void *prm);
char		*make_string(t_check_prms *p, int step);

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
