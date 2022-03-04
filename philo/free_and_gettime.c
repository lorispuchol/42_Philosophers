/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_gettime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:03:55 by lpuchol           #+#    #+#             */
/*   Updated: 2022/03/04 15:51:29 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_end(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nb_philo)
	{
		if (pthread_join(args->philo[i].id_th, NULL) != 0)
		{
			ft_free(args);
			return (0 * printf("pthread_join failed\n") - 1);
		}
	}
	return (0);
}

void	ft_one_philo(t_args *args)
{
	long long int	time_start;
	long long int	expected_time;

	time_start = ft_get_time_now();
	expected_time = time_start + args->t_die;
	printf("0ms 1 has taken a fork\n");
	while (ft_get_time_now() < expected_time)
		usleep(100);
	printf("%lldms 1 died\n", (ft_get_time_now() - time_start));
}

void	ft_free(t_args *args)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&args->mut_print);
	while (++i < args->nb_philo)
		pthread_detach(args->philo[i].id_th);
	pthread_mutex_unlock(&args->mut_print);
	i = -1;
	pthread_mutex_lock(&args->mut_print);
	while (++i < args->nb_philo)
		pthread_mutex_destroy(&args->fork[i]);
	pthread_mutex_unlock(&args->mut_print);
	pthread_mutex_destroy(&args->mut_print);
	free(args->fork);
	free(args->philo);
}

void	ft_display_log(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->ar->mut_print);
	if (philo->ar->end != 0)
	{
		pthread_mutex_unlock(&philo->ar->mut_print);
		return ;
	}
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
