/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:08:21 by kevwang           #+#    #+#             */
/*   Updated: 2025/05/22 11:08:22 by kevwang          ###   ########.fr       */
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

void	ft_call_bit(unsigned char c, char *bit)
{	
	int	i;

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
