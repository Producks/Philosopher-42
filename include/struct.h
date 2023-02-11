/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:20:06 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/10 18:54:02 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	int					id;
	int					num_times_eaten;
	bool				even;
	long int			time_last_meal;
	long int			time_of_death;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	struct s_params		*params;
}	t_philo;

typedef struct s_params
{
	int					nbr_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_times_eat;
	long int			start_simul;
	bool				dead;
	t_philo				param[200];
	pthread_mutex_t		fork[200];
	pthread_mutex_t		write;
	pthread_mutex_t		dead_check;
	int					log;
}	t_params;

#endif