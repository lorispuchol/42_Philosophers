/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:56:17 by lpuchol           #+#    #+#             */
/*   Updated: 2022/02/26 18:02:52 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_philos(t_args *args)
{
	int	i;

	args->philo = malloc(sizeof(t_philo) * args->nb_philo);
	if (!args->philo)
		return (0 * printf("malloc failed") - 1);
	i = -1;
	while (++i < args->nb_philo)
	{
		args->philo[i].id_philo = i + 1;
		args->philo[i].nb_meal = 0;
		args->philo[i].ar = args;
	}
	args->fork = malloc(sizeof(pthread_mutex_t) * args->nb_philo);
	if (!args->fork)
	{
		free (args->philo);
		return (0 * printf("malloc failed") - 1);
	}
	return (ft_init_philos_2(args, -1));
}

int	ft_init_philos_2(t_args *args, int i)
{
	while (++i < args->nb_philo)
	{
		if (pthread_mutex_init(&args->fork[i], NULL) != 0)
		{
			while (--i <= 0)
				pthread_mutex_destroy(&args->fork[i]);
			free (args->philo);
			free (args->fork);
			return (0 * printf("pthread_mutex_init failed\n") - 1);
		}
	}
	i = -1;
	while (++i < args->nb_philo)
	{
		args->philo[i].fork_l = args->fork[i];
		args->philo[i].i_fork_l = i;
		args->philo[i].fork_r = args->fork[i + 1];
		args->philo[i].i_fork_r = i + 1;
		if (i == (args->nb_philo - 1))
		{
			args->philo[i].fork_r = args->fork[0];
			args->philo[i].i_fork_r = 0;
		}
	}
	return (ft_init_philos_3(args));
}

int	ft_init_philos_3(t_args *args)
{
	int	i;
	int	i2;

	i2 = -1;
	i = -1;
	while (++i < args->nb_philo)
	{
		if (pthread_create(&(args->philo[i].id_th), NULL,
				&actions, &args->philo[i]) != 0)
		{
			while (--i <= 0)
				pthread_detach(args->philo[i].id_th);
			while (++i2 < args->nb_philo)
				pthread_mutex_destroy(&args->fork[i]);
			free (args->philo);
			free (args->fork);
			return (0 * printf("pthread_create failed\n") - 1);
		}
	}
	return (0);
}

int	ft_parsing(t_args *args)
{
	if (args->argc != 5 && args->argc != 6)
		return (0 * printf("wrong number of arguments\n") - 1);
	if (ft_atoi(args->argv[1], &args->nb_philo, 0) == -1)
		return (-1);
	if (ft_atoi(args->argv[2], &args->t_die, 0) == -1)
		return (-1);
	if (ft_atoi(args->argv[3], &args->t_eat, 0) == -1)
		return (-1);
	if (ft_atoi(args->argv[4], &args->t_sleep, 0) == -1)
		return (-1);
	if (args->nb_philo <= 0 || args->t_die < 0
		|| args->t_eat < 0 || args->t_sleep < 0)
		return (0 * printf("At least one invalid argument\n") - 1);
	if (args->argc == 6)
	{
		if (ft_atoi(args->argv[5], &args->nb_must_eat, 0) == -1)
			return (-1);
		if (args->nb_must_eat < 0)
			return (0 * printf("Invalid optional argument\n") - 1);
	}
	else
		args->nb_must_eat = -1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	args;
	int		i;

	args.argv = argv;
	args.argc = argc;
	if (ft_parsing(&args) == -1)
		return (-1);
	if (ft_init_philos(&args) == -1)
		return (-1);
	i = -1;
	while (++i < args.nb_philo)
	{
		if (pthread_join(args.philo[i].id_th, NULL) != 0)
		{
			ft_free(&args);
			return (0 * printf("pthread_join failed\n") - 1);
		}
	}
	ft_free(&args);
	return (0);
}

/*
	affiche l'association des fourchettes et des philos
	i = -1;
	while (++i < args->nb_philo)
	{
		printf ("ID philo  : %d\n", args->philo[i].id_philo);
		printf ("fork left : %d\n", args->philo[i].i_fork_l);
		printf ("fork right : %d\n", args->philo[i].i_fork_r);
	}
*/

/*	
	affiche les id des philos
	i = -1;
	while (++i < args->nb_philo)
	{
		printf ("ID philo : %d\n", args->philo[i].id_philo);
		printf ("NB meal  : %d\n\n", args->philo[i].nb_meal);
	}
*/

/*
	affiche les user input
	printf("nb_philo : %d\n", args->nb_philo);
	printf("t_die : %d\n", args->t_die);
	printf("t_eat : %d\n", args->t_eat);
	printf("t_sleep : %d\n", args->t_sleep);
	printf("nb_must_eat : %d\n", args->nb_must_eat);
*/