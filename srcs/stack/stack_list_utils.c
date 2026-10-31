/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack_list_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/31 11:17:45 by amazloum      #+#    #+#                 */
/*   Updated: 2026/10/31 11:41:13 by amazloum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_clear(t_stack *s)
{
	t_node	*next;

	while (s->top)
	{
		next = s->top->next;
		free(s->top);
		s->top = next;
	}
	s->bot = NULL;
	s->size = 0;
}

int	stack_at(t_stack *s, int k)
{
	t_node	*n;
	int		i;

	if (k <= s->size / 2)
	{
		n = s->top;
		i = 0;
		while (i++ < k)
			n = n->next;
		return (n->val);
	}
	n = s->bot;
	i = s->size - 1;
	while (i-- > k)
		n = n->prev;
	return (n->val);
}
