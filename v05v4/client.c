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

void	ft_base(int c, int i, char *newstr)
{
	if (c >= 2)
	{
		ft_base(c / 2, i - 1, newstr);
	}
	newstr[i] = "01"[c % 2];
}

char	*ft_call_bit(unsigned char c)
{	
	char	*bite;
	int		i;

	i = 0;
	bite = malloc(sizeof(char) * (8 + 1));
	if (!bite)
		return (NULL);
	while (i < 8)
	{
		bite[i] = '0';
		i++;
	}
	ft_base(c, 7, bite);
	bite[8] = '\0';
	return (bite);
}

char	*ft_call_len(int c)
{	
	char	*bite;
	int		i;

	i = 0;
	bite = malloc(sizeof(char) * (32 + 1));
	if (!bite)
		return (NULL);
	while (i < 32)
	{
		bite[i] = '0';
		i++;
	}
	ft_base(c, 31, bite);
	bite[32] = '\0';
	return (bite);
}

void	ft_send_len(pid_t pid, char *str)
{
	static char	*str_copie_len;
	static int	i = 0;

	if (!str_copie_len)
		str_copie_len = ft_strdup(str);
	if (i < 32)
	{
		if (str_copie_len[i] == '0')
			kill(pid, SIGUSR1);
		else if (str_copie_len[i] == '1')
			kill(pid, SIGUSR2);
		i++;
	}
	if (i == 32)
	{
		free(str_copie_len);
		str_copie_len = NULL;
	}
}

void ft_reset(char **bit, int *i)
{
	*i = 0;
	free(*bit);
	*bit = NULL;
}

void ft_send_bit(pid_t pid, char *bit, int i)
{
	if (bit[i] == '0')
		kill(pid, SIGUSR1);
	else if (bit[i] == '1')
		kill(pid, SIGUSR2);
}

void ft_initialize(char *str, char **str_copie, char **bit)
{
	*str_copie = str;
	if (!*bit)
		*bit = ft_call_bit(*str_copie[0]);
	// *str_copie = str_copie[1];
}

void	ft_send_signal(pid_t pid, char *str)
{
	static char	*str_copie = NULL;
	static int	i = 0;
	static int	j = 1;
	static int	clean = 0;
	static char	*bit = NULL;

	if (!str_copie && clean == 0)
		ft_initialize(str, &str_copie, &bit);
	else
	{
		if (i < 8)
			ft_send_bit(pid, bit, i++);
		if (i == 8)
		{
			ft_reset(&bit, &i);
			if (clean == 0)
			{
				if (str_copie[j])
					bit = ft_call_bit(str_copie[j++]);
				else
				{
					bit = ft_call_bit(0);
					clean = 1;
				}
			}
		}
	}
}

void	ft_receive(int signum, siginfo_t *info, void *truc)
{
	static int	test = 0;

	if (truc)
		truc = NULL;
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
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	pid_t				pidserver;
	struct sigaction	sig;
	char				*len_bit;

	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = ft_receive;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	if (argc == 3)
	{
		pidserver = ft_atoi(argv[1]);
		// ft_putnbr(pidserver);
		len_bit = ft_call_len(ft_strlen(argv[2]));
		ft_send_len(pidserver, len_bit);
		free(len_bit);
		ft_send_signal(pidserver, argv[2]);
		while (1)
		{
			pause();
		}
	}
	return (0);
}
