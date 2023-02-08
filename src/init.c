/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:43:39 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/07 22:13:43 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/struct.h"
#include "../include/utils.h"
#include "../include/error.h"
#include "../include/init.h"

static int	init_thread_param(t_params *params)
{
	int	index;
	int	philo_id;

	index = 0;
	philo_id = 1;
	while (index < params->nbr_philosophers)
	{
		params->param[index].id = philo_id;
		params->param[index].time_last_meal = 0;
		params->param[index].num_times_eaten = 0;
		params->param[index].left_fork = &params->fork[index];
		params->param[index].right_fork = &params->fork[(index + 1)
			% params->nbr_philosophers];
		params->param[index].params = params;
		index++;
		philo_id++;
	}
	return (0);
}

//Fix here later;
static int	init_mutex(t_params *params)
{
	int	index;

	index = 0;
	while (index < params->nbr_philosophers)
	{
		if (pthread_mutex_init(&params->fork[index], NULL) != 0)
			return (-1);
		index++;
	}
	pthread_mutex_init(&params->write, NULL);
	return (0);
}

static int	check_args(int argc, char **argv)
{
	int	index;

	index = 1;
	while (index != argc)
	{
		if (parsing_argv_error(argv[index]) == -1)
			return (-1);
		index++;
	}
	return (0);
}

int	init_params(int argc, char **argv, t_params *params)
{
	if (check_args(argc, argv) == -1)
		return (-1);
	params->dead = false;
	params->nbr_philosophers = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->nbr_times_eat = ft_atoi(argv[5]);
	else
		params->nbr_times_eat = 0;
	if (check_atoi_error(params) == -1)
		return (-1);
	if (init_mutex(params) == -1)
		return (-1);
	if (init_thread_param(params) == -1)
		return (-1);
	return (0);
}
