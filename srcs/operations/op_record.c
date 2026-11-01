/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_record.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/01 14:25:01 by amazloum      #+#    #+#                 */
/*   Updated: 2026/11/01 14:45:19 by amazloum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	grow(t_ps *ps)
{
	int	*bigger;
	int	i;

	ps->cap = ps->cap * 2 + 64;
	bigger = malloc(sizeof(int) * ps->cap);
	if (!bigger)
		ps_exit(ps, 1);
	i = -1;
	while (++i < ps->nops)
		bigger[i] = ps->ops[i];
	free(ps->ops);
	ps->ops = bigger;
}

void	op(t_ps *ps, int code)
{
	if ((code == PA && ps->b.size == 0) || (code == PB && ps->a.size == 0))
		return ;
	apply_op(ps, code);
	if (ps->nops == ps->cap)
		grow(ps);
	ps->ops[ps->nops] = code;
	ps->nops++;
}

static int	cancels(int x, int y)
{
	return ((x == PA && y == PB) || (x == PB && y == PA)
		|| (x == RA && y == RRA) || (x == RRA && y == RA)
		|| (x == RB && y == RRB) || (x == RRB && y == RB)
		|| (x == RR && y == RRR) || (x == RRR && y == RR)
		|| (x == SA && y == SA) || (x == SB && y == SB)
		|| (x == SS && y == SS));
}

static int	merged(int x, int y)
{
	if ((x == RA && y == RB) || (x == RB && y == RA))
		return (RR);
	if ((x == RRA && y == RRB) || (x == RRB && y == RRA))
		return (RRR);
	if ((x == SA && y == SB) || (x == SB && y == SA))
		return (SS);
	return (-1);
}

void	optimize_ops(t_ps *ps)
{
	int	i;
	int	n;
	int	m;

	n = 0;
	i = -1;
	while (++i < ps->nops)
	{
		m = -1;
		if (n > 0)
			m = merged(ps->ops[n - 1], ps->ops[i]);
		if (n > 0 && cancels(ps->ops[n - 1], ps->ops[i]))
			n--;
		else if (m >= 0)
			ps->ops[n - 1] = m;
		else
		{
			ps->ops[n] = ps->ops[i];
			n++;
		}
	}
	ps->nops = n;
}
