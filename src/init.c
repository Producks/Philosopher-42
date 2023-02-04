/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:43:39 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/04 04:02:23 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/struct.h"
#include "../include/utils.h"
#include "../include/error.h"
#include "../include/init.h"

static int	check_args(int argc, char **argv)
{
	int	index;

	index = 1;
	while (index != argc)
	{
		if (parsing_argv_error(argv[index]) == false)
			return (-1);
		index++;
	}
	return (0);
}

int	init_params(int argc, char **argv, t_philo *philo)
{
	if (check_args(argc, argv) == -1)
		return (-1);
	philo->nbr_philosophers = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_die = ft_atoi(argv[4]);
	if (argc == 6)
		philo->nbr_times_eat = ft_atoi(argv[5]);
	else
		philo->nbr_times_eat = 0;
	if (check_atoi_error(philo) == -1)
		return (-1);
	return (0);
}
