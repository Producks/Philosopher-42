/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:08:54 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/08 15:18:47 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/struct.h"

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

int	check_atoi_error(t_params *params)
{
	if (params->nbr_philosophers > 200 || params->nbr_philosophers < 2)
		return (print_error("Error: over 200 or under 2 nbr of philosopher"));
	if (params->nbr_philosophers < 0 || params->nbr_times_eat < 0
		|| params->time_to_die < 0 || params->time_to_eat < 0
		|| params->time_to_sleep < 0)
		return (print_error("Error: argument over MAX_INT"));
	return (0);
}

int	parsing_argv_error(const char *str)
{
	int	index;

	index = 0;
	if (!str[index])
		return (print_error("Error: argument is empty"));
	if (str[index] == '-')
		return (print_error("Error: integer is negative"));
	if (str[index] == '+')
		index++;
	while (str[index])
	{
		if (str[index] < 48 || str[index] > 57)
			return (print_error("Error: argument is not a nbr"));
		index++;
	}
	return (0);
}

int	mutex_init_failure(t_params *params, int index)
{
	while (index >= 0)
	{
		pthread_mutex_destroy(&params->fork[index]);
		index--;
	}
	return (print_error("Error: mutex init failed"));
}
