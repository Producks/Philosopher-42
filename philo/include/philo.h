/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 22:58:26 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/15 21:18:06 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "mutex.h"
# include "struct.h"

typedef struct s_philo
{
	int					id;
	int					num_times_eaten;
	int					time_last_meal;
	int					time_of_death;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	pthread_mutex_t		*write_lock;
	bool				*dead;
	pthread_mutex_t		*dead_lock;
	t_sim_params		sim_params;
}	t_philo;

void	init_philo(t_arguments *arguments, t_philo *philo,
			t_mutex *mutex, bool *dead_philo);

#endif