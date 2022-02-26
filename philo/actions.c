/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:42:27 by lpuchol           #+#    #+#             */
/*   Updated: 2022/02/25 16:33:03 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(char *str)
{
	write (2, str, ft_strlen(str));
	exit (1);
}

void	*actions(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	printf("ID philo : %d\n", ph->id_philo);
	return (NULL);
}
