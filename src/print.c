/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 10:27:40 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/11 11:21:09 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/struct.h"
#include "../include/simulation.h"

static void put_nbr(unsigned long int nbr)
{
    if (nbr > 9)
        put_nbr(nbr / 10);
    write(1, &"0123456789"[10 % nbr], 1);
}

void	print_fork(t_philo *philo, unsigned long int time, int id)
{
	pthread_mutex_lock(&philo->params->write);
	if (check_death(philo) == true)
	{
		pthread_mutex_unlock(&philo->params->write);
		return ;
	}
	put_nbr(time);
	write(1, " ", 1);
	put_nbr(id);
	write(1, " has taken a fork\n", 18);
	pthread_mutex_unlock(&philo->params->write);
}

void	print_eat(t_philo *philo, unsigned long int time, int id)
{
	pthread_mutex_lock(&philo->params->write);
	if (check_death(philo) == true)
	{
		pthread_mutex_unlock(&philo->params->write);
		return ;
	}
	put_nbr(time);
	write(1, " ", 1);
	put_nbr(id);
	write(1, " is eating\n", 11);
	pthread_mutex_unlock(&philo->params->write);
}

void	print_sleep(t_philo *philo, unsigned long int time, int id)
{
	pthread_mutex_lock(&philo->params->write);
	if (check_death(philo) == true)
	{
		pthread_mutex_unlock(&philo->params->write);
		return ;
	}
	put_nbr(time);
	write(1, " ", 1);
	put_nbr(id);
	write(1, " is sleeping\n", 13);
	pthread_mutex_unlock(&philo->params->write);
}

void	print_think(t_philo *philo, unsigned long int time, int id)
{
	pthread_mutex_lock(&philo->params->write);
	if (check_death(philo) == true)
	{
		pthread_mutex_unlock(&philo->params->write);
		return ;
	}
	put_nbr(time);
	write(1, " ", 1);
	put_nbr(id);
	write(1, " is thinking\n", 13);
	pthread_mutex_unlock(&philo->params->write);
}
