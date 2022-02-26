/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_and_others.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:03:55 by lpuchol           #+#    #+#             */
/*   Updated: 2022/02/25 16:11:37 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit(int a)
{
	int	ret;

	ret = 0;
	if ((a >= '0' && a <= '9'))
		ret = 1;
	return (ret);
}

int	ft_atoi(const char *str)
{
	long	ret;
	int		i;
	int		signe;

	signe = 1;
	ret = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			signe = -signe;
	if (str[i] == '\0')
		ft_exit("Non-numeric argument\n");
	while (str[i] && ft_isdigit(str[i]) == 1)
	{
		ret = ret * 10 + str[i] - 48;
		if ((ret > 2147483648 && signe == -1)
			|| (ret > 2147483647 && signe == 1))
			ft_exit("Argument too big\n");
		i++;
	}
	if (ft_isdigit(str[i]) == 0 && str[i] != '\0')
		ft_exit("Non-numeric argument\n");
	return (ret * signe);
}
