/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_normalise.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 18:22:36 by uhand             #+#    #+#             */
/*   Updated: 2019/07/12 17:46:44 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_dllist **stack)
{
	t_dllist	*last;
	t_dllist	*tmp;

	if (stack[0]->right)
		if (!stack[0]->right->right)
		{
			norm_swap(stack);
			return ;
		}
	last = stack[0];
	while (last->right)
		last = last->right;
	tmp = stack[0]->right;
	tmp->left = NULL;
	stack[0]->right = NULL;
	stack[0]->left = last;
	last->right = stack[0];
	stack[0] = tmp;
}

static void	find_norm_way_a(t_ps_prms *p, t_dllist *stack, int *way)
{
	t_way	w;

	w.rot = 0;
	w.min = -1;
	while (w.rot < p->len_a)
	{
		way_init(&w, stack, p->len_b);
		while (w.ptr)
		{
			w.c = (t_content*)w.ptr->content;
			w.bias = w.i - w.c->sort_pos;
			check_bias(&w);
			if (w.bias < 0)
				w.neg += ft_abs(w.bias);
			else
				w.pos += w.bias;
			w.i++;
			w.ptr = w.ptr->right;
		}
		set_way_params(&w, way, p->len_a);
		rotate(&stack);
		w.rot++;
	}
	/*ft_printf("\nway a: %d \n", *way);*///<--
}

static void	find_norm_way_b(t_ps_prms *p, t_dllist *stack, int *way)
{
	t_way	w;
	//t_dllist	*ptr;
	//t_content	*c;


	/*ptr = p->stack_a;
	ft_printf("1 len_a: %d\n", p->len_a);
	while (ptr)
	{
		c = (t_content*)ptr->content;
		ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
			c->pos - c->sort_pos);
		ptr = ptr->right;
	}
	ft_printf("\n\n");
	ptr = p->stack_b;
	ft_printf("1 len_b: %d\n", p->len_b);
	while (ptr)
	{
		c = (t_content*)ptr->content;
		ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
			c->pos - c->sort_pos);
		ptr = ptr->right;
	}
	ft_printf("\n");*/

	w.rot = 0;
	w.min = -1;
	while (w.rot < p->len_b)
	{
		way_init(&w, stack, (p->len_b - 1));
		while (w.ptr)
		{
			w.c = (t_content*)w.ptr->content;
			w.bias = w.i - w.c->sort_pos;
			check_bias(&w);
			if (w.bias < 0)
				w.neg += ft_abs(w.bias);
			else
				w.pos += w.bias;
			w.i--;
			w.ptr = w.ptr->right;
		}
		//ft_printf("\n");
		set_way_params(&w, way, p->len_b);
		//ft_printf("\n");
		rotate(&stack);

		/*ptr = p->stack_a;
		ft_printf("4 len_a: %d\n", p->len_a);
		while (ptr)
		{
			c = (t_content*)ptr->content;
			ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
				c->pos - c->sort_pos);
			ptr = ptr->right;
		}
		ft_printf("\n\n");
		ptr = p->stack_b;
		ft_printf("4 len_b: %d\n", p->len_b);
		while (ptr)
		{
			c = (t_content*)ptr->content;
			ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
				c->pos - c->sort_pos);
			ptr = ptr->right;
		}
		ft_printf("\n");*/


		w.rot++;
	}
	/*ft_printf("\nway b: %d \n", *way);*///<--
}

static void	get_conclusion(t_ps_prms *p, t_normalise *n)
{
	int		way_len;

	if ((n->way_a > 0 && n->way_b < 0) || (n->way_a < 0 && n->way_b > 0))
	{
		way_len = ft_abs(n->way_a) + ft_abs(n->way_b);
		n->rev_a = n->way_a - p->len_a;
		n->rev_b = n->way_b - p->len_b;
		if (way_len > ft_abs(n->way_a - n->rev_b) \
			|| way_len > ft_abs(n->way_b - n->rev_a))
			way_shortening(n);
		/*ft_printf("\nway ab: %d \tway a: %d \tway b: %d \t\n", \
			n->way_ab, n->way_a, n->way_b);*///<--
		return ;
	}
	if (ft_abs(n->way_a) > ft_abs(n->way_b))
	{
		n->way_ab = n->way_b;
		n->way_a -= n->way_b;
		n->way_b = 0;
		/*ft_printf("\nway ab: %d \tway a: %d \tway b: %d \t\n", \
			n->way_ab, n->way_a, n->way_b);*///<--
		return ;
	}
	n->way_ab = n->way_a;
	n->way_b -= n->way_a;
	n->way_a = 0;
	/*ft_printf("\nway ab: %d \tway a: %d \tway b: %d \t\n", \
		n->way_ab, n->way_a, n->way_b);*///<--
}

int			normalise(t_ps_prms *p, t_cmd_gen *g)
{
	t_normalise	n;

	//t_dllist	*ptr;
	//t_content	*c;

	/*ptr = p->stack_a;
	ft_printf("1 len_a: %d\n", p->len_a);
	while (ptr)
	{
		c = (t_content*)ptr->content;
		ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
			c->pos - c->sort_pos);
		ptr = ptr->right;
	}
	ft_printf("\n\n");
	ptr = p->stack_b;
	ft_printf("1 len_b: %d\n", p->len_b);
	while (ptr)
	{
		c = (t_content*)ptr->content;
		ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
			c->pos - c->sort_pos);
		ptr = ptr->right;
	}
	ft_printf("\n");*/

	if (p->stack_a && p->len_a > 1)
	{
		if(!(n.stack_a = copy_linked_stack(&p->stack_a, &n.stack_a)))
			exit (0);
	}
	else
		n.stack_a = NULL;
	if (p->stack_b && p->len_b > 1)
	{
		if(!(n.stack_b = copy_linked_stack(&p->stack_b, &n.stack_b)))
			exit (0);
	}
	else
		n.stack_b = NULL;
	n.way_a = 0;
	n.way_b = 0;
	n.way_ab = 0;
	if (n.stack_a)
		find_norm_way_a(p, n.stack_a, &n.way_a);

	/*ptr = p->stack_a;
	ft_printf("2 len_a: %d\n", p->len_a);
	while (ptr)
	{
		c = (t_content*)ptr->content;
		ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
			c->pos - c->sort_pos);
		ptr = ptr->right;
	}
	ft_printf("\n\n");
	ptr = p->stack_b;
	ft_printf("2 len_b: %d\n", p->len_b);
	while (ptr)
	{
		c = (t_content*)ptr->content;
		ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
			c->pos - c->sort_pos);
		ptr = ptr->right;
	}
	ft_printf("\n");*/

	if (n.stack_b)
		find_norm_way_b(p, n.stack_b, &n.way_b);

	/*ptr = p->stack_a;
	ft_printf("3 len_a: %d\n", p->len_a);
	while (ptr)
	{
		c = (t_content*)ptr->content;
		ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
			c->pos - c->sort_pos);
		ptr = ptr->right;
	}
	ft_printf("\n\n");
	ptr = p->stack_b;
	ft_printf("3 len_b: %d\n", p->len_b);
	while (ptr)
	{
		c = (t_content*)ptr->content;
		ft_printf("%5d	#%d	##%d	%3d\n", c->val, c->pos, c->sort_pos, \
			c->pos - c->sort_pos);
		ptr = ptr->right;
	}
	ft_printf("\n");*/

	get_conclusion(p, &n);
	run_commands(p, g, &n);
	return (1);
}

int			normalise_b(t_ps_prms *p, t_cmd_gen *g, int ret)
{
	t_normalise	n;

	n.stack_a = NULL;
	if (p->stack_b && p->len_b > 1)
	{
		if(!(n.stack_b = copy_linked_stack(&p->stack_b, &n.stack_b)))
			exit (0);
	}
	else
		n.stack_b = NULL;
	n.way_a = 0;
	n.way_b = 0;
	n.way_ab = 0;
	if (n.stack_b)
		find_norm_way_b(p, n.stack_b, &n.way_b);
	if (!ret)
		run_commands(p, g, &n);
	else
	{
		ft_dlldeltoright(&n.stack_b, &linked_stack_free);
		return (n.way_b);
	}
	return (1);
}
