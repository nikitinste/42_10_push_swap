/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 18:19:18 by uhand             #+#    #+#             */
/*   Updated: 2019/06/23 19:53:36 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	set_previous(t_list	*lst)
{
	t_list		*prev;
	t_content	*c;

	prev = NULL;
	while (lst)
	{
		c = (t_content*)lst->content;
		c->prev = prev;
		prev = lst;
		lst = lst->next;
	}
}

static void	shake_to_right(t_shaker *s)
{
		while (s->tmp != s->right)
		{
			s->a = (t_content*)s->tmp->content;
			s->b = (t_content*)s->tmp->next->content;
			if (s->a->val > s->b->val)
				ft_lstswap(s->a->prev, s->tmp, s->b->prev, s->tmp->next);
			else
				s->tmp = s->tmp->next;
		}
}

static void	shake_to_left(t_shaker *s)
{
	while (s->tmp != s->left)
	{
		s->b = (t_content*)s->tmp->content;
		s->a = (t_content*)(s->b->prev->content);
		if (s->a->val > s->b->val)
			ft_lstswap(s->a->prev, s->b->prev, s->b->prev, s->tmp);

		s->tmp = s->tmp->next;
	}
}

static void	shaker(t_shaker *s)
{
	while (s->left != s->right || s->right != s->c_l->prev)
	{
		s->tmp = s->left;
		shake_to_right(s);
		s->right = s->c_r->prev;
		s->c_r = (t_content*)s->right->content;
		s->tmp = s->right;
		shake_to_left(s);
		s->left = s->left->next;
		s->c_l = (t_content*)s->left->content;
	}
}

int		sorting(t_ps_prms *p)
{
	t_shaker	s;

	set_previous(p->stack_a);
	if (!(s.stack = (t_list**)malloc(sizeof(t_list*))) \
		|| !(s.stack[0] = ft_lstcpy(p->stack_a, s.stack[0])))
		return (0);
	s.left = s.stack[0];
	s.c_l = (t_content*)s.left->content;
	s.right = s.stack[0];
	while (s.right->next)
		s.right = s.right->next;
	s.c_r = (t_content*)s.right->content;
	shaker(&s);
	while (s.stack)
	{
		s.c_l = (t_content*)s.stack[0]->content;
		ft_printf("%d	#%d\n", s.c_l->val, s.c_l->pos);
		s.stack[0] = s.stack[0]->next;
	}
	return (1);
}
