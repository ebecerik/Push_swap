/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/12 12:15:31 by amazloum      #+#    #+#                 */
/*   Updated: 2026/11/13 10:56:02 by amazloum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	op_code(char *s)
{
	char	*names[11];
	int		i;

	names[0] = "sa";
	names[1] = "sb";
	names[2] = "ss";
	names[3] = "pa";
	names[4] = "pb";
	names[5] = "ra";
	names[6] = "rb";
	names[7] = "rr";
	names[8] = "rra";
	names[9] = "rrb";
	names[10] = "rrr";
	i = -1;
	while (++i < 11)
		if (ft_strcmp(s, names[i]) == 0)
			return (i);
	return (-1);
}

static int	read_line(char *buf)
{
	int		len;
	int		r;
	char	c;

	len = 0;
	r = read(0, &c, 1);
	while (r == 1 && c != '\n')
	{
		if (len == 3)
			return (-1);
		buf[len++] = c;
		r = read(0, &c, 1);
	}
	buf[len] = '\0';
	if (r < 0 || (r == 0 && len > 0))
		return (-1);
	return (r == 1);
}

static void	run_ops(t_ps *ps)
{
	char	buf[4];
	int		r;
	int		code;

	r = read_line(buf);
	while (r == 1)
	{
		code = op_code(buf);
		if (code < 0)
			ps_exit(ps, 1);
		apply_op(ps, code);
		r = read_line(buf);
	}
	if (r < 0)
		ps_exit(ps, 1);
}

static int	is_done(t_ps *ps)
{
	t_node	*n;

	if (ps->b.size != 0)
		return (0);
	n = ps->a.top;
	while (n && n->next)
	{
		if (n->val > n->next->val)
			return (0);
		n = n->next;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_ps	ps;

	ft_bzero(&ps, sizeof(t_ps));
	parse_args(&ps, argc, argv);
	if (ps.a.size == 0)
		ps_exit(&ps, 0);
	index_ranks(&ps);
	run_ops(&ps);
	if (is_done(&ps))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	ps_exit(&ps, 0);
	return (0);
}
