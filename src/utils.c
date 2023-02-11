/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:35:29 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/10 23:47:28 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/struct.h"
#include "../include/utils.h"
#include "../include/simulation.h"

inline unsigned long int	time_stamp(void)
{
	struct timeval	ms;

	gettimeofday(&ms, 0);
	return (ms.tv_sec * 1000 + ms.tv_usec / 1000);
}

/*later check emoji and collors
200 500 200 200 10*/
void	print_philo_state(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->params->write);
	if (philo->params->dead == true)
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

// void	print_philo_state(t_philo *philo, int flag)
// {
// 	pthread_mutex_lock(&philo->params->write);
// 	if (philo->params->dead == true)
// 	{
// 		pthread_mutex_unlock(&philo->params->write);
// 		return ;
// 	}
// 	else if (flag == 0)
// 		printf(CYN "%ld %d has taken a fork 🍴\n", (time_stamp() - philo->params->start_simul), philo->id);
// 	else if (flag == 1)
// 		printf(YEL "%ld %d is eating 🍝\n",
// 			(time_stamp() - philo->params->start_simul), philo->id);
// 	else if (flag == 2)
// 		printf(BLU "%ld %d is sleeping 💤\n",
// 			(time_stamp() - philo->params->start_simul), philo->id);
// 	else
// 		printf(GRN "%ld %d is thinking 🤔\n",
// 			(time_stamp() - philo->params->start_simul), philo->id);
// 	pthread_mutex_unlock(&philo->params->write);
// }

/**/
void	philo_sleep(t_philo *philo)
{
	unsigned long int	current;

	print_philo_state(philo, 2);
	current = time_stamp();
	if (philo->params->time_to_sleep - (current - philo->time_last_meal) >= philo->params->time_to_die)
	{
		wait_till_death(philo);
		return ;
	}
	usleep(1000 * philo->params->time_to_sleep);
}

/*to do first fork and second fork*/
void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_philo_state(philo, 0);
	pthread_mutex_lock(philo->second_fork);
	print_philo_state(philo, 0);
	if (philo->params->time_to_eat + (time_stamp() - philo->time_last_meal) >= philo->params->time_to_die)
	{
		wait_till_death(philo);
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return ;
	}
	print_philo_state(philo, 1);
	usleep(philo->params->time_to_eat * 1000);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	philo->time_last_meal = time_stamp();
	philo->num_times_eaten++;
}

void	wait_till_death(t_philo *philo)
{
	int	sleep_time;

	pthread_mutex_lock(&philo->params->write);
	pthread_mutex_lock(&philo->params->dead_check);
	sleep_time = ((philo->params->time_to_die - (time_stamp() - philo->time_last_meal)) * 1000);
	if (sleep_time < 0)
		sleep_time = 0;
	usleep(sleep_time);
	if (philo->params->dead == false)
		die(philo);
	pthread_mutex_unlock(&philo->params->write);
	pthread_mutex_unlock(&philo->params->dead_check);
}