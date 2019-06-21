/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:58:36 by uhand             #+#    #+#             */
/*   Updated: 2019/06/21 18:21:38 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

/*
**	push-swap params: c
*/

typedef struct	s_content
{
	int		val;
	int		pos;
	int		shift;
}				t_content;

/*
**	push-swap params: p
*/

typedef struct	s_ps_prms
{
	t_list		*stack_a;
	t_list		*stack_b;
	int			len;
}				t_ps_prms;

long long	ps_atoi(const char *str);
void		sorting(t_ps_prms *p);

#endif
