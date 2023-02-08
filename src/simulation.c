/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:37:27 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/08 12:58:58 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/struct.h"
#include "../include/utils.h"

void	check_death(t_philo *philo)
{
	if (time_stamp() - philo->time_last_meal > philo->params->time_to_die
		&& philo->params->dead == false)
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
}

void	*test(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->time_last_meal = time_stamp();
	while (philo->params->dead != true)
	{
		philo_sleep(philo);
		philo_eat(philo);
		check_death(philo);
	}
	return (NULL);
}

int	simulation(t_params *params)
{
	int			index;
	pthread_t	threads[200];

	index = 0;
	params->start_simul = time_stamp();
	while (index < params->nbr_philosophers)
	{
		pthread_create(&threads[index], NULL, test, &params->param[index]);
		index++;
	}
	index = 0;
	while (index < params->nbr_philosophers)
		pthread_join(threads[index++], NULL);
	return (0);
}
