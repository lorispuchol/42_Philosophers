/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:42:27 by lpuchol           #+#    #+#             */
/*   Updated: 2022/02/26 16:05:34 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*actions(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	printf("ID philo : %d\n", ph->id_philo);
	return (NULL);
}
