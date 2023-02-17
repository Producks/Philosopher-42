/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:37:27 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/17 00:19:55 by ddemers          ###   ########.fr       */
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

static void	dinner(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep((philo->sim_params.time_to_eat * 1000 / 2));
	while (check_death(philo) != true)
	{
		philo_eat(philo);
		if (philo->num_times_eaten == philo->sim_params.nbr_times_eat)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
}

static void	*one(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(philo->first_fork);
	print_philo_state(philo, 0);
	philo_wait_till_death(philo);
	pthread_mutex_unlock(philo->first_fork);
	return (NULL);
}

static int	handle_one(t_philo *philo, pthread_t *threads, t_mutex *mutex)
{
	if (pthread_create(&threads[0], NULL, one, &philo[0]) != 0)
	{
		free_mutexes(mutex, 1);
		return (print_error("Error: Enomem create failure"));
	}
	pthread_join(threads[0], NULL);
	free_mutexes(mutex, 1);
	return (0);
}

static void	*launch(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(philo->launch);
	pthread_mutex_unlock(philo->launch);
	philo->time_last_meal = *philo->start_simul;
	dinner(philo);
	return (NULL);
}

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
	if (arguments->nbr_philosophers == 1)
		return (handle_one(philo, threads, &mutex));
	pthread_mutex_lock(&mutex.launch);
	while (++index < arguments->nbr_philosophers)
	{
		philo[index].start_simul = &start_simul;
		if (pthread_create(&threads[index], NULL, launch, &philo[index]) != 0)
			return (create_failure(threads, &mutex.dead_lock, &dead_philo,
					(index - 1)));
	}
	start_simul = time_stamp();
	pthread_mutex_unlock(&mutex.launch);
	while (--index >= 0)
		pthread_join(threads[index], NULL);
	free_mutexes(&mutex, arguments->nbr_philosophers);
	return (0);
}
