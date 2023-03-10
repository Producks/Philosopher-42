/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 22:58:26 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/26 15:03:26 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include "mutex.h"
# include "arguments.h"

typedef struct s_philo
{
	int					id;
	int					num_times_eaten;
	int					time_last_meal;
	int					time_of_death;
	unsigned int		*start_simul;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	pthread_mutex_t		*meal_lock;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*launch;
	bool				*dead;
	pthread_mutex_t		*dead_lock;
	t_sim_params		sim_params;
}	t_philo;

void	init_philo(t_arguments *arguments, t_philo *philo,
			t_mutex *mutex, bool *dead_philo);

#endif