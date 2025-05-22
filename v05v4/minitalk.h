/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:29:25 by kevwang           #+#    #+#             */
/*   Updated: 2025/05/19 10:29:26 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h> //pour les functions signal
# include <stdlib.h> //malloc etc

int		ft_atoi(const char *str);
int		ft_power(int nb, int power);
int		ft_strlen(char *str);
void	ft_pustr(char *str);
char	*ft_itoa(int n);
char	*ft_strdup(char *s);
void	ft_putnbr(int nb);

#endif
