/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:11:03 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/24 11:45:05 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "arguments.h"
#include "philo.h"
#include "utils.h"

/*A philo is about to die, wait till the moment of death
to announce it. Use 2 mutex to remove race conditions/data races.
Also set philo->dead to true so simulation end for everyone*/
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
	}
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_unlock(philo->dead_lock);
}

/*Print the action/state of the philo, use a mutex to
make sure only one print so there no overlap(data races)*/
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

/*Function that handle everything that has to do with eating.
Uses multiples mutexes to avoid race condition. Also check
if the philo has enough time to eat*/
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

/*Handle the sleep part of the simulation, doesn't require a
mutex outside of philo_state. Check if the philo has time to sleep*/
void	philo_sleep(t_philo *philo)
{
	unsigned int	current;

	print_philo_state(philo, 2);
	current = time_stamp();
	if ((time_stamp() - philo->time_last_meal)
		>= (philo->sim_params.time_to_die - philo->sim_params.time_to_sleep))
	{
		philo_wait_till_death(philo);
		return ;
	}
	usleep(1000 * philo->sim_params.time_to_sleep);
}

/*Handle the think part of the simulation, doesn't require a mutex
outside of print_philo state. Will think until there 500ms left.
Can be easily adjusted for another value depending on the computer*/
void	philo_think(t_philo *philo)
{
	int	think_time;

	print_philo_state(philo, 3);
	think_time = philo->sim_params.time_to_die
		- (time_stamp() - philo->time_last_meal)
		- philo->sim_params.time_to_eat - 200;
	if (think_time < 0)
		return ;
	usleep(think_time * 1000);
}
