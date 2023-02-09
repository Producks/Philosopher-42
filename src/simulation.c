/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:37:27 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/09 02:54:01 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/struct.h"
#include "../include/utils.h"
#include "../include/error.h"

//eat time + sleep time < death_timer
//2 times my eat_time > death_timer
// pour decaller moitier / eat_time

void	die(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->write);
	if (philo->params->dead == true)
	{
		pthread_mutex_unlock(&philo->params->write);
		return ;
	}
	philo->params->dead = true;
	printf(RED "%ld %d died 💀\n",
		(time_stamp() - philo->params->start_simul), philo->id);
	pthread_mutex_unlock(&philo->params->write);
}

/*wait ->(time until death) - 500*/
void	*dinner(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->time_last_meal = philo->params->start_simul;
	if (philo->even == true)
		usleep(philo->params->time_to_eat / 2);
	while (philo->params->dead != true && philo->num_times_eaten != philo->params->nbr_times_eat)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_sleep(philo);
		//smart_think(philo);
	}
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
	return (0);
}
