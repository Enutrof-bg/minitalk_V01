/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:39:50 by kevwang           #+#    #+#             */
/*   Updated: 2025/05/19 11:39:52 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

void	ft_pustr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	write(1, str, i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	result;

	i = 0;
	signe = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * signe);
}

int	ft_power(int nb, int power)
{
	int	result;

	result = 1;
	if (power < 0)
		return (0);
	if (nb == 0 && power == 0)
		return (1);
	while (power >= 1)
	{
		result = result * nb;
		power--;
	}
	return (result);
}

char	*ft_calloc(int size)
{
	int		i;
	char	*newcalloc;

	i = 0;
	newcalloc = malloc(sizeof(char) * (size));
	if (!newcalloc)
		return (NULL);
	while (i < size)
	{
		newcalloc[i] = 0;
		i++;
	}
	return (newcalloc);
}

char	*ft_strdup(const char *s)
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (newstr == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}