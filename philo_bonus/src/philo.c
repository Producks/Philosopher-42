/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 23:03:57 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/18 03:00:08 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "arguments.h"
#include "semaphore.h"

void	init_philo(t_arguments *arguments, t_philo *philo,
	t_sema *semaphores, bool *dead_philo)
{
	int	index;

	index = 0;
	while (index < arguments->nbr_philosophers)
	{
		philo[index].id = index + 1;
		philo[index].forks = semaphores->forks;
		philo[index].write = semaphores->write;
		philo[index].dead_check = semaphores->dead_check;
		philo[index].availability = semaphores->availability;
		philo[index].launch = semaphores->launch;
		philo[index].dead = dead_philo;
		philo[index].num_times_eaten = 0;
		philo[index].sim_params = arguments->sim_params;
		index++;
	}
}
