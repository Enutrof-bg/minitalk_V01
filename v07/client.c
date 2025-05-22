/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:20:40 by kevwang           #+#    #+#             */
/*   Updated: 2025/05/19 10:20:42 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	*g_str_copie = NULL;

void	ft_send_len(pid_t pid, char *str)
{
	static char	*g_str_copie_len;
	static int	i = 0;
	static int	clean = 0;

	if (!g_str_copie_len)
		g_str_copie_len = ft_strdup(str);
	if (i < 32)
	{
		if (g_str_copie_len[i] == '0')
			kill(pid, SIGUSR1);
		else if (g_str_copie_len[i] == '1')
			kill(pid, SIGUSR2);
		i++;
	}
	if (i == 32 && clean == 0)
	{
		clean = 1;
		free(g_str_copie_len);
		g_str_copie_len = NULL;
	}
}

// void ft_send_signal_2(int *i, int *j, char *bit, int *clean, pid_t *pid)
// {
// 	if (*i < 8)
// 	{
// 		if (bit[*i] == '0')
// 			kill(*pid, SIGUSR1);
// 		else if (bit[*i] == '1')
// 			kill(*pid, SIGUSR2);
// 		i++;
// 	}
// 	if (*clean == 1 && *i == 8)
// 	{
// 		free(g_str_copie);
// 		g_str_copie = NULL;
// 	}
// 	else if (*i == 8 && *clean == 0)
// 	{
// 		*i = 0;
// 		j++;
// 		ft_call_bit(g_str_copie[*j], bit);
// 	}
// 	if (!g_str_copie[*j] && *clean == 0)
// 	{
// 		ft_call_bit(0, bit);
// 		*i = 0;
// 		*clean = 1;
// 	}
// }
// void ft_free(char *str)
// {
// 	free(str);
// 	str = NULL;
// }

void	ft_send_signal(pid_t pid, char *str)
{
	static int	i = 0;
	static int	j = 0;
	static char	bit[9];
	static int	clean = 0;
	// static char	*g_str_copie = NULL;

	// if (signum == SIGUSR2)
	// {
	// 	if (g_str_copie)
	// 		ft_free(g_str_copie);
	// 	return ;
	// }
	if (!g_str_copie && clean == 0)
	{
		g_str_copie = ft_strdup(str);
		if (!g_str_copie)
			exit(1);
		ft_call_bit(g_str_copie[j], bit);
	}
	else
	{
		// ft_send_signal_2(&i, &j, bit, &clean, &pid);
		if (i < 8)
		{
			if (bit[i] == '0')
				kill(pid, SIGUSR1);
			else if (bit[i] == '1')
				kill(pid, SIGUSR2);
			i++;
		}
		if (clean == 1 && i == 8)
		{
			// ft_free(g_str_copie);
			free(g_str_copie);
			g_str_copie = NULL;
		}
		else if (i == 8 && clean == 0)
		{
			i = 0;
			j++;
			ft_call_bit(g_str_copie[j], bit);
		}
		if (!g_str_copie[j] && clean == 0)
		{
			ft_call_bit(0, bit);
			i = 0;
			clean = 1;
		}
	}
}

void	ft_receive(int signum, siginfo_t *info, void *old)
{
	static int	test = 0;

	if (old)
		old = NULL;
	if (signum == SIGUSR1)
	{
		if (test < 31)
			ft_send_len(info->si_pid, NULL);
		else
			ft_send_signal(info->si_pid, NULL);
		test++;
	}
	else if (signum == SIGUSR2)
	{
		test = 0;
		// ft_send_signal(info->si_pid, NULL, SIGUSR2);
		if (g_str_copie)
		{
			free(g_str_copie);
			g_str_copie = NULL;
		}
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	pid_t				pidserver;
	char				*len_bit;
	struct sigaction	sig;

	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = ft_receive;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	if (argc >= 3)
	{
		pidserver = ft_atoi(argv[1]);
		len_bit = ft_call_len(ft_strlen(argv[2]));
		if (!len_bit)
			return (1);
		ft_send_len(pidserver, len_bit);
		free(len_bit);
		ft_send_signal(pidserver, argv[2]);
	}
	while (1)
	{
		pause();
	}
}
