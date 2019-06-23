/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:58:36 by uhand             #+#    #+#             */
/*   Updated: 2019/06/23 19:47:33 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

/*
**	push-swap params: p
*/

typedef struct	s_ps_prms
{
	t_list		*stack_a;
	t_list		*stack_b;
	int			len;
}				t_ps_prms;

/*
**	stack content params: c
*/

typedef struct	s_content
{
	int			val;
	int			pos;
	int			sort_pos;
	t_list		*prev;
}				t_content;

/*
**	shaker sort params: s
*/

typedef struct	s_shaker
{
	t_list		**stack;
	t_list		*left;
	t_list		*right;
	t_list		*tmp;
	t_content	*c_l;
	t_content	*c_r;
	t_content	*a;
	t_content	*b;
}				t_shaker;

long long	ps_atoi(const char *str);
int			sorting(t_ps_prms *p);

#endif
