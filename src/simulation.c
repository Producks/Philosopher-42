/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:37:27 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/11 19:25:54 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/struct.h"
#include "../include/utils.h"
#include "../include/error.h"
#include "../include/philo_action.h"

bool	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->dead_check);
	if (philo->params->dead == true)
	{
		pthread_mutex_unlock(&philo->params->dead_check);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&philo->params->dead_check);
		return (false);
	}
}

void	*dinner(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->time_last_meal = philo->params->start_simul;
	if (philo->even == true)
		usleep(philo->params->time_to_eat / 2);
	while (check_death(philo) != true)
	{
		philo_eat(philo);
		if (philo->num_times_eaten == philo->params->nbr_times_eat)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*test(void *ptr)
{
	return (NULL);
}

int	start_simulation(t_params *params)
{
	int			i;
	pthread_t	threads[200];

	i = 0;
	params->start_simul = time_stamp();
	while (i < params->nbr_philosophers)
	{
		if (pthread_create(&threads[i], NULL, dinner, &params->param[i]) != 0)
			return (create_failure(params, (i - 1), threads));
		i++;
	}
	i = 0;
	while (i < params->nbr_philosophers)
		pthread_join(threads[i++], NULL);
	printf("Time done:%ld\n", (time_stamp() - params->start_simul));
	return (0);
}
