/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:35:29 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/17 17:18:28 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <limits.h>
#include "philo.h"

/*Check if a philo died, use a mutex to avoid race condition*/
bool	check_death(t_philo *philo)
{
	sem_wait(philo->dead_check);
	if (*philo->dead == true)
	{
		sem_post(philo->dead_check);
		return (true);
	}
	else
	{
		sem_post(philo->dead_check);
		return (false);
	}
}

/*Function to get the time, has a static struct which
will be our start simulation time the first time we call it*/
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

/*Your typical atoi function*/
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

/*Print the string we sent it to the stderr*/
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
