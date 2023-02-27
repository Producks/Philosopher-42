/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 22:58:26 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/27 04:27:42 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include "arguments.h"
# include "semaphore.h"

typedef struct s_philo
{
	int					id;
	int					num_times_eaten;
	int					time_last_meal;
	int					time_of_death;
	unsigned int		*start_simul;
	sem_t				*write;
	sem_t				*dead_check;
	sem_t				*forks;
	sem_t				*availability;
	sem_t				*launch;
	sem_t				*meal;
	bool				*dead;
	t_sim_params		sim_params;
}	t_philo;

void	init_philo(t_arguments *arguments, t_philo *philo,
			t_sema *semaphores, bool *dead_philo);

#endif