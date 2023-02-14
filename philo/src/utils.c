/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:35:29 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/12 00:26:00 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <limits.h>
#include "../include/philo_action.h"

unsigned long int	time_stamp(void)
{
	struct timeval	ms;

	gettimeofday(&ms, 0);
	return (ms.tv_sec * 1000 + ms.tv_usec / 1000);
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