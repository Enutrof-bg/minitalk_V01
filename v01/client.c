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

void 	ft_base(int c, int i, char *newstr)
{
	if (c >= 2)
	{
		ft_base(c / 2, i - 1, newstr);
	}
	newstr[i] = "01"[c % 2];
}

char *ft_call_bit(unsigned char c)
{	
	char *bit;
	int i;

	i = 0;
	bit = malloc(sizeof(char) * (8));
	while (i < 8)
	{
		bit[i] = '0';
		i++;
	}
	ft_base(c, 7, bit);
	bit[8] = '\0';
	return (bit);
}

void ft_send_signal(pid_t pid, char *str)
{
	int i;
	int killtest;

	i = 0;
	killtest = 1;
	printf("%s\n", str);
	while (str[i])
	{
		if (str[i] == '0')
		{
			killtest = kill(pid, SIGUSR1);
			printf("%c\n", str[i]);
		}
		else if (str[i] == '1')
		{
			killtest = kill(pid, SIGUSR2);
			printf("%c\n", str[i]);
		}
		i++;
		if (killtest == 0)
			printf("Signal sent.\n");
		else if (killtest == -1)
			printf("Signal failed.\n");
		killtest = 1;
		sleep(1);
	}
}

int main(int argc, char **argv)
{
	pid_t pidserver = 0;
	// int i = 0;
	// int killtest = 0;
	// printf("%d\n", ft_power(2, 8));
	if (argc >= 2)
	{
		pidserver = ft_atoi(argv[1]);
		printf("%d\n", pidserver);
		// while (argv[2])
		ft_send_signal(pidserver, ft_call_bit('j'));
		// killtest = kill(pidserver, SIGUSR1);
		// if (killtest == 0)
		// 	printf("Signal sent.");
		// else
		// 	printf("Signal failed.");

		// killtest = kill(pidserver, SIGUSR2);
		// if (killtest == 0)
		// 	printf("Signal sent.");
		// else
		// 	printf("Signal failed.");
	}
}