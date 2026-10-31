/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/30 11:52:28 by amazloum      #+#    #+#                 */
/*   Updated: 2026/10/31 12:39:32 by amazloum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define SA 0
# define SB 1
# define SS 2
# define PA 3
# define PB 4
# define RA 5
# define RB 6
# define RR 7
# define RRA 8
# define RRB 9
# define RRR 10

# define ADAPTIVE 0
# define SIMPLE 1
# define MEDIUM 2
# define COMPLEX 3

# define R_N 0
# define R_NSQRT 1
# define R_NLOGN 2
# define R_N2 3

# define TOP_A 0
# define BOT_A 1
# define TOP_B 2
# define BOT_B 3

typedef struct s_node
{
	int				val;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	t_node	*bot;
	int		size;
}	t_stack;

typedef struct s_ps
{
	t_stack		a;
	t_stack		b;
	int			*ops;
	int			nops;
	int			cap;
	int			strat;
	int			strat_set;
	int			bench;
	int			regime;
	long long	mistakes;
	long long	pairs;
}	t_ps;

typedef struct s_chunk
{
	int	loc;
	int	size;
}	t_chunk;

typedef struct s_move
{
	int	ra;
	int	rb;
	int	total;
}	t_move;

t_node	*node_new(int val);
void	stack_add_bottom(t_stack *s, t_node *n);
void	stack_push_top(t_stack *s, t_node *n);
t_node	*stack_pop_top(t_stack *s);
t_node	*stack_pop_bottom(t_stack *s);
void	stack_clear(t_stack *s);
int		stack_at(t_stack *s, int k);

int		ft_strcmp(const char *a, const char *b);
int		is_space(char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(long long n, int fd);
void	ft_bzero(void *p, size_t n);

void	ps_exit(t_ps *ps, int err);

int		pos_of_min(t_stack *s);
int		pos_of_max(t_stack *s);
int		pos_of_val(t_stack *s, int v);
int		rot_cost(t_stack *s, int idx);
void	rotate_to(t_ps *ps, int which, int idx);

void	parse_args(t_ps *ps, int argc, char **argv);

void	read_numbers(t_ps *ps, char *s);
void	index_ranks(t_ps *ps);

void	apply_op(t_ps *ps, int code);

void	op(t_ps *ps, int code);
void	optimize_ops(t_ps *ps);

void	print_ops(t_ps *ps);

void	print_bench(t_ps *ps);

int		is_sorted(t_stack *s);
void	compute_disorder(t_ps *ps);
void	run_strategy(t_ps *ps);

void	sort_three(t_ps *ps);
void	simple_sort(t_ps *ps);

void	chunk_sort(t_ps *ps);

void	quick_sort(t_ps *ps);
int		chunk_val(t_ps *ps, t_chunk *c, int k);
void	move_elem(t_ps *ps, int from, int to);
void	sort_small_chunk(t_ps *ps, t_chunk *c);

void	adaptive_low(t_ps *ps);
void	insert_back(t_ps *ps);
void	exec_move(t_ps *ps, t_move m);
int		count_unkept(int *keep, int n);
int		unkept_dist(t_stack *a, int *keep, int from_top);
int		lower_bound(int *s, int *tail, int len, int x);
#endif
