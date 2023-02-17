/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:09:45 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/16 23:32:37 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_H
# define MUTEX_H

# include <pthread.h>

typedef struct s_mutex
{
	pthread_mutex_t	fork[200];
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	launch;
}	t_mutex;

int		init_mutex(t_mutex *mutex, int nbr_philosopher);
void	free_mutexes(t_mutex *mutex, int nbr_philosopher);

#endif