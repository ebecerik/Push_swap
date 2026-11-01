/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chunk_sort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/01 16:13:20 by amazloum      #+#    #+#                 */
/*   Updated: 2026/11/01 16:25:21 by amazloum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	chunk_range(int n)
{
	int	r;

	r = 1;
	while (r * r < n)
		r++;
	return (r * 13 / 10);
}

static void	push_chunks(t_ps *ps, int range)
{
	int	i;

	i = 0;
	while (ps->a.size > 0)
	{
		if (ps->a.top->val <= i)
		{
			op(ps, PB);
			if (ps->b.size > 1)
				op(ps, RB);
			i++;
		}
		else if (ps->a.top->val <= 1 + range)
		{
			op(ps, PB);
			i++;
		}
		else
			op(ps, RA);
	}
}

static void	pull_two(t_ps *ps, int m)
{
	rotate_to(ps, 1, pos_of_val(&ps->b, m - 1));
	op(ps, PA);
	rotate_to(ps, 1, pos_of_val(&ps->b, m));
	op(ps, PA);
	op(ps, SA);
}

static void	pull_back(t_ps *ps)
{
	int	m;
	int	p1;
	int	p2;

	while (ps->b.size > 0)
	{
		m = ps->b.size - 1;
		p1 = pos_of_val(&ps->b, m);
		p2 = pos_of_val(&ps->b, m - 1);
		if (p2 >= 0 && rot_cost(&ps->b, p2) < rot_cost(&ps->b, p1))
			pull_two(ps, m);
		else
		{
			rotate_to(ps, 1, p1);
			op(ps, PA);
		}
	}
}

void	chunk_sort(t_ps *ps)
{
	push_chunks(ps, chunk_range(ps->a.size));
	pull_back(ps);
}
