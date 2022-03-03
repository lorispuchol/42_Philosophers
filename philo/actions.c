/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:42:27 by lpuchol           #+#    #+#             */
/*   Updated: 2022/03/02 18:09:05 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_display_log(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->ar->mut_print);
	philo->ar->chrono_now = ft_get_time_now() - philo->ar->time_start;
	printf("%lldms %d %s\n", philo->ar->chrono_now, philo->id_philo, str);
	pthread_mutex_unlock(&philo->ar->mut_print);
}

void ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->ar->fork[philo->fork_l]);
	ft_display_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo->ar->fork[philo->fork_r]);
	ft_display_log(philo, "has taken a fork");
	ft_display_log(philo, "is eating");
	usleep(1000 * philo->ar->t_eat);
	pthread_mutex_unlock(&philo->ar->fork[philo->fork_r]);
	pthread_mutex_unlock(&philo->ar->fork[philo->fork_l]);
	//ft_sleep(philo);
}

void	*actions(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if ((ph->id_philo % 2) == 0)
		usleep(100);
	ft_eat(ph);
	return (NULL);
}
/*
	printf("ID philo : %d\n", ph->id_philo);
	printf("i fork_l : %d\n", ph->fork_l);
	printf("i fork_r : %d\n\n", ph->fork_r);
*/