/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:46:18 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/12 16:04:40 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <semaphore.h>

typedef struct s_philo
{
	int			id;
	int			num_times_eaten;
	bool		even;
	long int 	time_last_meal;
	sem_t		*write;
	sem_t		*dead_check;
}	t_philo;

#endif