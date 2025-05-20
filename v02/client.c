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

void	ft_send_signal(pid_t pid, char *str)
{
	int	i;
	int	killtest;

	i = 0;
	while (str[i])
	{
		if (str[i] == '0')
			killtest = kill(pid, SIGUSR1);
		else if (str[i] == '1')
			killtest = kill(pid, SIGUSR2);
		i++;
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pidserver;
	char	*bit;
	int		i;

	i = 0;
	if (argc >= 3)
	{
		pidserver = ft_atoi(argv[1]);
		printf("%d\n", pidserver);
		// len = ft_strlen(argv[2][i]);
		while (argv[2][i])
		{
			bit = ft_call_bit(argv[2][i]);
			ft_send_signal(pidserver, bit);
			free(bit);
			i++;
		}
	}
}
