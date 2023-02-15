/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:11:45 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/14 12:44:38 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../include/thread.h"
#include "../include/utils.h"
#include "../include/simulation.h"

# define RED   "\x1B[31m"

static void	philo_wait_till_death(t_philo *philo)
{
	int	sleep_time;

	sem_wait(philo->write);
	sem_wait(philo->dead_check);
	sleep_time = ((philo->time_to_die - (time_stamp() - philo->time_last_meal)) * 1000);
	if (sleep_time < 0)
		sleep_time = 0;
	usleep(sleep_time);
	if (*philo->dead == false)
	{
		*philo->dead = true;
		printf(RED "%ld %d died 💀\n",
			(time_stamp() - *philo->start_simul), philo->id);
	}
	sem_post(philo->write);
	sem_post(philo->dead_check);
}

static void	print_philo_state(t_philo *philo, int flag)
{
	sem_wait(philo->write);
	if (check_death(philo) == true)
	{
		sem_post(philo->write);
		return ;
	}
	else if (flag == 0)
		printf("%ld %d has taken a fork\n", (time_stamp() - *philo->start_simul), philo->id);
	else if (flag == 1)
		printf("%ld %d is eating\n",
			(time_stamp() - *philo->start_simul), philo->id);
	else if (flag == 2)
		printf("%ld %d is sleeping\n",
			(time_stamp() - *philo->start_simul), philo->id);
	else
		printf("%ld %d is thinking\n",
			(time_stamp() - *philo->start_simul), philo->id);
	sem_post(philo->write);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->forks);
	print_philo_state(philo, 0);
	sem_wait(philo->forks);
	print_philo_state(philo, 0);
	if (philo->time_to_eat + (time_stamp() - philo->time_last_meal) >= philo->time_to_die)
	{
		sem_post(philo->forks);
		sem_post(philo->forks);
		philo_wait_till_death(philo);
		return ;
	}
	print_philo_state(philo, 1);
	usleep(philo->time_to_eat * 1000);
	sem_post(philo->forks);
	sem_post(philo->forks);
	philo->time_last_meal = time_stamp();
	philo->num_times_eaten++;
}

void	philo_sleep(t_philo *philo)
{
	unsigned long int	current;

	print_philo_state(philo, 2);
	//print_sleep(philo, (time_stamp() - philo->start_simul), philo->id);
	current = time_stamp();
	if (philo->time_to_sleep - (current - philo->time_last_meal) >= philo->time_to_die)
	{
		philo_wait_till_death(philo);
		return ;
	}
	usleep(1000 * philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	int	think_time;

	print_philo_state(philo, 3);
	//print_think(philo, (time_stamp() - philo->start_simul), philo->id);
	think_time = (philo->time_to_die - (time_stamp() - philo->time_last_meal) - 500) * 1000;
	if (think_time < 0)
		return ;
	usleep(think_time);
}
