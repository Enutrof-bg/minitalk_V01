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

static char *str_copie = NULL;

void	ft_base(int c, int i, char *newstr)
{
	if (c >= 2)
	{
		ft_base(c / 2, i - 1, newstr);
	}
	newstr[i] = "01"[c % 2];
}

// char	*ft_call_bit(unsigned char c)
// {	
// 	char	*bit;
// 	int		i;

// 	i = 0;
// 	bit = malloc(sizeof(char) * (8 + 1));
// 	if (!bit)
// 		return (NULL);
// 	while (i < 8)
// 	{
// 		bit[i] = '0';
// 		i++;
// 	}
// 	ft_base(c, 7, bit);
// 	bit[8] = '\0';
// 	return (bit);
// }

void	ft_call_bit(unsigned char c, char *bit)
{	
	int i;

	i = 0;
	while (i < 8)
	{
		bit[i] = '0';
		i++;
	}
	ft_base(c, 7, bit);
	bit[8] = '\0';
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
	// int	killtest;
	static char *str_copie_len;
	static int i = 0;
	static int clean = 0;
	// static int j = 0;
	// static char *bit;

	if (!str_copie_len)
		str_copie_len = ft_strdup(str);
	// if (!bit)
	// 	bit = ft_call_len(str_copie_len[j]);

	// write(1,"copie:",6);
	// write(1, str_copie_len, ft_strlen(str_copie_len));
	// write(1, "\n", 1);


	// write(1, bit, ft_strlen(bit));
	// write(1,":bit\n",5);

	if (i < 32)
	{
		if (str_copie_len[i] == '0')
			kill(pid, SIGUSR1);
		else if (str_copie_len[i] == '1')
			kill(pid, SIGUSR2);
		i++;
	}
	if (i == 32 && clean == 0)
	{
		// write(1,bit,32);
		// write(1,"\n",1);
		// i = 0;
		// j++;
		clean = 1;
		free(str_copie_len);
		str_copie_len = NULL;
	}
		// bit = ft_call_bit(str_copie_len[j]);
	// if (!str_copie_len[j])
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
	// int	killtest;
	// static char *str_copie = NULL;
	static int i = 0;
	static int j = 0;
	static char bit[9];
	static int clean = 0;

	if (!str_copie && clean == 0)
	{
		str_copie = ft_strdup(str);
		if (!str_copie)
			exit(0);
		ft_call_bit(str_copie[j], bit);
		// if (!str_copie || !bit)
			// return ;
		// write(1,"str_copie : ",12);
		// write(1, str_copie, ft_strlen(str_copie));
		// write(1,"\n",1);

		// write(1,"bit : ", 6);
		// write(1, bit, ft_strlen(bit));
		// write(1,"\n",1);
	}
	else
	{
	// write(1, bit, ft_strlen(bit));
	// write(1,"\n",1);

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
			free(str_copie);
			str_copie = NULL;
			// free(bit);
			// bit = NULL;
		}
		else if (i == 8 && clean == 0)
		{
			// write(1,bit,8);
			// write(1,"\n",1);
			i = 0;
			j++;
			// free(bit);
			// bit = NULL;
			ft_call_bit(str_copie[j], bit);
		}
		if (!str_copie[j] && clean == 0)
		{
			// free(bit);
			// bit = NULL;
			// str_copie = NULL;
			ft_call_bit(0, bit);
			i = 0;
			clean = 1;
		}

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

	if (truc)
		truc = NULL;
	if (signum == SIGUSR1)
	{
		if (test < 31)
		{
			// printf("%d len\n", test);
			ft_send_len(info->si_pid, NULL);
			test++;
		}
		// if (test == 32) 
		// {
		// 	if (str_copie)
		// 		free(str_copie);
		// 	str_copie = NULL;
		// 	test++;
		// }
		else
		{
			// if (str_copie)
			// 	free(str_copie);
			// str_copie = NULL;
			// printf("%d signal\n", test);
			ft_send_signal(info->si_pid, NULL);
			test++;
		}
	}
	else if (signum == SIGUSR2)
	{
		test = 0;
		// printf("sortie");
		if (str_copie)
		{
			free(str_copie);
			str_copie = NULL;
		}
		// if (bit)
		// {
		// 	free(bit);
		// 	bit = NULL;
		// }
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pidserver;
	// char	*bit;
	// int		i;
	struct sigaction sig;
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = ft_receive;

	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	// i = 0;
	if (argc >= 3)
	{
		pidserver = ft_atoi(argv[1]);
		printf("%d\n", pidserver);

		int len = ft_strlen(argv[2]);
		// printf("%d\n", len);
		char *len_bit = ft_call_len(len);
		if (!len_bit)
			return (1);
		// printf("len_bit:%s\n", len_bit);

		ft_send_len(pidserver, len_bit);
		free(len_bit);
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

	while (1)
	{
		pause();
		// sigaction(SIGUSR1, &sig, NULL);
		// sigaction(SIGUSR2, &sig, NULL);
	}

}
