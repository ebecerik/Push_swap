/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_sort.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: elifbece <elifbece@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/05 19:54:46 by elifbece      #+#    #+#                 */
/*   Updated: 2026/11/05 20:57:31 by elifbece      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_ps *ps)
{
	int	m;

	if (ps->a.size != 3)
		return ;
	m = pos_of_max(&ps->a);
	if (m == 0)
		op(ps, RA);
	else if (m == 1)
		op(ps, RRA);
	if (ps->a.top->val > ps->a.top->next->val)
		op(ps, SA);
}

void	simple_sort(t_ps *ps)
{
	int	min;

	if (ps->a.size < 2)
		return ;
	else if (ps->a.size == 2)
	{
		if (ps->a.top->val > ps->a.top->next->val)
			op(ps, SA);
		return ;
	}
	while (ps->a.size > 3)
	{
		min = pos_of_min(&ps->a);
		rotate_to(ps, 0, min);
		op(ps, PB);
	}
	sort_three(ps);
	while (ps->b.size > 0)
		op(ps, PA);
}
