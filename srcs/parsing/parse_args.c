/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: elifbece <elifbece@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/02 16:34:05 by elifbece      #+#    #+#                 */
/*   Updated: 2026/11/02 16:39:25 by elifbece      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_long_flag(char *s)
{
	return (s[0] == '-' && s[1] == '-');
}

static int	is_blank(char *s)
{
	int	i;

	i = 0;
	if (!s[0])
		return (1);
	while (s[i])
	{
		if (!is_space(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	set_strat(t_ps *ps, int code)
{
	if (ps->strat_set && ps->strat != code)
		ps_exit(ps, 1);
	ps->strat = code;
	ps->strat_set = 1;
}

static void	handle_flag(t_ps *ps, char *s)
{
	if (ft_strcmp(s, "--simple") == 0)
		set_strat(ps, SIMPLE);
	else if (ft_strcmp(s, "--medium") == 0)
		set_strat(ps, MEDIUM);
	else if (ft_strcmp(s, "--complex") == 0)
		set_strat(ps, COMPLEX);
	else if (ft_strcmp(s, "--adaptive") == 0)
		set_strat(ps, ADAPTIVE);
	else if (ft_strcmp(s, "--bench") == 0)
		ps->bench = 1;
	else
		ps_exit(ps, 1);
}

void	parse_args(t_ps *ps, int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (is_long_flag(argv[i]))
			handle_flag(ps, argv[i]);
		else if (is_blank(argv[i]))
			ps_exit(ps, 1);
	}
	i = 0;
	while (++i < argc)
		if (!is_long_flag(argv[i]))
			read_numbers(ps, argv[i]);
}
