/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 23:03:57 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/02 11:49:47 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_arguments *arguments, t_philo *philo,
	t_mutex *mutex, bool *dead_philo)
{
	int	index;

	index = 0;
	while (index < arguments->nbr_philosophers)
	{
		philo[index].id = index + 1;
		philo[index].first_fork = &mutex->fork[(2 + index
				- (index % 2)) % arguments->nbr_philosophers];
		philo[index].second_fork = &mutex->fork[(2 + index
				- (1 - index % 2)) % arguments->nbr_philosophers];
		philo[index].meal_lock = &mutex->meal_lock[index];
		philo[index].write_lock = &mutex->write_lock;
		philo[index].dead_lock = &mutex->dead_lock;
		philo[index].launch = &mutex->launch;
		philo[index].dead = dead_philo;
		philo[index].num_times_eaten = 0;
		philo[index].time_last_meal = 0;
		philo[index].sim_params = arguments->sim_params;
		index++;
	}
}
