/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quick_sort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/01 17:32:18 by amazloum      #+#    #+#                 */
/*   Updated: 2026/11/01 17:35:53 by amazloum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	set_dests(int loc, t_chunk *d)
{
	d[0].size = 0;
	d[1].size = 0;
	d[2].size = 0;
	d[0].loc = TOP_A;
	d[1].loc = BOT_A;
	d[2].loc = BOT_B;
	if (loc == TOP_A)
	{
		d[0].loc = BOT_A;
		d[1].loc = TOP_B;
	}
	else if (loc == BOT_A)
		d[1].loc = TOP_B;
	else if (loc == BOT_B)
		d[2].loc = TOP_B;
}

static int	chunk_min(t_ps *ps, t_chunk *c)
{
	int	k;
	int	lo;
	int	v;

	lo = chunk_val(ps, c, 0);
	k = 0;
	while (++k < c->size)
	{
		v = chunk_val(ps, c, k);
		if (v < lo)
			lo = v;
	}
	return (lo);
}

static void	split(t_ps *ps, t_chunk *c, t_chunk *d)
{
	int	p1;
	int	p2;
	int	v;
	int	part;

	p1 = chunk_min(ps, c) + c->size / 3;
	p2 = chunk_min(ps, c) + (c->size * 2) / 3;
	set_dests(c->loc, d);
	while (c->size-- > 0)
	{
		v = chunk_val(ps, c, 0);
		part = 2;
		if (v >= p2)
			part = 0;
		else if (v >= p1)
			part = 1;
		move_elem(ps, c->loc, d[part].loc);
		d[part].size++;
	}
}

static void	rec_sort(t_ps *ps, t_chunk c)
{
	t_chunk	d[3];

	if (c.loc == BOT_A && c.size == ps->a.size)
		c.loc = TOP_A;
	if (c.loc == BOT_B && c.size == ps->b.size)
		c.loc = TOP_B;
	if (c.size <= 3)
	{
		sort_small_chunk(ps, &c);
		return ;
	}
	split(ps, &c, d);
	rec_sort(ps, d[0]);
	rec_sort(ps, d[1]);
	rec_sort(ps, d[2]);
}

void	quick_sort(t_ps *ps)
{
	t_chunk	c;

	c.loc = TOP_A;
	c.size = ps->a.size;
	rec_sort(ps, c);
}
