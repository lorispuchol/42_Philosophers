/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_gettime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:03:55 by lpuchol           #+#    #+#             */
/*   Updated: 2022/03/02 15:50:27 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nb_philo)
	{
		pthread_detach(args->philo[i].id_th);
		pthread_mutex_destroy(&args->fork[i]);
	}
	pthread_mutex_destroy(&args->mut_print);
	free(args->fork);
	free(args->philo);
}

long long int ft_get_time_now(void)
{
	long long int time;
	struct timeval	st_time;
	
	gettimeofday(&st_time, NULL);
	time = st_time.tv_sec * 1000 + st_time.tv_usec / 1000;
	return (time);
}

