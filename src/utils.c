/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:35:29 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/06 22:24:27 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <sys/time.h>
#include <stdio.h>
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

// void	print_philo_state(t_philo *philo, int flag, char *message)
// {
// 	pthread_mutex_lock(&philo->params->write);
// 	if (flag != 1)
// 	{
// 		printf("%ld \n", time_stamp() - philo->params->start_simul);
// 		printf("%d \n", philo->id);
// 		printf("%s", message);
// 	}
// 	pthread_mutex_unlock(&philo->params->write);
// }

void	print_philo_state(t_philo *philo, int flag, char *message)
{
	pthread_mutex_lock(&philo->params->write);
	if (flag == 0)
		printf(CYN "%ld %d has taken a fork 🍴\n", (time_stamp() - philo->params->start_simul), philo->id);
	else if (flag == 1)
		printf(YEL "%ld %d is eating 🍝\n", time_stamp(), philo->id);
	else if (flag == 2)
		printf(BLU "%ld %d is sleeping 💤\n", time_stamp(), philo->id);
	else if (flag == 3)
		printf(GRN "%ld %d is thinking 🤔\n", time_stamp(), philo->id);
	else
		printf(RED "%ld %d died 💀\n", time_stamp(), philo->id);
	pthread_mutex_unlock(&philo->params->write);
}