/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:35:29 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/07 19:55:45 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/struct.h"
#include "../include/utils.h"

int	ft_atoi(const char *str)
{
	long	result;

	result = 0;
	if (*str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		result = result * 10 + (*str - 48);
		if (result > INT_MAX)
			return (-1);
		str++;
	}
	return ((int)result);
}

unsigned long int	time_stamp(void)
{
	struct timeval	ms;

	gettimeofday(&ms, 0);
	return (ms.tv_sec * 1000 + ms.tv_usec / 1000);
}

void	print_philo_state(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->params->write);
	if (philo->params->dead == true)
	{
		pthread_mutex_unlock(&philo->params->write);
		return ;
	}
	else if (flag == 0)
		printf(CYN "%ld %d has taken a fork 🍴\n",
			(time_stamp() - philo->params->start_simul), philo->id);
	else if (flag == 1)
		printf(YEL "%ld %d is eating 🍝\n",
			(time_stamp() - philo->params->start_simul), philo->id);
	else if (flag == 2)
		printf(BLU "%ld %d is sleeping 💤\n",
			(time_stamp() - philo->params->start_simul), philo->id);
	else
		printf(GRN "%ld %d is thinking 🤔\n",
			(time_stamp() - philo->params->start_simul), philo->id);
	pthread_mutex_unlock(&philo->params->write);
}

void	philo_sleep(t_philo *philo)
{
	unsigned long int	current;

	print_philo_state(philo, 2);
	current = time_stamp();
	while (time_stamp() - current < philo->params->time_to_sleep)
		usleep(1000);
}
