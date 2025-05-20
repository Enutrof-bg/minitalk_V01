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

// void	signal_handler(int signum)
// {
// 	printf("SIGNUM :%d\n", signum);
// }

// void	signal_term(int signum)
// {
// 	printf("term :%d\n", signum);
// 	// kill(pidserver);
// }

int ft_convert(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '0')
		{
			i++;
		}
		else if (str[i] == '1')
		{
			count = count + ft_power(2, 7 - i);
			i++;
		}
	}
	return (count);
}

void ft_print(int signum)
{
	int count;
	static char str[500];
	static char bit[9];
	static int i = 0;
	static int j = 0;
	// if (!str)
	// {
	// 	str = ft_calloc(sizeof(char) * 500);
	// 	if (!str)
	// 		return ;
	// }
	if (signum == 10)
		bit[i] = '0';
	else if (signum == 12)
		bit[i] = '1';
	i++;
	bit[8] = '\0';
	// printf("signum :%d\n", signum);
	// printf("i :%d bit :%s\n",i, bit);
	if (i == 8)
	{
		// printf("%s\n", bit);
		count = ft_convert(bit);
		// printf("%c\n", (char)count);
		str[j] = (char)count;
		// printf("%c\n", str[j]);
		// ft_pustr(str);
		j++;
		// ft_putchar(count);
		count = 0;
		while (i > 0)
		{
			bit[i] = '0';
			i--;
		}
		// printf("i :%d bit :%s\n",i, bit);
		ft_pustr(str);
	}
	
}

int main()
{
	// signal(SIGUSR1, ft_print);
	// signal(SIGUSR2, ft_print);

	pid_t pidserver = getpid();
	printf("SERVER PID : %d\n", pidserver);
	while (1)
	{
		signal(SIGUSR1, ft_print);
		signal(SIGUSR2, ft_print);
	}
}
