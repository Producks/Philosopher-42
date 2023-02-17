/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:46:12 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/17 04:57:28 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include "../include/struct.h"
#include "../include/thread.h"
#include "../include/simulation.h"
#include "../include/utils.h"

static void create_threads(t_philo philo[200], int nbr_philo, long int *start_simul)
{
	int			index;
	pthread_t	threads[200];

	index = 0;
	*start_simul = time_stamp();
	while (index < nbr_philo)
	{
		pthread_create(&threads[index], NULL, dinner, &philo[index]);
		index++;	
	}
	index = 0;
	while (index < nbr_philo)
	{
		pthread_join(threads[index], NULL);
		index++;
	}
}

void	init_thread(t_hold *temp)
{
	int			index;
	int			philo_id;
	t_philo		philo[200];
	long int	start_simul;
	bool		dead;

	index = 0;
	philo_id = 1;
	dead = false;
	while (index < temp->rules.nbr_philosophers)
	{
		philo[index].id = philo_id;
		if (philo_id % 2 == 0)
			philo[index].even = true;
		else
			philo[index].even = false;
		philo[index].num_times_eaten = 0;
		philo[index].time_to_die = temp->rules.time_to_die;
		philo[index].time_to_eat = temp->rules.time_to_eat;
		philo[index].time_to_sleep = temp->rules.time_to_sleep;
		philo[index].nbr_times_eat = temp->rules.nbr_times_eat;
		philo[index].write = &temp->semaphore.write;
		philo[index].dead_check = &temp->semaphore.dead_check;
		philo[index].forks = &temp->semaphore.forks;
		philo[index].availability = &temp->semaphore.availability;
		philo[index].dead = &dead;
		philo[index].start_simul = &start_simul;
		philo_id++;
		index++;
	}
	create_threads(philo, temp->rules.nbr_philosophers, &start_simul);
	printf("%d\n", dead);
}