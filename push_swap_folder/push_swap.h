/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:58:36 by uhand             #+#    #+#             */
/*   Updated: 2019/06/22 14:15:32 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

/*
**	shaker sort params: s
*/

typedef struct	s_shaker
{
	t_list	*left;
	t_list	*right;
	t_list	*stack;
}				t_shaker;

/*
**	push-swap params: c
*/

typedef struct	s_content
{
	int		val;
	int		pos;
	int		sort_pos;
	t_list	*prev;
}				t_content;

/*
**	push-swap params: p
*/

typedef struct	s_ps_prms
{
	t_list	*stack_a;
	t_list	*stack_b;
	int		len;
}				t_ps_prms;

long long	ps_atoi(const char *str);
int			sorting(t_ps_prms *p);

#endif
