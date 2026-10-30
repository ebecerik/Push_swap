/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/30 12:53:10 by amazloum      #+#    #+#                 */
/*   Updated: 2026/10/30 18:14:28 by amazloum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*node_new(int val)
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (!n)
		return (NULL);
	n->val = val;
	n->prev = NULL;
	n->next = NULL;
	return (n);
}

void	stack_add_bottom(t_stack *s, t_node *n)
{
	n->next = NULL;
	n->prev = s->bot;
	if (s->bot)
		s->bot->next = n;
	else
		s->top = n;
	s->bot = n;
	s->size++;
}

void	stack_push_top(t_stack *s, t_node *n)
{
	n->prev = NULL;
	n->next = s->top;
	if (s->top)
		s->top->prev = n;
	else
		s->bot = n;
	s->top = n;
	s->size++;
}

t_node	*stack_pop_top(t_stack *s)
{
	t_node	*n;

	n = s->top;
	if (!n)
		return (NULL);
	s->top = n->next;
	if (s->top)
		s->top->prev = NULL;
	else
		s->bot = NULL;
	n->next = NULL;
	s->size--;
	return (n);
}

t_node	*stack_pop_bottom(t_stack *s)
{
	t_node	*n;

	n = s->bot;
	if (!n)
		return (NULL);
	s->bot = n->prev;
	if (s->bot)
		s->bot->next = NULL;
	else
		s->top = NULL;
	n->prev = NULL;
	s->size--;
	return (n);
}
