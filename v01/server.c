/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:20:46 by kevwang           #+#    #+#             */
/*   Updated: 2025/05/19 10:20:48 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signum)
{
	printf("SIGNUM :%d\n", signum);
}

void	signal_term(int signum)
{
	printf("term :%d\n", signum);
	// kill(pidserver);
}

void ft_print(int signum)
{
	int count;
	int *ptrcount;

	count = 0;
	ptrcount = &count;
	printf("signum :%d\n", signum);

}

int main()
{
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_term);
	signal(SIGUSR1, ft_print);
	signal(SIGUSR2, ft_print);
	while (1)
	{
		pid_t pidserver = getpid();
		printf("SERVER PID : %d\n", pidserver);
		// kill(pidserver, SIGUSR1);
		sleep(1);
	}
}
