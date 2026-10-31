/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/31 12:16:19 by amazloum      #+#    #+#                 */
/*   Updated: 2026/10/31 12:39:53 by amazloum      ########   odam.nl         */
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

int	main(int argc, char **argv)
{
	t_ps	ps;

	ft_bzero(&ps, sizeof(t_ps));
	parse_args(&ps, argc, argv);
	if (ps.a.size == 0)
		ps_exit(&ps, 0);
	index_ranks(&ps);
	compute_disorder(&ps);
	run_strategy(&ps);
	optimize_ops(&ps);
	print_ops(&ps);
	if (ps.bench)
		print_bench(&ps);
	ps_exit(&ps, 0);
	return (0);
}
