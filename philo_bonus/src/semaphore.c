/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:07:16 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/27 02:32:20 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <fcntl.h>
#include "semaphore.h"
#include "utils.h"
#include <stdio.h>

/*LOL*/
void	init_meal_sema_message(int index, char *str, char *message)
{
	int		i;
	int		divider;

	i = 0;
	while (*message)
	{
		str[i] = *message;
		message++;
		i++;
	}
	i = 0;
	divider = 100;
	str[5] = (index / divider) + 48;
	index %= divider;
	divider = 10;
	str[6] = (index / divider) + 48;
	index %= divider;
	divider = 1;
	str[7] = (index / divider) + 48;
	index %= divider;
	str[8] = '\0';
}

/*Really really important! If we don't free them we can't run the program
again*/
void	destroy_sem(t_sema *semaphores, int nbr_of_philo)
{
	int		index;
	char	message[9];

	index = 0;
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
	while (index < nbr_of_philo)
	{
		init_meal_sema_message(index, message, "/meal");
		sem_close(semaphores->meal[index]);
		sem_unlink(message);
		index++;
	}
}

/*Similar to mutex, but has to unlink to have no issues later*/
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

int	init_meal_sem(t_sema *semaphores, int nbr_of_philo)
{
	int		index;
	int		index_two;
	char	message[8];

	index = 0;
	while (index < nbr_of_philo)
	{
		init_meal_sema_message(index, message, "/meal");
		semaphores->meal[index] = sem_open(message, O_CREAT, 0644, 1);
		if (semaphores->meal[index] == SEM_FAILED)
		{
			index_two = 0;
			while (index_two < index)
			{
				init_meal_sema_message(index_two, message, "/meal");
				sem_unlink(message);
				sem_close(semaphores->meal[index_two]);
				index_two++;
			}
			return (-1);
		}
		index++;
	}
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
	if (init_meal_sem(semaphores, nbr_of_philo) == -1)
		return (sem_failure(semaphores, 4));
	return (0);
}
