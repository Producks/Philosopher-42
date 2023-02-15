/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:11:03 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/14 02:20:20 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../include/struct.h"
#include "../include/simulation.h"
#include "../include/utils.h"

void	philo_wait_till_death(t_philo *philo)
{
	int	sleep_time;

	pthread_mutex_lock(&philo->params->write);
	pthread_mutex_lock(&philo->params->dead_check);
	sleep_time = ((philo->params->time_to_die - (time_stamp() - philo->time_last_meal)) * 1000);
	if (sleep_time < 0)
		sleep_time = 0;
	usleep(sleep_time);
	if (philo->params->dead == false)
	{
		philo->params->dead = true;
		printf(RED "%ld %d died 💀\n",
			(time_stamp() - philo->params->start_simul), philo->id);
		philo->time_of_death = (time_stamp() - philo->params->start_simul);
		philo->params->log = philo->id - 1;
	}
	pthread_mutex_unlock(&philo->params->write);
	pthread_mutex_unlock(&philo->params->dead_check);
}

void	print_philo_state(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->params->write);
	if (check_death(philo) == true)
	{
		pthread_mutex_unlock(&philo->params->write);
		return ;
	}
	else if (flag == 0)
		printf("%ld %d has taken a fork\n", (time_stamp() - philo->params->start_simul), philo->id);
	else if (flag == 1)
		printf("%ld %d is eating\n",
			(time_stamp() - philo->params->start_simul), philo->id);
	else if (flag == 2)
		printf("%ld %d is sleeping\n",
			(time_stamp() - philo->params->start_simul), philo->id);
	else
		printf("%ld %d is thinking\n",
			(time_stamp() - philo->params->start_simul), philo->id);
	pthread_mutex_unlock(&philo->params->write);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_philo_state(philo, 0);
	//print_fork(philo, (time_stamp() - philo->params->start_simul), philo->id);
	pthread_mutex_lock(philo->second_fork);
	print_philo_state(philo, 0);
	//print_fork(philo, (time_stamp() - philo->params->start_simul), philo->id);
	if (philo->params->time_to_eat + (time_stamp() - philo->time_last_meal) >= philo->params->time_to_die)
	{
		philo_wait_till_death(philo);
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return ;
	}
	print_philo_state(philo, 1);
	//print_eat(philo, (time_stamp() - philo->params->start_simul), philo->id);
	usleep(philo->params->time_to_eat * 1000);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	philo->time_last_meal = time_stamp();
	philo->num_times_eaten++;
}

void	philo_sleep(t_philo *philo)
{
	unsigned long int	current;

	print_philo_state(philo, 2);
	//print_sleep(philo, (time_stamp() - philo->params->start_simul), philo->id);
	current = time_stamp();
	if (philo->params->time_to_sleep - (current - philo->time_last_meal) >= philo->params->time_to_die)
	{
		philo_wait_till_death(philo);
		return ;
	}
	usleep(1000 * philo->params->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	int	think_time;

	print_philo_state(philo, 3);
	//print_think(philo, (time_stamp() - philo->params->start_simul), philo->id);
	think_time = (philo->params->time_to_die - (time_stamp() - philo->time_last_meal) - 500) * 1000;
	if (think_time < 0)
		return ;
	usleep(think_time);
}
