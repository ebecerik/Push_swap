/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_ops.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elifbece <elifbece@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/10 13:14:37 by elifbece      #+#    #+#                 */
/*   Updated: 2026/11/11 13:23:03 by elifbece      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*op_name(int code)
{
	static char	*names[11] = {"sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr",
		"rra", "rrb", "rrr"};

	return (names[code]);
}

void	print_ops(t_ps *ps)
{
	int	i;

	i = -1;
	while (++i < ps->nops)
	{
		ft_putstr_fd(op_name(ps->ops[i]), 1);
		write(1, "\n", 1);
	}
}
