/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_numbers.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: elifbece <elifbece@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/02 17:11:42 by elifbece      #+#    #+#                 */
/*   Updated: 2026/11/03 20:30:27 by elifbece      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	parse_sign(char **p)
{
	int	neg;

	neg = 0;
	if (**p == '+' || **p == '-')
	{
		if (**p == '-')
			neg = 1;
		(*p)++;
	}
	return (neg);
}

static int	parse_digits(char **p, long long *out, int neg)
{
	long long	n;
	long long	limit;

	n = 0;
	if (neg)
		limit = (long long)INT_MAX + 1;
	else
		limit = INT_MAX;
	if (**p < '0' || **p > '9')
		return (0);
	while (**p >= '0' && **p <= '9')
	{
		n = n * 10 + (**p - '0');
		if (n > limit)
			return (0);
		(*p)++;
	}
	if (neg)
		*out = -n;
	else
		*out = n;
	return (1);
}

static int	parse_one(char **p, long long *out)
{
	int	neg;

	neg = parse_sign(p);
	if (!parse_digits(p, out, neg))
		return (0);
	if (**p && !is_space(**p))
		return (0);
	return (1);
}

void	read_numbers(t_ps *ps, char *s)
{
	long long	val;
	t_node		*n;

	while (*s)
	{
		while (is_space(*s))
			s++;
		if (!*s)
			break ;
		if (!parse_one(&s, &val))
			ps_exit(ps, 1);
		n = node_new((int)val);
		if (!n)
			ps_exit(ps, 1);
		stack_add_bottom(&ps->a, n);
	}
}
