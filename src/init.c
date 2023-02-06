/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:43:39 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/05 23:13:47 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
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
		params->param[index].time = 0;
		params->param[index].left_fork = &params->fork[index];
		params->param[index].right_fork = &params->fork[(index + 1)
			% params->nbr_philosophers];
		printf("Philo %d left 🍴:%d\n", index, index);
		printf("Philo %d right 🍴:%d\n", index, (index + 1)
			% params->nbr_philosophers);
		params->param[index].params = params;
		index++;
	}
}

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
}

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

int	init_params(int argc, char **argv, t_params *params)
{
	if (check_args(argc, argv) == -1)
		return (-1);
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
