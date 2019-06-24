/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:58:36 by uhand             #+#    #+#             */
/*   Updated: 2019/06/24 18:10:47 by uhand            ###   ########.fr       */
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
	t_dllist	*stack_a;
	t_dllist	*stack_b;
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
}				t_content;

/*
**	shaker sort params: s
*/

typedef struct	s_shaker
{
	t_dllist	*stack;
	t_dllist	*left;
	t_dllist	*right;
	t_dllist	*tmp;
	t_content	*a;
	t_content	*b;
}				t_shaker;

long long	ps_atoi(const char *str);
int			sorting(t_ps_prms *p);

#endif
