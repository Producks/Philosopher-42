/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:10:56 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/27 00:47:39 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "arguments.h"
#include "philo.h"
#include "mutex.h"
#include "utils.h"

static int	check_all_ate(t_philo *philo,
	t_mutex *mutex, t_arguments *arguments)
{
	int	index;
	int	meal_count;

	if (arguments->sim_params.nbr_times_eat == 0)
		return (false);
	index = 0;
	meal_count = 0;
	while (index < arguments->nbr_philosophers)
	{
		pthread_mutex_lock(&mutex->meal_lock[index]);
		meal_count = philo[index].num_times_eaten;
		pthread_mutex_unlock(&mutex->meal_lock[index]);
		if (meal_count != arguments->sim_params.nbr_times_eat)
			return (false);
		index++;
	}
	return (true);
}

static void	death_is_upon_us(t_philo *philo, t_mutex *mutex, int index)
{
	printf(RED "%d %d died 💀\n", time_stamp(), philo[index].id);
	pthread_mutex_lock(&mutex->dead_lock);
	*philo->dead = true;
	pthread_mutex_unlock(&mutex->dead_lock);
	pthread_mutex_unlock(&mutex->write_lock);
}

void	grim_reaper(t_philo *philo, t_mutex *mutex,
	unsigned int *start_simul, t_arguments *arguments)
{
	int		index;
	int		last_meal;

	index = 0;
	*start_simul = time_stamp();
	pthread_mutex_unlock(&mutex->launch);
	while (true)
	{
		if (check_all_ate(philo, mutex, arguments) == true)
			break ;
		pthread_mutex_lock(&mutex->meal_lock[index]);
		last_meal = philo[index].time_last_meal;
		pthread_mutex_unlock(&mutex->meal_lock[index]);
		if (time_stamp() - last_meal >= arguments->sim_params.time_to_die)
		{
			pthread_mutex_lock(&mutex->write_lock);
			death_is_upon_us(philo, mutex, index);
			break ;
		}
		index = (index + 1) % arguments->nbr_philosophers;
		usleep(100);
	}
}

// void	grim_reaper(t_philo *philo, t_mutex *mutex,
//		unsigned int *start_simul, t_arguments *arguments)
// {
// 	int		index;
// 	int		last_meal;
// 	int		eating_count;
// 	bool	simulation_end;

// 	*start_simul = time_stamp();
// 	simulation_end = false;
// 	printf("%d\n", eating_count);
// 	pthread_mutex_unlock(&mutex->launch);
// 	while (!simulation_end)
// 	{
// 		index = 0;
// 		simulation_end = false;
// 		while (index < arguments->nbr_philosophers)
// 		{
// 			usleep(100);
// 			pthread_mutex_lock(&mutex->meal_lock[index]);
// 			last_meal = philo[index].time_last_meal;
// 			eating_count = philo[index].num_times_eaten;
// 			pthread_mutex_unlock(&mutex->meal_lock[index]);
// 			if (eating_count == philo->sim_params.nbr_times_eat)
// 			{
// 				simulation_end = true;
// 				index = (index + 1) % arguments->nbr_philosophers;
// 				continue ;
// 			}
// 			// if (time_stamp() - last_meal
//	>= arguments->sim_params.time_to_die)
// 			// {
// 			// 	pthread_mutex_lock(&mutex->write_lock);
// 			// 	death_is_upon_us(philo, mutex, index);
// 			// 	simulation_end = true;
// 			// 	break ;
// 			// }
// 			//simulation_end &= false;
// 			//index = (index + 1) % arguments->nbr_philosophers;
// 		}
// 	}
// }