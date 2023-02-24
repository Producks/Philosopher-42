/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:11:03 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/24 12:09:07 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "arguments.h"
#include "philo.h"
#include "utils.h"

/*A philo is about to die, wait till the moment of death
to announce it. Use 2 semaphores to remove race conditions/data races.
Also set philo->dead to true so simulation end for everyone*/
void	philo_wait_till_death(t_philo *philo)
{
	int	sleep_time;

	sem_wait(philo->write);
	sem_wait(philo->dead_check);
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
	sem_post(philo->write);
	sem_post(philo->dead_check);
}

/*Print the action/state of the philo, use a semaphore to
make sure only one print so there no overlap(data races)*/
void	print_philo_state(t_philo *philo, int flag)
{
	sem_wait(philo->write);
	if (check_death(philo) == true)
	{
		sem_post(philo->write);
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
	sem_post(philo->write);
}

/*Function that handle everything that has to do with eating.
Uses multiples semaphores to avoid race condition. Also check
if the philo has enough time to eat*/
void	philo_eat(t_philo *philo)
{
	sem_wait(philo->availability);
	sem_wait(philo->forks);
	print_philo_state(philo, 0);
	sem_wait(philo->forks);
	print_philo_state(philo, 0);
	if (philo->sim_params.time_to_eat + (time_stamp()
			- philo->time_last_meal) >= philo->sim_params.time_to_die)
	{
		philo_wait_till_death(philo);
		sem_post(philo->forks);
		sem_post(philo->forks);
		sem_post(philo->availability);
		return ;
	}
	print_philo_state(philo, 1);
	usleep(philo->sim_params.time_to_eat * 1000);
	sem_post(philo->forks);
	sem_post(philo->forks);
	sem_post(philo->availability);
	philo->time_last_meal = time_stamp();
	philo->num_times_eaten++;
}

/*Handle the sleep part of the simulation, doesn't require a
semaphores outside of philo_state. Check if the philo has time to sleep*/
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

/*Handle the think part of the simulation, doesn't require a semaphores
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
