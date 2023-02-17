/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:35:29 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/16 23:25:38 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <limits.h>
#include "../include/philo.h"
#include "../include/philo_action.h"

bool	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == true)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (false);
	}
}

unsigned int	time_stamp(void)
{
	static struct timeval	start_simul = {0, 0};
	struct timeval			ms;

	if (start_simul.tv_sec == 0)
		gettimeofday(&start_simul, 0);
	gettimeofday(&ms, 0);
	return ((ms.tv_sec - start_simul.tv_sec) * 1000
		+ (ms.tv_usec - start_simul.tv_usec) / 1000);
}

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

int	print_error(const char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		write(2, &str[index], 1);
		index++;
	}
	write(2, "\n", 1);
	return (-1);
}
