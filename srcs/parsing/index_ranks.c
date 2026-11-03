/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index_ranks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: elifbece <elifbece@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/02 17:39:16 by elifbece      #+#    #+#                 */
/*   Updated: 2026/11/03 20:30:47 by elifbece      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*collect_vals(t_ps *ps)
{
	int		*vals;
	t_node	*n;
	int		i;

	vals = malloc(sizeof(int) * ps->a.size);
	if (!vals)
		ps_exit(ps, 1);
	n = ps->a.top;
	i = 0;
	while (n)
	{
		vals[i++] = n->val;
		n = n->next;
	}
	return (vals);
}

static int	has_duplicates(t_ps *ps, int *vals)
{
	int	i;
	int	j;

	i = -1;
	while (++i < ps->a.size)
	{
		j = i;
		while (++j < ps->a.size)
			if (vals[i] == vals[j])
				return (1);
	}
	return (0);
}

static int	rank_of(int *vals, int n, int i)
{
	int	rank;
	int	j;

	rank = 0;
	j = -1;
	while (++j < n)
		if (vals[j] < vals[i])
			rank++;
	return (rank);
}

void	index_ranks(t_ps *ps)
{
	int		*vals;
	t_node	*n;
	int		i;

	if (ps->a.size < 2)
		return ;
	vals = collect_vals(ps);
	if (has_duplicates(ps, vals))
	{
		free(vals);
		ps_exit(ps, 1);
	}
	n = ps->a.top;
	i = 0;
	while (n)
	{
		n->val = rank_of(vals, ps->a.size, i);
		n = n->next;
		i++;
	}
	free(vals);
}
