/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 18:19:18 by uhand             #+#    #+#             */
/*   Updated: 2019/07/02 12:23:15 by stepa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	set_sorted_position(t_dllist *stack)
{
	int			i;
	t_content	*c;

	i = 0;
	while (stack)
	{
		c = (t_content*)stack->content;
		c->sort_pos = i;
		stack = stack->right;
		i++;
	}
}

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

int		stack_sorting(t_ps_prms *p)
{
	t_shaker	s;

	if (p->len_a < 2)
		return (1);
	if (!(s.stack = copy_linked_stack(&p->stack_a, &s.stack)))
		return (0);
	s.left = s.stack;
	s.right = s.stack;
	while (s.right && s.right->right)
		s.right = s.right->right;
	shaker(&s);
	set_sorted_position(s.stack);
	/*while (s.stack)
	{
		s.a = (t_content*)s.stack->content;
		ft_printf("%5d	#%d	##%d\n", s.a->val, s.a->pos, s.a->sort_pos);
		s.stack = s.stack->right;
	}
	ft_printf("\n");*/
	ft_dlldeltoright(&s.stack, &linked_stack_free);
	return (1);
}
