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

int	ft_convert(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '0')
			i++;
		else if (str[i] == '1')
		{
			count = count + ft_power(2, 7 - i);
			i++;
		}
	}
	return (count);
}

int	ft_len_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '0')
			i++;
		else if (str[i] == '1')
		{
			count = count + ft_power(2, 31 - i);
			i++;
		}
	}
	return (count);
}

void	ft_len(int signum, int *len)
{
	static char	bit[33];
	static int	i = 0;

	if (signum == SIGUSR1)
		bit[i] = '0';
	else if (signum == SIGUSR2)
		bit[i] = '1';
	i++;
	if (i == 32)
	{
		bit[32] = '\0';
		*len = ft_len_count(bit);
		i = 0;
	}
}

void	ft_print(int signum, siginfo_t *info, void *old)
{
	int			count;
	static char	*str = NULL;
	static char	bit[9];
	static int	i = 0;
	static int	j = 0;
	static int	len = -1;

	if (old)
		old = NULL;
	if (len == -1)
	{
		ft_len(signum, &len);
		kill(info->si_pid, SIGUSR1);
	}
	else
	{
		if (!str)
		{
			str = malloc(sizeof(char) * (len + 1));
			if (!str)
				exit(1);
		}
		if (signum == SIGUSR1)
			bit[i] = '0';
		else if (signum == SIGUSR2)
			bit[i] = '1';
		i++;
		if (i == 8)
		{
			bit[8] = '\0';
			count = ft_convert(bit);
			str[j] = count;
			j++;
			i = 0;
			if (count == '\0' || j >= len)
			{
				str[len] = '\0';
				ft_putstr(str);
				j = 0;
				len = -1;
				free(str);
				str = NULL;
				kill(info->si_pid, SIGUSR2);
				return ;
			}
		}
		kill(info->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	pid_t				pidserver;
	struct sigaction	sig;

	pidserver = getpid();
	ft_putstr(ft_itoa(pidserver));
	ft_putstr("\n");
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = ft_print;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
	{
		pause();
	}
}
