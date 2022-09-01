/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:43:06 by vrogiste          #+#    #+#             */
/*   Updated: 2022/09/01 17:09:37 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#include "utils.h"

static bool	g_lock = true;

void	action(int sig)
{
	(void)sig;
	g_lock = false;
}

void	send_byte(int pid, unsigned char c)
{
	size_t	i;
	bool	bit;

	i = 0;
	while (i < sizeof(unsigned char) << 3)
	{
		g_lock = true;
		bit = c & (1 << i);
		kill(pid, (SIGUSR1 * !bit) + (SIGUSR2 * bit));
		while (g_lock)
			;
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (argc != 3)
	{
		dputstr(STDERR_FILENO, "usage: ./client [pid] [message]\n");
		return (EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, action);
	str = argv[2];
	while (true)
	{
		send_byte(pid, *str);
		if (!*str)
			break ;
		str++;
	}
}
