/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_normalise_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:23:29 by uhand             #+#    #+#             */
/*   Updated: 2019/07/06 21:26:18 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	norm_swap(t_dllist **stack)
{
	t_dllist *second;

	second = stack[0]->right;
	stack[0]->left = second;
	stack[0]->right = NULL;
	second->right = stack[0];
	second->left = NULL;
	stack[0] = second;

}

void	check_bias(t_way *w)
{
	if (!w->direction)
		return ;
	if ((w->zero > 0 && w->bias < 0) || (w->zero < 0 && w->bias > 0) || \
		w->bias == 0)
	{
		w->direction = 0;
		return ;
	}
	if (w->zero == 0 || (ft_abs(w->zero) > ft_abs(w->bias)))
		w->zero = w->bias;
}

void	way_init(t_way *w, t_dllist *stack, int len)
{
	w->zero = 0;
	w->direction = 1;
	w->i = len;
	w->pos = 0;
	w->neg = 0;
	w->ptr = stack;
}

void	check_direction(t_way *w, int len)
{
	if (!w->direction)
		return ;
	if (w->neg == 0)
		w->pos -= ft_abs(w->zero * len);
	else
		w->neg -= ft_abs(w->zero * len);
}

int		check_stack_is_sorted(t_dllist *stack)
{
	t_dllist 	*ptr;
	t_content	*first;
	t_content	*second;

	if (!stack || !stack->right)
		return (0);
	ptr = stack;
	while (ptr->right)
	{
		first = stack->content;
		second = stack->right->content;
		if (first < second)
			return (0);
		ptr = ptr->right;
	}
	return (1);
}
