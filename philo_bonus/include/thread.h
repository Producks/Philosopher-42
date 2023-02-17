/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:46:18 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/17 04:57:07 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include "struct.h"
# include <semaphore.h>
# include <stdbool.h>

typedef struct s_philo
{
	int			id;
	int			num_times_eaten;
	bool		even;
	bool		*dead;
	long int 	time_last_meal;
	long int	*start_simul;
	sem_t		*write;
	sem_t		*dead_check;
	sem_t		*forks;
	sem_t		*availability;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nbr_times_eat;
}	t_philo;

void	init_thread(t_hold *temp);

#endif