/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: amazloum <amazloum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/31 11:31:06 by amazloum      #+#    #+#                 */
/*   Updated: 2026/10/31 11:39:10 by amazloum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_strcmp(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] && a[i] == b[i])
		i++;
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	write(fd, s, len);
}

void	ft_putnbr_fd(long long n, int fd)
{
	char	c;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = '0' + n % 10;
	write(fd, &c, 1);
}

void	ft_bzero(void *p, size_t n)
{
	unsigned char	*s;

	s = p;
	while (n > 0)
	{
		*s = 0;
		s++;
		n--;
	}
}
