/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:42:33 by vrogiste          #+#    #+#             */
/*   Updated: 2022/09/01 16:26:38 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#include "utils.h"

#define BUFFER_SIZE 10000

static void	action(int sig, siginfo_t *info, void *context)
{
	static int				i;
	static unsigned char	c;
	static char				buffer[BUFFER_SIZE];
	static int				len;

	(void)context;
	c |= (sig == SIGUSR2) << i;
	i++;
	if (i == sizeof(unsigned char) << 3)
	{
		buffer[len] = c;
		if (!c || len == BUFFER_SIZE)
		{
			write(STDOUT_FILENO, buffer, len);
			len = 0;
			if (!c)
				dputstr(STDOUT_FILENO, "\n");
		}
		else
			len++;
		i = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
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
		pause();
}
