/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:53:47 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/13 18:12:13 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/thread.h"
#include "../include/utils.h"
#include "../include/philo_action.h"

bool check_death(t_philo *philo)
{
	sem_wait(philo->dead_check);
	if (*philo->dead == false)
	{
		sem_post(philo->dead_check);
		return (false);
	}
	else
	{
		sem_post(philo->dead_check);
		return (true);
	}
}

void	*dinner(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->time_last_meal = *philo->start_simul;
	if (philo->even == true)
		usleep(philo->time_to_eat / 2);
	while (check_death(philo) != true)
	{
		philo_eat(philo);
		if (philo->num_times_eaten == philo->nbr_times_eat)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}