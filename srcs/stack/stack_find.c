/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack_find.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: elifbece <elifbece@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/05 14:52:22 by elifbece      #+#    #+#                 */
/*   Updated: 2026/11/05 19:50:31 by elifbece      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	pos_of_min(t_stack *s)
{
	t_node	*n;
	int		i;
	int		best_i;
	int		best_val;

	if (!s->top)
		return (0);
	n = s->top;
	i = 0;
	best_i = 0;
	best_val = n->val;
	while (n)
	{
		if (n->val < best_val)
		{
			best_val = n->val;
			best_i = i;
		}
		n = n->next;
		i++;
	}
	return (best_i);
}

int	pos_of_max(t_stack *s)
{
	t_node	*n;
	int		i;
	int		max_i;
	int		max_val;

	if (!s->top)
		return (-1);
	n = s->top;
	i = 0;
	max_i = 0;
	max_val = n->val;
	while (n)
	{
		if (n->val > max_val)
		{
			max_val = n->val;
			max_i = i;
		}
		n = n->next;
		i++;
	}
	return (max_i);
}

int	pos_of_val(t_stack *s, int v)
{
	t_node	*n;
	int		i;

	if (!s->top)
		return (-1);
	n = s->top;
	i = 0;
	while (n)
	{
		if (n->val == v)
			return (i);
		n = n->next;
		i++;
	}
	return (-1);
}

int	rot_cost(t_stack *s, int idx)
{
	int	back;

	back = s->size - idx;
	if (idx < back)
		return (idx);
	return (back);
}

void	rotate_to(t_ps *ps, int which, int idx)
{
	t_stack	*s;
	int		code;
	int		cost;

	s = &ps->a;
	if (which)
		s = &ps->b;
	cost = rot_cost(s, idx);
	code = RRA + which;
	if (cost == idx)
		code = RA + which;
	while (cost-- > 0)
		op(ps, code);
}
