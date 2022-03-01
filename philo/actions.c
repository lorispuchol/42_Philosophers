/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:42:27 by lpuchol           #+#    #+#             */
/*   Updated: 2022/02/28 19:44:54 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_display_log(t_philo *philo, char *str)
{
	long long int	time;

	pthread_mutex_lock(&philo->ar->mut_print);
	if (ft_get_current_time(philo->ar) != 0)
		return (-1);
	time = (((philo->ar->current_time.tv_sec - philo->ar->start_time.tv_sec)
				* 1000) + ((philo->ar->current_time.tv_usec
					- philo->ar->start_time.tv_usec) / 1000));
	printf("%lldms %d %s\n", time, philo->id_philo, str);
	pthread_mutex_unlock(&philo->ar->mut_print);
	return (0);
}

void	*actions(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	pthread_mutex_lock(&ph->ar->fork[ph->fork_l]);
	pthread_mutex_lock(&ph->ar->fork[ph->fork_r]);
	if (ft_display_log(ph, "is eating") != 0)
		return (NULL);
	sleep(1);
	pthread_mutex_unlock(&ph->ar->fork[ph->fork_l]);
	pthread_mutex_unlock(&ph->ar->fork[ph->fork_r]);
	return (NULL);
}
/*
	printf("ID philo : %d\n", ph->id_philo);
	printf("i fork_l : %d\n", ph->fork_l);
	printf("i fork_r : %d\n\n", ph->fork_r);
*/