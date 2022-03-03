/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:34:52 by lpuchol           #+#    #+#             */
/*   Updated: 2022/03/03 14:08:18 by lpuchol          ###   ########.fr       */
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
	long long int	time_start;
	long long int	chrono_now;
	int				argc;
	char			**argv;
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_must_eat;
	int				end;
	int				nb_finish_eat;
	pthread_mutex_t	mut_print;
	pthread_mutex_t	*fork;
	t_philo			*philo;
};

struct	s_philo
{
	int				die;
	int				finish_eat;
	long long int	chrono_last_meal;
	pthread_t		id_th;
	int				fork_l;
	int				fork_r;
	int				id_philo;
	int				nb_meal;
	t_args			*ar;
};

// philo.c
int				ft_init_philos(t_args *args);
int				ft_init_forks(t_args *args, int i);
int				ft_launch_philos(t_args *args, int i, int i2);
int				ft_parsing(t_args *args);
// actions.c
void			ft_main_check_if_die_or_finish(t_args *args);
void			ft_usleep(int sleep_ms, t_philo *philo);
void			ft_sleep(t_philo *philo);
void			ft_eat(t_philo *philo);
void			*actions(void *philo);
// free_and_gettime.c
void			ft_free(t_args *args);
void			ft_display_log(t_philo *philo, char *str);
long long int	ft_get_time_now(void);
// utils.c
int				ft_isdigit(int a);
int				ft_atoi(const char *str, int *dest, int i);

#endif