/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:37:27 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/15 21:04:21 by ddemers          ###   ########.fr       */
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
#include "../include/philo.h"
#include "../include/mutex.h"

bool	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == true)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (false);
	}
}

void	*dinner(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(philo->sim_params.time_to_eat / 2);
	while (check_death(philo) != true)
	{
		philo_eat(philo);
		if (philo->num_times_eaten == philo->sim_params.nbr_times_eat)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

// void	*one(void *ptr)
// {
// 		/*if (arguments->nbr_philosophers == 1)
// 	{
// 		//start_simul = time_stamp(); TODO
// 		pthread_create(&threads[0], NULL, one, &params->param[i]); //fix later
// 		pthread_join(threads[0], NULL);
// 		return (0);
// 	}*/
// 	t_philo	*philo;

// 	philo = (t_philo *)ptr;
// 	pthread_mutex_lock(philo->first_fork);
// 	print_philo_state(philo, 0);
// 	philo_wait_till_death(philo);
// 	pthread_mutex_unlock(philo->first_fork);
// 	return (NULL);
// }

int	start_simulation(t_arguments *arguments, int index)
{
	unsigned int		start_simul;
	bool				dead_philo;
	t_mutex				mutex;
	t_philo				philo[200];
	pthread_t			threads[200];

	if (init_mutex(&mutex, arguments->nbr_philosophers) == -1)
		return (-1);
	init_philo(arguments, philo, &mutex, &dead_philo);
	start_simul = time_stamp();
	while (++index < arguments->nbr_philosophers)
	{
		philo[index].time_last_meal = start_simul;
		if (pthread_create(&threads[index], NULL, dinner, &philo[index]) != 0)
			return (create_failure(threads, &mutex.dead_lock, &dead_philo,
					(index - 1)));
	}
	while (--index >= 0)
		pthread_join(threads[index], NULL);
	free_mutexes(&mutex, arguments->nbr_philosophers);
	return (0);
}
