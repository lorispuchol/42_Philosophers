/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:42:27 by lpuchol           #+#    #+#             */
/*   Updated: 2022/03/04 12:36:08 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_main_check_if_die_or_finish(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nb_philo)
	{
		pthread_mutex_lock(&args->mut_print);
		if (((ft_get_time_now() - args->time_start)
				- args->philo[i].chrono_last_meal) > args->t_die)
		{
			args->philo[i].die = 1;
			args->end = 1;
			args->chrono_now = ft_get_time_now() - args->time_start;
			printf("%lldms %d died\n", args->chrono_now, i + 1);
			pthread_mutex_unlock(&args->mut_print);
			return ;
		}
		else
			pthread_mutex_unlock(&args->mut_print);
	}
	pthread_mutex_lock(&args->mut_print);
	if (args->nb_finish_eat == args->nb_philo)
		args->end = 1;
	pthread_mutex_unlock(&args->mut_print);
}

void	ft_usleep(int sleep_ms, t_philo *philo)
{
	long long int	expected_time;

	pthread_mutex_unlock(&philo->ar->mut_print);
	expected_time = ft_get_time_now() + sleep_ms;
	while (ft_get_time_now() < expected_time)
		usleep(100);
}

void	ft_sleep(t_philo *philo)
{
	ft_display_log(philo, "is sleeping");
	pthread_mutex_lock(&philo->ar->mut_print);
	ft_usleep(philo->ar->t_sleep, philo);
	ft_display_log(philo, "is thinking");
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->ar->fork[philo->fork_l]);
	ft_display_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo->ar->fork[philo->fork_r]);
	ft_display_log(philo, "has taken a fork");
	ft_display_log(philo, "is eating");
	pthread_mutex_lock(&philo->ar->mut_print);
	philo->chrono_last_meal = ft_get_time_now() - philo->ar->time_start;
	pthread_mutex_unlock(&philo->ar->mut_print);
	pthread_mutex_lock(&philo->ar->mut_print);
	ft_usleep(philo->ar->t_eat, philo);
	philo->nb_meal++;
	if (philo->nb_meal == philo->ar->nb_must_eat)
	{
		philo->finish_eat = 1;
		pthread_mutex_lock(&philo->ar->mut_print);
		philo->ar->nb_finish_eat++;
		pthread_mutex_unlock(&philo->ar->mut_print);
	}
	pthread_mutex_unlock(&philo->ar->fork[philo->fork_r]);
	pthread_mutex_unlock(&philo->ar->fork[philo->fork_l]);
}

void	*actions(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if ((ph->id_philo % 2) == 0)
		usleep(500);
	pthread_mutex_lock(&ph->ar->mut_print);
	while (ph->die == 0 && ph->finish_eat == 0 && ph->ar->end == 0)
	{
		pthread_mutex_unlock(&ph->ar->mut_print);
		ft_eat(ph);
		pthread_mutex_lock(&ph->ar->mut_print);
		if (ph->die == 0 && ph->finish_eat == 0 && ph->ar->end == 0)
		{
			pthread_mutex_unlock(&ph->ar->mut_print);
			ft_sleep(ph);
		}
		else
		{
			pthread_mutex_unlock(&ph->ar->mut_print);
			return (NULL);
		}
		pthread_mutex_lock(&ph->ar->mut_print);
	}
	pthread_mutex_unlock(&ph->ar->mut_print);
	return (NULL);
}
