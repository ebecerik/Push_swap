/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker_exit_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/12 12:15:28 by amazloum      #+#    #+#                 */
/*   Updated: 2026/11/13 10:55:59 by amazloum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_exit(t_ps *ps, int err)
{
	stack_clear(&ps->a);
	stack_clear(&ps->b);
	free(ps->ops);
	if (err)
		write(2, "Error\n", 6);
	exit(err);
}
