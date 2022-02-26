/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:56:17 by lpuchol           #+#    #+#             */
/*   Updated: 2022/02/25 20:12:34 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philos(t_args *args)
{
	int	i;

	args->philo = malloc(sizeof(t_philo) * args->nb_philo);
	if (!args->philo)
		ft_exit("malloc failed");
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
		ft_exit("malloc failed");
	}
	ft_init_philos_2(args, -1);
}

void	ft_init_philos_2(t_args *args, int i)
{
	while (++i < args->nb_philo)
	{
		if (pthread_mutex_init(&args->fork[i], NULL) != 0)
		{
			free (args->philo);
			free (args->fork);
			ft_exit("pthread_mutex_init failed\n");
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
	ft_init_philos_3(args);
}

void	ft_init_philos_3(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nb_philo)
	{
		if (pthread_create(&(args->philo[i].id_th), NULL,
				&actions, &args->philo[i]) != 0)
		{
			free (args->philo);
			free (args->fork);
			ft_exit("pthread_create failed\n");
		}
	}
}

void	ft_parsing(t_args *args)
{
	if (args->argc != 5 && args->argc != 6)
		ft_exit("wrong number of arguments\n");
	args->nb_philo = ft_atoi(args->argv[1]);
	args->t_die = ft_atoi(args->argv[2]);
	args->t_eat = ft_atoi(args->argv[3]);
	args->t_sleep = ft_atoi(args->argv[4]);
	if (args->nb_philo <= 0 || args->t_die < 0
		|| args->t_eat < 0 || args->t_sleep < 0)
		ft_exit("At least one invalid argument\n");
	if (args->argc == 6)
	{
		args->nb_must_eat = ft_atoi(args->argv[5]);
		if (args->nb_must_eat < 0)
			ft_exit("Invalid optional argument\n");
	}
	else
		args->nb_must_eat = -1;
}

int	main(int argc, char **argv)
{
	t_args	args;
	int		i;

	args.argv = argv;
	args.argc = argc;
	ft_parsing(&args);
	ft_init_philos(&args);
	i = -1;
	while (++i < args.nb_philo)
	{
		if (pthread_join(args.philo[i].id_th, NULL) != 0)
		{
			free (args.philo);
			free (args.fork);
			ft_exit("pthread_join failed\n");
		}
	}
	free (args.philo);
	free (args.fork);
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
	int i = -1;
	while (++i < args.nb_philo)
	{
		printf ("ID philo : %d\n", args.philo[i].id_philo);
		printf ("NB meal  : %d\n\n", args.philo[i].nb_meal);
	}
*/

/*
	affiche les user input
	printf("nb_philo : %d\n", args.nb_philo);
	printf("t_die : %d\n", args.t_die);
	printf("t_eat : %d\n", args.t_eat);
	printf("t_sleep : %d\n", args.t_sleep);
	printf("nb_must_eat : %d\n", args.nb_must_eat);
*/