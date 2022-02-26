/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:34:52 by lpuchol           #+#    #+#             */
/*   Updated: 2022/02/25 16:35:00 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_args	t_args;
typedef struct s_philo	t_philo;

struct	s_args
{
	int				argc;
	char			**argv;
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_must_eat;
	pthread_mutex_t	*fork;
	t_philo			*philo;
};

struct	s_philo
{
	pthread_t		id_th;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	fork_r;
	int				i_fork_l;
	int				i_fork_r;
	int				id_philo;
	int				nb_meal;
	t_args			*ar;
};

//philo.c
void	ft_init_philos(t_args *args);
void	ft_init_philos_2(t_args *args, int i);
void	ft_init_philos_3(t_args *args);
void	ft_parsing(t_args *args);
//actions.c
void	ft_exit(char *str);
void	*actions(void *philo);
//atoi_exit_and_others.c
int		ft_strlen(char *str);
int		ft_isdigit(int a);
int		ft_atoi(const char *str);

#endif