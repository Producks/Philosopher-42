/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:20:06 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/06 18:02:32 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>

typedef struct s_philo
{
	int					id;
	unsigned long int	time_last_meal;
	int					num_times_eaten;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_params		*params;
}	t_philo;

typedef struct s_params
{
	int				nbr_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_times_eat;
	unsigned long int	start_simul;
	t_philo			param[200];
	pthread_mutex_t	fork[200];
	pthread_mutex_t	write;
}	t_params;

#endif