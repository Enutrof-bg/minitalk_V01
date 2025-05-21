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
	char	*bit;
	int		i;

	i = 0;
	bit = malloc(sizeof(char) * (8 + 1));
	if (!bit)
		return (NULL);
	while (i < 8)
	{
		bit[i] = '0';
		i++;
	}
	ft_base(c, 7, bit);
	bit[8] = '\0';
	return (bit);
}

char	*ft_call_len(int c)
{	
	char	*bit;
	int		i;

	i = 0;
	bit = malloc(sizeof(char) * (32 + 1));
	if (!bit)
		return (NULL);
	while (i < 32)
	{
		bit[i] = '0';
		i++;
	}
	ft_base(c, 31, bit);
	bit[32] = '\0';
	return (bit);
}

void	ft_send_len(pid_t pid, char *str)
{
	int	killtest;
	static char *str_copie;
	static int i = 0;
	// static int j = 0;
	// static char *bit;

	if (!str_copie)
		str_copie = str;
	// if (!bit)
	// 	bit = ft_call_len(str_copie[j]);
	write(1,"copie:",6);
	write(1, str_copie, ft_strlen(str_copie));
	write(1, "\n", 1);
	// write(1, bit, ft_strlen(bit));
	// write(1,":bit\n",5);
	if (i < 32)
	{
		if (str_copie[i] == '0')
			killtest = kill(pid, SIGUSR1);
		else if (str_copie[i] == '1')
			killtest = kill(pid, SIGUSR2);
		i++;
	}
	// if (i == 32)
	// {
	// 	write(1,bit,32);
	// 	write(1,"\n",1);
	// 	i = 0;
	// 	j++;
	// 	free(bit);
	// 	bit = ft_call_bit(str_copie[j]);
	// }
	// if (!str_copie[j])
	// {
	// 	free(bit);
	// 	bit = ft_call_bit(0);
	// }
	// i = 0;
	// while (str[i])
	// {
	// 	if (str[i] == '0')
	// 		killtest = kill(pid, SIGUSR1);
	// 	else if (str[i] == '1')
	// 		killtest = kill(pid, SIGUSR2);
	// 	i++;
	// 	usleep(100);
	// }
}

void	ft_send_signal(pid_t pid, char *str)
{
	int	killtest;
	static char *str_copie;
	static int i = 0;
	static int j = 0;
	static char *bit;
	static int clean = 0;

	if (!str_copie && clean == 0)
	{
		str_copie = str;
		if (!bit)
			bit = ft_call_bit(str_copie[j]);
		// write(1,"str_copie : ",12);
		// write(1, str_copie, ft_strlen(str_copie));
		// write(1,"\n",1);

		// write(1,"bit : ", 6);
		// write(1, bit, ft_strlen(bit));
		// write(1,"\n",1);
	}
	else
	{
	write(1, bit, ft_strlen(bit));
	write(1,"\n",1);
	if (i < 8)
	{
		if (bit[i] == '0')
			killtest = kill(pid, SIGUSR1);
		else if (bit[i] == '1')
			killtest = kill(pid, SIGUSR2);
		i++;
	}
	if (i == 8)
	{
		write(1,bit,8);
		write(1,"\n",1);
		i = 0;
		j++;
		free(bit);
		bit = ft_call_bit(str_copie[j]);
	}
	if (!str_copie[j] && clean == 0)
	{
		free(bit);
		// bit = NULL;
		// str_copie = NULL;
		bit = ft_call_bit(0);
		clean = 1;
	}
	// if (clean == 1)
	// {
	// 	str_copie = NULL;
	// 	free(bit);
	// }
	// i = 0;
	// while (str[i])
	// {
	// 	if (str[i] == '0')
	// 		killtest = kill(pid, SIGUSR1);
	// 	else if (str[i] == '1')
	// 		killtest = kill(pid, SIGUSR2);
	// 	i++;
	// 	usleep(100);
	// }
	}
}

void	ft_receive(int signum, siginfo_t *info, void *truc)
{
	static int test = 0;

	truc = NULL;
	if (signum == SIGUSR1)
	{
		if (test < 31)
		{
			printf("%d len\n", test);
			ft_send_len(info->si_pid, NULL);
			test++;
		}
		else
		{
			printf("%d signal\n", test);
			ft_send_signal(info->si_pid, NULL);
			test++;
		}
	}
	else if (signum == SIGUSR2)
	{
		test = 0;
		printf("sortie");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pidserver;
	// char	*bit;
	int		i;
	struct sigaction sig;

	sig.sa_sigaction = ft_receive;
	i = 0;
	if (argc >= 3)
	{
		pidserver = ft_atoi(argv[1]);
		printf("%d\n", pidserver);

		int len = ft_strlen(argv[2]);
		// printf("%d\n", len);
		char *len_bit = ft_call_len(len);
		printf("len_bit:%s\n", len_bit);

		ft_send_len(pidserver, len_bit);
		// while (argv[2][i])
		// {
		// 	bit = ft_call_bit(argv[2][i]);
		// 	// printf("%s\n", bit);


		ft_send_signal(pidserver, argv[2]);


		// 	free(bit);
		// 	i++;
		// }

		// bit = ft_call_bit(0);
		// // printf("%s\n", bit);
		// ft_send_signal(pidserver, bit);
		// free(bit);
	}
	// sigaction(SIGUSR1, &sig, NULL);
	// sigaction(SIGUSR2, &sig, NULL);
	while (1)
	{
		// pause();
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
	}
}
