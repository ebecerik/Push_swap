/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quick_move.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/01 17:23:41 by amazloum      #+#    #+#                 */
/*   Updated: 2026/11/05 11:30:56 by amazloum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	chunk_val(t_ps *ps, t_chunk *c, int k)
{
	if (c->loc == TOP_A)
		return (stack_at(&ps->a, k));
	if (c->loc == BOT_A)
		return (stack_at(&ps->a, ps->a.size - 1 - k));
	if (c->loc == TOP_B)
		return (stack_at(&ps->b, k));
	return (stack_at(&ps->b, ps->b.size - 1 - k));
}

static void	move_from_a(t_ps *ps, int from, int to)
{
	if (from == BOT_A)
		op(ps, RRA);
	if (from == TOP_A && to == BOT_A)
		op(ps, RA);
	if (to == TOP_B || to == BOT_B)
		op(ps, PB);
	if (to == BOT_B)
		op(ps, RB);
}

static void	move_from_b(t_ps *ps, int from, int to)
{
	if (from == BOT_B)
		op(ps, RRB);
	if (from == TOP_B && to == BOT_B)
		op(ps, RB);
	if (to == TOP_A || to == BOT_A)
		op(ps, PA);
	if (to == BOT_A)
		op(ps, RA);
}

void	move_elem(t_ps *ps, int from, int to)
{
	if (from == TOP_A || from == BOT_A)
		move_from_a(ps, from, to);
	else
		move_from_b(ps, from, to);
}
