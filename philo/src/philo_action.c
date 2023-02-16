/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:11:03 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/15 21:12:25 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../include/struct.h"
#include "../include/simulation.h"
#include "../include/utils.h"
#include "../include/philo.h"

void	philo_wait_till_death(t_philo *philo)
{
	int	sleep_time;

	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_lock(philo->dead_lock);
	sleep_time = ((philo->sim_params.time_to_die
				- (time_stamp() - philo->time_last_meal)) * 1000);
	if (sleep_time < 0)
		sleep_time = 0;
	usleep(sleep_time);
	if (*philo->dead == false)
	{
		*philo->dead = true;
		printf(RED "%d %d died 💀\n", time_stamp(), philo->id);
		philo->time_of_death = time_stamp();
	}
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_unlock(philo->dead_lock);
}

void	print_philo_state(t_philo *philo, int flag)
{
	pthread_mutex_lock(philo->write_lock);
	if (check_death(philo) == true)
	{
		pthread_mutex_unlock(philo->write_lock);
		return ;
	}
	else if (flag == 0)
		printf("%d %d has taken a fork\n", time_stamp(), philo->id);
	else if (flag == 1)
		printf("%d %d is eating\n", time_stamp(), philo->id);
	else if (flag == 2)
		printf("%d %d is sleeping\n", time_stamp(), philo->id);
	else
		printf("%d %d is thinking\n", time_stamp(), philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_philo_state(philo, 0);
	pthread_mutex_lock(philo->second_fork);
	print_philo_state(philo, 0);
	if (philo->sim_params.time_to_eat + (time_stamp()
			- philo->time_last_meal) >= philo->sim_params.time_to_die)
	{
		philo_wait_till_death(philo);
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return ;
	}
	print_philo_state(philo, 1);
	usleep(philo->sim_params.time_to_eat * 1000);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	philo->time_last_meal = time_stamp();
	philo->num_times_eaten++;
}

void	philo_sleep(t_philo *philo)
{
	unsigned int	current;

	print_philo_state(philo, 2);
	current = time_stamp();
	if (philo->sim_params.time_to_sleep - (current
			- philo->time_last_meal) >= philo->sim_params.time_to_die)
	{
		philo_wait_till_death(philo);
		return ;
	}
	usleep(1000 * philo->sim_params.time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	int	think_time;

	print_philo_state(philo, 3);
	think_time = (philo->sim_params.time_to_die - (time_stamp()
				- philo->time_last_meal) - 500) * 1000;
	if (think_time < 0)
		return ;
	usleep(think_time);
}
