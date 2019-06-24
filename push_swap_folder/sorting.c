/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 18:19:18 by uhand             #+#    #+#             */
/*   Updated: 2019/06/24 19:25:18 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	shake_to_right(t_shaker *s)
{
	while (s->tmp != s->right)
	{
		s->a = (t_content*)s->tmp->content;
		s->b = (t_content*)s->tmp->right->content;
		if (s->a->val > s->b->val)
			ft_dllswap(s->tmp, s->tmp->right);
		s->tmp = s->tmp->right;
	}
}

static void	shake_to_left(t_shaker *s)
{
	while (s->tmp != s->left)
	{
		s->a = (t_content*)s->tmp->content;
		s->b = (t_content*)s->tmp->left->content;
		if (s->a->val < s->b->val)
			ft_dllswap(s->tmp, s->tmp->left);
		s->tmp = s->tmp->left;
	}
}

static void	shaker(t_shaker *s)
{
	while (s->left != s->right && s->right != s->left->left)
	{
		s->tmp = s->left;
		shake_to_right(s);
		s->right = s->right->left;
		s->tmp = s->right;
		shake_to_left(s);
		s->left = s->left->right;
	}
}

int		sorting(t_ps_prms *p)
{
	t_shaker	s;

	if (!(s.stack = ft_dllcpyr(p->stack_a, s.stack)))
		return (0);
	s.left = s.stack;
	s.right = s.stack;
	while (s.right->right)
		s.right = s.right->right;
	shaker(&s);
	while (s.stack)
	{
		s.a = (t_content*)s.stack->content;
		ft_printf("%d	#%d\n", s.a->val, s.a->pos);
		s.stack = s.stack->right;
	}
	return (1);
}
