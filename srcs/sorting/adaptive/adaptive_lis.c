/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   adaptive_lis.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/04 11:47:56 by amazloum      #+#    #+#                 */
/*   Updated: 2026/11/05 11:30:46 by amazloum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	mark_path(int *s, int *prev, int k, int *keep)
{
	while (k >= 0)
	{
		keep[s[k]] = 1;
		k = prev[k];
	}
}

static void	build_lis(int *s, int n, int *keep)
{
	int	*tail;
	int	*prev;
	int	len;
	int	k;
	int	j;

	tail = s + n;
	prev = s + n * 2;
	len = 0;
	k = -1;
	while (++k < n)
	{
		j = lower_bound(s, tail, len, s[k]);
		prev[k] = -1;
		if (j > 0)
			prev[k] = tail[j - 1];
		tail[j] = k;
		if (j == len)
			len++;
	}
	mark_path(s, prev, tail[len - 1], keep);
}

static int	mark_lis(t_ps *ps, int *keep)
{
	t_node	*node;
	int		*s;
	int		n;
	int		k;

	n = ps->a.size;
	s = malloc(sizeof(int) * n * 3);
	if (!s)
		return (-1);
	node = ps->a.top;
	while (node->val != 0)
		node = node->next;
	k = -1;
	while (++k < n)
	{
		s[k] = node->val;
		node = node->next;
		if (!node)
			node = ps->a.top;
	}
	build_lis(s, n, keep);
	free(s);
	return (count_unkept(keep, n));
}

static void	push_unkept(t_ps *ps, int *keep, int left)
{
	int	up;
	int	down;

	while (left > 0)
	{
		up = unkept_dist(&ps->a, keep, 1);
		down = unkept_dist(&ps->a, keep, 0);
		if (down + 1 < up)
			rotate_to(ps, 0, ps->a.size - 1 - down);
		else
			rotate_to(ps, 0, up);
		op(ps, PB);
		left--;
	}
}

void	adaptive_low(t_ps *ps)
{
	int	*keep;
	int	left;

	keep = malloc(sizeof(int) * ps->a.size);
	if (!keep)
		ps_exit(ps, 1);
	ft_bzero(keep, sizeof(int) * ps->a.size);
	left = mark_lis(ps, keep);
	if (left < 0)
	{
		free(keep);
		ps_exit(ps, 1);
	}
	push_unkept(ps, keep, left);
	free(keep);
	insert_back(ps);
	rotate_to(ps, 0, pos_of_min(&ps->a));
}
