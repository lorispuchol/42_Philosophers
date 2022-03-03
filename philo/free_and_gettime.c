/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_gettime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:03:55 by lpuchol           #+#    #+#             */
/*   Updated: 2022/03/03 17:11:23 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_args *args)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&args->mut_print);
	while (++i < args->nb_philo)
	{
		pthread_detach(args->philo[i].id_th);
		pthread_mutex_destroy(&args->fork[i]);
	}
	pthread_mutex_unlock(&args->mut_print);
	pthread_mutex_destroy(&args->mut_print);
	free(args->fork);
	free(args->philo);
}

void	ft_display_log(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->ar->mut_print);
	philo->ar->chrono_now = ft_get_time_now() - philo->ar->time_start;
	printf("%lldms %d %s\n", philo->ar->chrono_now, philo->id_philo, str);
	pthread_mutex_unlock(&philo->ar->mut_print);
}

long long int	ft_get_time_now(void)
{
	long long int	time;
	struct timeval	st_time;

	gettimeofday(&st_time, NULL);
	time = st_time.tv_sec * 1000 + st_time.tv_usec / 1000;
	return (time);
}
