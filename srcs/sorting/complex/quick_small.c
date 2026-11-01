/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quick_small.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/01 17:26:41 by amazloum      #+#    #+#                 */
/*   Updated: 2026/11/01 17:35:44 by amazloum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_top_three(t_ps *ps)
{
	t_node	*t;

	t = ps->a.top;
	while (!(t->val < t->next->val && t->next->val < t->next->next->val))
	{
		if (t->val > t->next->val)
			op(ps, SA);
		else
		{
			op(ps, PB);
			op(ps, SA);
			op(ps, PA);
		}
		t = ps->a.top;
	}
}

void	sort_small_chunk(t_ps *ps, t_chunk *c)
{
	int	k;

	if (c->loc == TOP_A && c->size == 3 && ps->a.size == 3)
	{
		sort_three(ps);
		return ;
	}
	k = c->size;
	while (k-- > 0)
		move_elem(ps, c->loc, TOP_A);
	if (c->size == 3)
		sort_top_three(ps);
	else if (c->size == 2 && ps->a.top->val > ps->a.top->next->val)
		op(ps, SA);
}
