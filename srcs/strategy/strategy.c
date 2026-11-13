/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strategy.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/01 14:47:08 by amazloum      #+#    #+#                 */
/*   Updated: 2026/11/13 18:15:41 by elifbece      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *s)
{
	t_node	*n;

	n = s->top;
	while (n && n->next)
	{
		if (n->val > n->next->val)
			return (0);
		n = n->next;
	}
	return (1);
}

void	compute_disorder(t_ps *ps)
{
	t_node	*i;
	t_node	*j;

	ps->mistakes = 0;
	ps->pairs = 0;
	i = ps->a.top;
	while (i)
	{
		j = i->next;
		while (j)
		{
			ps->pairs++;
			if (i->val > j->val)
				ps->mistakes++;
			j = j->next;
		}
		i = i->next;
	}
}

static void	set_regime(t_ps *ps)
{
	if (ps->strat == SIMPLE)
		ps->regime = R_N2;
	else if (ps->strat == MEDIUM)
		ps->regime = R_NSQRT;
	else if (ps->strat == COMPLEX)
		ps->regime = R_NLOGN;
	else if (ps->pairs == 0 || ps->mistakes * 5 < ps->pairs)
		ps->regime = R_N;
	else if (ps->mistakes * 2 < ps->pairs)
		ps->regime = R_NSQRT;
	else
		ps->regime = R_NLOGN;
}

void	run_strategy(t_ps *ps)
{
	set_regime(ps);
	if (is_sorted(&ps->a))
		return ;
	if (ps->strat == ADAPTIVE && ps->a.size <= 6)
		ps->regime = R_N2;
	if (ps->regime == R_N2)
		simple_sort(ps);
	else if (ps->regime == R_N)
		adaptive_low(ps);
	else if (ps->regime == R_NSQRT)
		chunk_sort(ps);
	else
		quick_sort(ps);
}
