/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:07:16 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/17 04:55:52 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stdio.h>
#include "../include/semaphore.h"

void	destroy_sem(t_sema *semaphore)
{
	sem_close(&semaphore->forks);
	sem_close(&semaphore->dead_check);
	sem_close(&semaphore->write);
}

void	init_sem(t_sema	*semaphore, int nbr_of_philo)
{
	sem_init(&semaphore->write, 0, 1);
	sem_init(&semaphore->dead_check, 0, 1);
	sem_init(&semaphore->forks, 0, nbr_of_philo);
	sem_init(&semaphore->availability, 0, nbr_of_philo / 2);
	return ;
}