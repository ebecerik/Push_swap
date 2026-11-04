/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   adaptive_insert.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/01 17:30:52 by amazloum      #+#    #+#                 */
/*   Updated: 2026/11/04 11:42:34 by amazloum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	target_in_a(t_stack *a, int x)
{
	t_node	*n;
	int		i;
	int		best;
	int		best_val;

	n = a->top;
	i = 0;
	best = -1;
	best_val = INT_MAX;
	while (n)
	{
		if (n->val > x && n->val < best_val)
		{
			best = i;
			best_val = n->val;
		}
		n = n->next;
		i++;
	}
	if (best < 0)
		best = pos_of_min(a);
	return (best);
}

static int	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

static void	pick(t_move *m, int ra, int rb, int total)
{
	if (total < m->total)
	{
		m->ra = ra;
		m->rb = rb;
		m->total = total;
	}
}

static t_move	cost_of(t_ps *ps, int j, int x)
{
	t_move	m;
	int		t;
	int		da;
	int		db;

	t = target_in_a(&ps->a, x);
	da = (ps->a.size - t) % ps->a.size;
	db = (ps->b.size - j) % ps->b.size;
	m.total = INT_MAX;
	pick(&m, t, j, ft_max(t, j));
	pick(&m, -da, -db, ft_max(da, db));
	pick(&m, t, -db, t + db);
	pick(&m, -da, j, da + j);
	return (m);
}

void	insert_back(t_ps *ps)
{
	t_move	best;
	t_move	m;
	t_node	*n;
	int		j;

	while (ps->b.size > 0)
	{
		best.total = INT_MAX;
		n = ps->b.top;
		j = 0;
		while (n)
		{
			m = cost_of(ps, j, n->val);
			if (m.total < best.total)
				best = m;
			n = n->next;
			j++;
		}
		exec_move(ps, best);
	}
}
