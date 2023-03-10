/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:37:27 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/27 01:17:28 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "utils.h"
#include "philo_action.h"
#include "error.h"
#include "grim_reaper.h"

/*The simulation function loops until the philosophers have eaten enough
times or one dies. To ensure that even-numbered philosophers eat later
than odd-numbered ones,the odd-numbered philosophers are allowed to eat first,
and then the even-numbered philosophers are allowed to eat. The README file
provides further details on how my solution works.*/
static void	dinner(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep((philo->sim_params.time_to_eat * 1000 / 2));
	while (philo_check_death(philo) != true)
	{
		philo_eat(philo);
		if (philo->num_times_eaten == philo->sim_params.nbr_times_eat)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
}

/*Function incase there 1 philo, really annoying
since the project should have a minimum of two*/
static void	*one(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(philo->first_fork);
	print_philo_state(philo, 0);
	usleep(philo->sim_params.time_to_die * 1000);
	printf(RED "%d %d died 💀\n", time_stamp(), philo->id);
	pthread_mutex_unlock(philo->first_fork);
	return (NULL);
}

/*Handle if there only 1 philo*/
static int	handle_one(t_philo *philo, pthread_t *threads, t_mutex *mutex)
{
	if (pthread_create(&threads[0], NULL, one, &philo[0]) != 0)
	{
		free_mutexes(mutex, 1);
		return (print_error("Error: Enomem create failure"));
	}
	pthread_join(threads[0], NULL);
	free_mutexes(mutex, 1);
	return (0);
}

/*Launch all threads at the same time!
This save a bit of time over calling dinner right away.
If we had access to pthread_barrier_t this would be even better*/
static void	*launch(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(philo->launch);
	pthread_mutex_unlock(philo->launch);
	pthread_mutex_lock(philo->meal_lock);
	philo->time_last_meal = *philo->start_simul;
	pthread_mutex_unlock(philo->meal_lock);
	dinner(philo);
	return (NULL);
}

/*This function was readable before I had to deal with the norminette*/
int	start_simulation(t_arguments *arguments, int index)
{
	unsigned int		start_simul;
	bool				dead_philo;
	t_mutex				mutex;
	t_philo				philo[200];
	pthread_t			threads[200];

	dead_philo = false;
	if (init_mutex(&mutex, arguments->nbr_philosophers) == -1)
		return (-1);
	init_philo(arguments, philo, &mutex, &dead_philo);
	if (arguments->nbr_philosophers == 1)
		return (handle_one(philo, threads, &mutex));
	pthread_mutex_lock(&mutex.launch);
	while (++index < arguments->nbr_philosophers)
	{
		philo[index].start_simul = &start_simul;
		if (pthread_create(&threads[index], NULL, launch, &philo[index]) != 0)
			return (pfail(threads, &mutex.dead_lock, &dead_philo, (index - 1)));
	}
	grim_reaper(philo, &mutex, &start_simul, arguments);
	while (--index >= 0)
		pthread_join(threads[index], NULL);
	free_mutexes(&mutex, arguments->nbr_philosophers);
	return (generate_log(dead_philo, start_simul, *arguments));
}
