/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:42:27 by lpuchol           #+#    #+#             */
/*   Updated: 2022/02/26 20:06:31 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*actions(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	pthread_mutex_lock(&ph->ar->mut_print);
	printf("ID philo : %d\n", ph->id_philo);
	printf("i fork_l : %d\n", ph->i_fork_l);
	printf("i fork_r : %d\n\n", ph->i_fork_r);
	pthread_mutex_unlock(&ph->ar->mut_print);

	pthread_mutex_lock(ph->fork_l);
	pthread_mutex_lock(ph->fork_r);
	sleep(1);
	pthread_mutex_unlock(ph->fork_l);
	pthread_mutex_unlock(ph->fork_r);
	return (NULL);
}
