/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:53:00 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/15 21:33:23 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mutex.h"
#include "../include/utils.h"
#include <stdio.h>

int	mutex_init_failure(pthread_mutex_t *fork, int index)
{
	while (index >= 0)
	{
		pthread_mutex_destroy(&fork[index]);
		index--;
	}
	return (print_error("Error: mutex init failed"));
}

void	free_mutexes(t_mutex *mutex, int nbr_philosopher)
{
	int	index;

	index = 0;
	while (index < nbr_philosopher)
	{
		pthread_mutex_destroy(&mutex->fork[index]);
		index++;
	}
	pthread_mutex_destroy(&mutex->write_lock);
	pthread_mutex_destroy(&mutex->dead_lock);
}

int	init_mutex(t_mutex *mutex, int nbr_philosopher)
{
	int	index;

	index = 0;
	while (index < nbr_philosopher)
	{
		if (pthread_mutex_init(&mutex->fork[index], NULL) != 0)
			return (mutex_init_failure(mutex->fork, (index - 1)));
		index++;
	}
	if (pthread_mutex_init(&mutex->write_lock, NULL) != 0)
		return (mutex_init_failure(mutex->fork, (index - 1)));
	if (pthread_mutex_init(&mutex->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&mutex->write_lock);
		return (mutex_init_failure(mutex->fork, (index - 1)));
	}
	return (0);
}
