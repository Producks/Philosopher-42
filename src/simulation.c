/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:37:27 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/09 18:52:12 by ddemers          ###   ########.fr       */
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
	if (philo->params->dead == true)
	{
		return ;
	}
	philo->params->dead = true;
	printf(RED "%ld %d died 💀\n",
		(time_stamp() - philo->params->start_simul), philo->id);
	philo->time_of_death = (time_stamp() - philo->params->start_simul);
	philo->params->log = philo->id - 1;
}

static void	think_big(t_philo *philo)
{
	int	think_time;
	print_philo_state(philo, 3);
	think_time = (philo->params->time_to_die - (time_stamp() - philo->time_last_meal) - 500) * 1000;
	if (think_time < 0)
		think_time = 0;
	usleep(think_time);
}

/*wait ->(time until death) - 500*/
void	*dinner(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->time_last_meal = philo->params->start_simul;
	if (philo->even == true)
		usleep(philo->params->time_to_eat / 2);
	while (philo->params->dead != true)
	{
		philo_eat(philo);
		if (philo->num_times_eaten == philo->params->nbr_times_eat)
			break ;
		philo_sleep(philo);
		think_big(philo);
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
