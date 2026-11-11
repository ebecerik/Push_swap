/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_bench.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: elifbece <elifbece@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/10 13:14:57 by elifbece      #+#    #+#                 */
/*   Updated: 2026/11/11 13:22:45 by elifbece      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	put_disorder(t_ps *ps)
{
	long long	pct;

	pct = 0;
	if (ps->pairs > 0)
		pct = ps->mistakes * 10000 / ps->pairs;
	ft_putstr_fd("[bench] disorder: ", 2);
	ft_putnbr_fd(pct / 100, 2);
	ft_putstr_fd(".", 2);
	if (pct % 100 < 10)
		ft_putstr_fd("0", 2);
	ft_putnbr_fd(pct % 100, 2);
	ft_putstr_fd("%\n", 2);
}

static void	put_strategy(t_ps *ps)
{
	static char	*strats[4] = {"Adaptive", "Simple", "Medium", "Complex"};
	static char	*regimes[4] = {"O(n)", "O(n√n)", "O(n log n)", "O(n²)"};

	ft_putstr_fd("[bench] strategy: ", 2);
	ft_putstr_fd(strats[ps->strat], 2);
	ft_putstr_fd(" / ", 2);
	ft_putstr_fd(regimes[ps->regime], 2);
	ft_putstr_fd("\n", 2);
}

static void	put_counts(t_ps *ps)
{
	static char	*labels[11] = {"sa: ", "sb: ", "ss: ", "pa: ", "pb: ",
		"ra: ", "rb: ", "rr: ", "rra: ", "rrb: ", "rrr: "};
	int			counts[11];
	int			i;

	ft_bzero(counts, sizeof(counts));
	i = -1;
	while (++i < ps->nops)
		counts[ps->ops[i]]++;
	ft_putstr_fd("[bench] ", 2);
	i = -1;
	while (++i < 11)
	{
		ft_putstr_fd(labels[i], 2);
		ft_putnbr_fd(counts[i], 2);
		if (i < 10)
			ft_putstr_fd(" ", 2);
	}
	ft_putstr_fd("\n", 2);
}

void	print_bench(t_ps *ps)
{
	put_disorder(ps);
	put_strategy(ps);
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_fd(ps->nops, 2);
	ft_putstr_fd("\n", 2);
	put_counts(ps);
}
