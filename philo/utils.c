/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_and_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:31:56 by lpuchol           #+#    #+#             */
/*   Updated: 2022/03/02 15:33:13 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int a)
{
	int	ret;

	ret = 0;
	if ((a >= '0' && a <= '9'))
		ret = 1;
	return (ret);
}

int	ft_atoi(const char *str, int *dest, int i)
{
	long	ret;
	int		signe;

	signe = 1;
	ret = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			signe = -signe;
	if (str[i] == '\0')
		return (0 * printf("Non-numeric argument\n") - 1);
	while (str[i] && ft_isdigit(str[i]) == 1)
	{
		ret = ret * 10 + str[i] - 48;
		if ((ret > 2147483648 && signe == -1)
			|| (ret > 2147483647 && signe == 1))
			return (0 * printf("Argument too big\n") - 1);
		i++;
	}
	if (ft_isdigit(str[i]) == 0 && str[i] != '\0')
		return (0 * printf("Non-numeric argument\n") - 1);
	*dest = (ret * signe);
	return (0);
}
