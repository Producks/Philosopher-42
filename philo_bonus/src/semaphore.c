/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:07:16 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/18 04:48:38 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <fcntl.h>
#include "semaphore.h"
#include "utils.h"
#include <stdio.h>

void	destroy_sem(t_sema *semaphores)
{
	sem_close(semaphores->forks);
	sem_unlink("/forks");
	sem_close(semaphores->write);
	sem_unlink("/write");
	sem_close(semaphores->launch);
	sem_unlink("/launch");
	sem_close(semaphores->dead_check);
	sem_unlink("/dead_check");
	sem_close(semaphores->availability);
	sem_unlink("/availability");
}

static int	sem_failure(t_sema *semaphores, int flag)
{
	if (flag >= 1)
	{
		sem_close(semaphores->forks);
		sem_unlink("/forks");
	}
	if (flag >= 2)
	{
		sem_close(semaphores->write);
		sem_unlink("/write");
	}
	if (flag >= 3)
	{
		sem_close(semaphores->dead_check);
		sem_unlink("/dead_check");
	}
	if (flag >= 4)
	{
		sem_close(semaphores->launch);
		sem_unlink("/launch");
	}
	return (print_error("Error: Sem init failure"));
}

/*
0: The file type is a regular file
6: The owner has read and write permissions
4: Group members have read permissions
4: Other users have read permissions*/
int	init_sem(t_sema	*semaphores, int nbr_of_philo)
{
	semaphores->forks = sem_open("/forks", O_CREAT, 0644, nbr_of_philo);
	if (semaphores->forks == SEM_FAILED)
		return (sem_failure(semaphores, 0));
	semaphores->write = sem_open("/write", O_CREAT, 0644, 1);
	if (semaphores->write == SEM_FAILED)
		return (sem_failure(semaphores, 1));
	semaphores->dead_check = sem_open("/dead_check", O_CREAT, 0644, 1);
	if (semaphores->dead_check == SEM_FAILED)
		return (sem_failure(semaphores, 2));
	semaphores->launch = sem_open("/launch", O_CREAT, 0644, 1);
	if (semaphores->launch == SEM_FAILED)
		return (sem_failure(semaphores, 3));
	semaphores->availability = sem_open("/availability", O_CREAT, 0644,
			(nbr_of_philo / 2));
	if (semaphores->availability == SEM_FAILED)
		return (sem_failure(semaphores, 4));
	return (0);
}
