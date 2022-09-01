/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:01:56 by vrogiste          #+#    #+#             */
/*   Updated: 2022/09/01 17:04:22 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	ft_strlen(const char *s)
{
	if (*s)
		return (1 + ft_strlen(s + 1));
	return (0);
}

void	dputstr(int fd, const char *s)
{
	write(fd, s, ft_strlen(s));
}

static void	dputchar(int fd, char c)
{
	write(fd, &c, sizeof(char));
}

void	dputnbr(int fd, int32_t n)
{
	int64_t	nb;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	if (nb / 10)
		dputnbr(fd, nb / 10);
	dputchar(fd, nb % 10 + '0');
}
