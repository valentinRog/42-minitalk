/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:42:33 by vrogiste          #+#    #+#             */
/*   Updated: 2022/09/05 12:11:37 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#include "utils.h"

#define BUFFER_SIZE 100000

static sig_atomic_t	g_received[2];

static void	action(int sig, siginfo_t *info, void *context)
{
	static int				i;
	static unsigned char	c;
	static char				buffer[BUFFER_SIZE];
	static int				len;

	(void)context;
	if (!(sig == SIGUSR2 || sig == SIGUSR1))
		return ;
	c |= (sig == SIGUSR2) << i++;
	if (i == sizeof(unsigned char) << 3)
	{
		buffer[len] = c;
		len++;
		if (!c || len == BUFFER_SIZE)
		{
			write(STDOUT_FILENO, buffer, len);
			len = 0;
			if (!c)
				dputstr(STDOUT_FILENO, "\n");
		}
		i = 0;
		c = 0;
	}
	g_received[0] = 1;
	g_received[1] = info->si_pid;
}

int	main(void)
{
	struct sigaction	s;

	dputstr(STDOUT_FILENO, "PID: ");
	dputnbr(STDOUT_FILENO, getpid());
	dputstr(STDOUT_FILENO, "\n");
	s.sa_sigaction = action;
	s.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s, 0);
	sigaction(SIGUSR2, &s, 0);
	while (true)
	{
		while (!g_received[0])
			pause();
		g_received[0] = 0;
		kill(g_received[1], SIGUSR1);
	}
}
