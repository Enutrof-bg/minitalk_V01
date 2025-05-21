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

int ft_len_count(char *str)
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

void ft_len(int signum, int *len)
{
	static char bit[33];
	static int i = 0;
	// int test;
	// char *result;

	if (signum == SIGUSR1)
		bit[i] = '0';
	else if (signum == SIGUSR2)
		bit[i] = '1';
	i++;
	
	// write(1, "test:", 5);
	// write(1, &bit[0], 32);
	// write(1, "\n", 1);
	// test = ft_len_count(bit);
	// result = ft_itoa(test);
	// write(1, result, ft_strlen(result));
	if (i == 32)
	{
		bit[32] = '\0';
		*len = ft_len_count(bit);
		i = 0;
		// result = ft_itoa(*len);
		// write(1, "len:", 4);
		// write(1, result, ft_strlen(result));
	}
}

void ft_print(int signum, siginfo_t *info, void *truc)
{
	int count;
	static char *str = NULL;
	static char bit[9];
	static int i = 0;
	static int j = 0;
	static int len = -1;
	// char *result;

	if (truc)
		truc = NULL;
	// (void)truc;
	if (len == -1)
	{
		ft_len(signum, &len);


		// result = ft_itoa(len);
		// write(1, "len:", 4);
		// write(1, result, ft_strlen(result));
		// write(1,"\n",1);


		kill(info->si_pid, SIGUSR1);
	}
	else 
	{
		if (!str)
		{
			printf(">>> ALLOC for %d bytes\n", len + 1);
			str = malloc(sizeof(char) * (len + 1));
			if (!str)
			{
				exit(1);
			}
		}
		if (signum == SIGUSR1)
			bit[i] = '0';
		else if (signum == SIGUSR2)
			bit[i] = '1';
		i++;
		
		// printf("signum :%d\n", signum);
		// printf("i :%d bit :%s\n",i, bit);
		if (i == 8)
		{
			bit[8] = '\0';
			// printf("%s\n", bit);


			// write(1,bit,8);
			// write(1,"\n",1);

			count = ft_convert(bit);
			// printf("%c\n", (char)count);
			str[j] = (char)count;
			// printf("%c\n", str[j]);
			// ft_pustr(str);
			j++;
			// ft_putchar(count);
			// count = 0;
			while (i > 0)
			{
				bit[i] = 0;
				i--;
			}
			// printf("i :%d bit :%s\n",i, bit);
			// if (str[j] == '\0')
			if (count == '\0' || j >= len)
			{
				str[j] = '\0';
				ft_pustr(str);
				j = 0;
				len = -1;
				free(str);
				str = NULL;
				// i = 0;
				// printf("%d\n", info->si_pid);
				kill(info->si_pid, SIGUSR2);
				return ; 
			}
		}
		kill(info->si_pid, SIGUSR1);
	}
	
}

int main()
{
	pid_t pidserver = getpid();
	printf("SERVER PID : %d\n", pidserver);
	// signal(SIGUSR1, ft_print);
	// signal(SIGUSR2, ft_print);
	struct sigaction sig;

	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = ft_print;
	
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	// signal(SIGUSR1, ft_print);
	// signal(SIGUSR2, ft_print);
	while (1)
	{
		pause();
		// sigaction(SIGUSR1, &sig, NULL);
		// sigaction(SIGUSR2, &sig, NULL);
	}
}
