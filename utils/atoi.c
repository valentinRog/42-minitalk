/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:03:51 by vrogiste          #+#    #+#             */
/*   Updated: 2022/09/01 17:04:00 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*ft_strchr(const char *s, int c)
{
	if (*s == (char)c)
		return ((char *)s);
	if (*s)
		return (ft_strchr(s + 1, c));
	return (NULL);
}

int	ft_atoi(const char *str)
{
	uint64_t	sum;
	int			sign;

	sum = 0;
	sign = 1;
	while (ft_strchr(" \t\n\r\v\f", *str))
		str++;
	if (*str == '+' || *str == '-')
		if (*(str++) == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		sum *= 10;
		sum += *str - '0';
		str++;
	}
	return (sum * sign);
}
