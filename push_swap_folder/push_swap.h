/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:58:36 by uhand             #+#    #+#             */
/*   Updated: 2019/07/09 20:19:52 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_ps_prms	t_ps_prms;
typedef	void				(*t_command)(t_ps_prms *p, char *command);

/*
**	push-swap params: p
*/

struct	s_ps_prms
{
	t_dllist		*stack_a;
	t_dllist		*stack_b;
	int				len_a;
	int				len_b;
	int				a;
	int				b;
	int				push_direction;
	int				norm;
	int				check;
	t_list			*rotation;
	t_list			*drums;
};

/*
**	stack content params: c
*/

typedef struct	s_content
{
	int				val;
	int				pos;
	int				sort_pos;
}				t_content;

/*
**	shaker sort params: s
*/

typedef struct	s_shaker
{
	t_dllist		*stack;
	t_dllist		*left;
	t_dllist		*right;
	t_dllist		*tmp;
	t_content		*a;
	t_content		*b;
}				t_shaker;

/*
**	command generator params: g
*/

typedef struct	s_cmd_gen
{
	t_command		command_arr[11];
	char			*rule_list[11];
}				t_cmd_gen;

/*
**	get command function params: m
*/

typedef struct	s_get_cmd
{
	int				cmd;
	t_dllist		*last_a;
	t_dllist		*last_b;
	t_content		*c_a;
	t_content		*c_b;
	t_content		*c_ar;
	t_content		*c_br;
}				t_get_cmd;

/*
**	normalise rotation params: n
*/

typedef struct	s_normalise
{
	t_dllist		*stack_a;
	t_dllist		*stack_b;
	int				way_a;
	int				way_b;
	int				rev_a;
	int				rev_b;
	int				way_ab;

}				t_normalise;

/*
**	normalise way params: w
*/

typedef struct	s_way
{
	t_dllist		*ptr;
	int				i;
	int				pos;
	int				neg;
	int				max;
	unsigned int	min;
	int				rot;
	int				bias;
	int				zero;
	int				direction;
	t_content		*c;
}				t_way;

/*
**	normalise command params: cmd
*/

typedef struct	s_execute
{
	int				i;
	int				command;
}				t_execute;


/*
**	drum params: d
*/

typedef struct	s_drums
{
	t_dllist		*ptr;
	int				rot;
	t_content		*content;
	int				val;
	int				cur_a;
	int				cur_b;
	int				rev_a;
	int				rev_b;
	int				cur_ab;
	int				a_way;
	int				b_way;
	int				ab_way;
	int				short_way;
}				t_drums;

/*
**	drum b_way params: b
*/

typedef struct	s_b_way
{
	t_dllist		*ptr;
	t_content		*content;
	int				val_first;
	int				val_second;
	int				rotation;
}				t_b_way;

long long	ps_atoi(const char *str);
int			stack_sorting(t_ps_prms *p);
t_dllist	*copy_linked_stack(t_dllist **src, t_dllist **dst);
void 		linked_stack_free(void *content, size_t size);
void		commands_init(t_ps_prms *p, t_cmd_gen *g);
void		reset_position_a(t_ps_prms *p);
void		reset_position_b(t_ps_prms *p);
void		set_even_odd(t_ps_prms *p);
int			check_condition(t_ps_prms *p, t_get_cmd *m);
int			check_sort_state(t_ps_prms *p, int a, int b);
int			normalise(t_ps_prms *p, t_cmd_gen *g);
void 		norm_swap(t_dllist **stack);
void		way_init(t_way *w, t_dllist *stack, int len);
void		check_bias(t_way *w);
void		set_way_params(t_way *w, int *way, int len);
void		check_direction(t_way *w, int len);
void		way_shortening(t_normalise *n);
void		run_commands(t_ps_prms *p, t_cmd_gen *g, t_normalise *n);
void		execute_command(t_ps_prms *p, t_cmd_gen *g, t_execute *cmd, \
	int way);
void		prepare_stack_b(t_ps_prms *p, t_cmd_gen *g);
void		run_drums(t_ps_prms *p, t_cmd_gen *g);
void		drums_init(t_drums *d, t_ps_prms *p);
void		set_drums_way(t_drums *d, int way_a, int way_b);
void		set_short_way(t_drums *d);
void		run_drum_commands(t_ps_prms *p, t_cmd_gen *g, t_drums *d);
int			check_stack_is_sorted(t_dllist *stack);
void		rotor(t_ps_prms *p);
void		drummer(t_ps_prms *p);
void		compare_ways(t_ps_prms *p);

void		drummer_2(t_ps_prms *p);
void		prepare_stack_a(t_ps_prms *p, t_cmd_gen *g);
void		run_rev_drums(t_ps_prms *p, t_cmd_gen *g);
void		rev_drums_init(t_drums *d, t_ps_prms *p);
void		run_rev_drum_commands(t_ps_prms *p, t_cmd_gen *g, t_drums *d);
int			normalise_b(t_ps_prms *p, t_cmd_gen *g);


int			rrr_condition(t_ps_prms *p, t_get_cmd *m);
int			rra_condition(t_ps_prms *p, t_get_cmd *m);
int			rrb_condition(t_ps_prms *p, t_get_cmd *m);
int			rr_condition(t_ps_prms *p, t_get_cmd *m);
int			ra_condition(t_ps_prms *p, t_get_cmd *m);
int			rb_condition(t_ps_prms *p, t_get_cmd *m);

void		rev_rot_ab(t_ps_prms *p, char *command);
void		rotate_ab(t_ps_prms *p, char *command);
void		rev_rot_a(t_ps_prms *p, char *command);
void		rev_rot_b(t_ps_prms *p, char *command);
void		rotate_a(t_ps_prms *p, char *command);
void		rotate_b(t_ps_prms *p, char *command);
void		swap_ab(t_ps_prms *p, char *command);
void		swap_a(t_ps_prms *p, char *command);
void		swap_b(t_ps_prms *p, char *command);
void		push_b(t_ps_prms *p, char *command);
void		push_a(t_ps_prms *p, char *command);
#endif
