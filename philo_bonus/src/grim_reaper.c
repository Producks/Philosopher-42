/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 01:20:10 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/27 04:52:14 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "semaphore.h"
#include "utils.h"

/*Check if all philo ate*/
static int	check_all_ate(t_philo *philo,
	t_sema *semaphores, t_arguments *arguments)
{
	int	index;
	int	meal_count;

	if (arguments->sim_params.nbr_times_eat == 0)
		return (false);
	index = 0;
	meal_count = 0;
	while (index < arguments->nbr_philosophers)
	{
		sem_wait(philo[index].meal);
		meal_count = philo[index].num_times_eaten;
		sem_post(philo[index].meal);
		if (meal_count != arguments->sim_params.nbr_times_eat)
			return (false);
		index++;
	}
	return (true);
}

/*GG noob*/
static void	death_is_upon_us(t_philo *philo,
	t_sema *semaphores, int index)
{
	printf(RED "%d %d died 💀\n", time_stamp(), philo[index].id);
	sem_wait(philo->dead_check);
	*philo->dead = true;
	sem_post(philo->dead_check);
	sem_post(philo->write);
}

/*The grim reaper looks if anyone is dead*/
void	grim_reaper(t_philo *philo, t_sema *semaphores,
	unsigned int *start_simul, t_arguments *arguments)
{
	int		index;
	int		last_meal;

	index = 0;
	*start_simul = time_stamp();
	sem_post(semaphores->launch);
	while (true)
	{
		if (check_all_ate(philo, semaphores, arguments) == true)
			break ;
		sem_wait(philo[index].meal);
		last_meal = philo[index].time_last_meal;
		last_meal = 0;
		sem_post(philo[index].meal);
		if (time_stamp() - last_meal >= arguments->sim_params.time_to_die)
		{
			sem_wait(philo->write);
			death_is_upon_us(philo, semaphores, index);
			break ;
		}
		index = (index + 1) % arguments->nbr_philosophers;
		usleep(100);
	}
}
