/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operations.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: elifbece <elifbece@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/03 20:34:50 by elifbece      #+#    #+#                 */
/*   Updated: 2026/11/03 20:40:31 by elifbece      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	do_swap(t_stack *s)
{
	t_node	*first;
	t_node	*second;

	if (s->size < 2)
		return ;
	first = stack_pop_top(s);
	second = stack_pop_top(s);
	stack_push_top(s, first);
	stack_push_top(s, second);
}

static void	do_push(t_stack *src, t_stack *dst)
{
	t_node	*n;

	if (src->size == 0)
		return ;
	n = stack_pop_top(src);
	stack_push_top(dst, n);
}

static void	do_rotate(t_stack *s)
{
	t_node	*n;

	if (s->size < 2)
		return ;
	n = stack_pop_top(s);
	stack_add_bottom(s, n);
}

static void	do_rrotate(t_stack *s)
{
	t_node	*n;

	if (s->size < 2)
		return ;
	n = stack_pop_bottom(s);
	stack_push_top(s, n);
}

void	apply_op(t_ps *ps, int code)
{
	if (code == SA || code == SS)
		do_swap(&ps->a);
	if (code == SB || code == SS)
		do_swap(&ps->b);
	if (code == PA)
		do_push(&ps->b, &ps->a);
	if (code == PB)
		do_push(&ps->a, &ps->b);
	if (code == RA || code == RR)
		do_rotate(&ps->a);
	if (code == RB || code == RR)
		do_rotate(&ps->b);
	if (code == RRA || code == RRR)
		do_rrotate(&ps->a);
	if (code == RRB || code == RRR)
		do_rrotate(&ps->b);
}
