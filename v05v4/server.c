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

void	ft_len(int signum, int *len, pid_t pid)
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
	kill(pid, SIGUSR1);
}

void ft_receive_bit(int signum, char *bit, int *i)
{
	if (signum == SIGUSR1)
		bit[*i] = '0';
	else if (signum == SIGUSR2)
		bit[*i] = '1';
	(*i)++;
}

void ft_reset(int *j, int *len, char **str, pid_t pid)
{
	ft_pustr(*str);
	*j = 0;
	*len = -1;
	free(*str);
	*str = NULL;
	kill(pid, SIGUSR2);

}

void ft_initialize(char **str, int len)
{
	*str = malloc(sizeof(char) * (len + 1));
	if (!*str)
		exit(1);
}

void	ft_print(int signum, siginfo_t *info, void *truc)
{
	static char	*str = NULL;
	static char	bit[9];
	static int	i = 0;
	static int	j = 0;
	static int	len = -1;

	if (truc)
		truc = NULL;
	if (len == -1)
	{
		ft_len(signum, &len, info->si_pid);
		return ;
	}
	if (!str)
		ft_initialize(&str, len);
	ft_receive_bit(signum, bit, &i);
	if (i == 8)
	{
		bit[8] = '\0';
		str[j] = (char)ft_convert(bit);
		i = 0;
		if (str[j] == '\0' || j >= len)
		{
			ft_reset(&j, &len, &str, info->si_pid);
			return ;
		}
		j++;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	pid_t				pidserver;
	struct sigaction	sig;

	pidserver = getpid();
	ft_putnbr(pidserver);
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = ft_print;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
