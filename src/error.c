/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:08:54 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/04 04:04:30 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/struct.h"

void	print_error(const char *str)
{
	int	index;

	while (str[index])
	{
		write(2, &str[index], 1);
		index++;
	}
	write(2, "\n", 1);
}

int	check_atoi_error(t_philo *philo)
{
	if (philo->nbr_philosophers > 200 || philo->nbr_philosophers < 2)
	{
		print_error("Error: over 200 or under 2 number of philosopher");
		return (-1);
	}
	if (philo->nbr_philosophers == -1 || philo->nbr_times_eat < 0
		|| philo->time_to_die < 0 || philo->time_to_eat < 0
		|| philo->time_to_die < 0)
	{
		print_error("Error: argument over MAX_INT");
		return (-1);
	}
	return (0);
}
