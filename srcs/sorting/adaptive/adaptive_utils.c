/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   adaptive_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/01 17:36:59 by amazloum      #+#    #+#                 */
/*   Updated: 2026/11/01 17:38:07 by amazloum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	lower_bound(int *s, int *tail, int len, int x)
{
	int	lo;
	int	hi;
	int	mid;

	lo = 0;
	hi = len;
	while (lo < hi)
	{
		mid = (lo + hi) / 2;
		if (s[tail[mid]] < x)
			lo = mid + 1;
		else
			hi = mid;
	}
	return (lo);
}

int	count_unkept(int *keep, int n)
{
	int	left;
	int	k;

	left = 0;
	k = -1;
	while (++k < n)
	{
		if (!keep[k])
			left++;
	}
	return (left);
}

int	unkept_dist(t_stack *a, int *keep, int from_top)
{
	t_node	*n;
	int		dist;

	n = a->bot;
	if (from_top)
		n = a->top;
	dist = 0;
	while (keep[n->val])
	{
		if (from_top)
			n = n->next;
		else
			n = n->prev;
		dist++;
	}
	return (dist);
}

static void	repeat(t_ps *ps, int code, int times)
{
	while (times-- > 0)
		op(ps, code);
}

void	exec_move(t_ps *ps, t_move m)
{
	while (m.ra > 0 && m.rb > 0)
	{
		op(ps, RR);
		m.ra--;
		m.rb--;
	}
	while (m.ra < 0 && m.rb < 0)
	{
		op(ps, RRR);
		m.ra++;
		m.rb++;
	}
	repeat(ps, RA, m.ra);
	repeat(ps, RRA, -m.ra);
	repeat(ps, RB, m.rb);
	repeat(ps, RRB, -m.rb);
	op(ps, PA);
}
