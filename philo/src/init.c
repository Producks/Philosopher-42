/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:43:39 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/12 00:36:41 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <limits.h>
#include "../include/struct.h"
#include "../include/error.h"
#include "../include/utils.h"
#include "../include/mutex.h"

static void init_thread_param_two(t_params *params, int index, int id)
{
	if (id % 2 == 0)
	{
		params->param[index].first_fork = &params->fork[index];
		params->param[index].second_fork = &params->fork[id
			% params->nbr_philosophers];
		params->param[index].even = true;
	}
	else
	{
		params->param[index].second_fork = &params->fork[index];
		params->param[index].first_fork = &params->fork[id
			% params->nbr_philosophers];
		params->param[index].even = false;
	}
	params->param[index].write = &params->write;
	params->param[index].dead_check = &params->dead_check;
	params->param[index].dead = &params->dead;
}

/*screw the norm, making this function look like garbage*/
static void	init_thread_param(t_params *params)
{
	int	index;
	int	philo_id;

	index = 0;
	philo_id = 1;
	while (index < params->nbr_philosophers)
	{
		params->param[index].id = philo_id;
		init_thread_param_two(params, index, philo_id);
		params->param[index].time_last_meal = 0;
		params->param[index].num_times_eaten = 0;
		params->param[index].params = params;
		philo_id++;
		index++;
	}
}

int	init_params(int argc, char **argv, t_params *params)
{
	params->dead = false;
	params->nbr_philosophers = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->nbr_times_eat = ft_atoi(argv[5]);
	else
		params->nbr_times_eat = 0;
	if (init_mutex(params) == -1)
		return (-1);
	init_thread_param(params);
	params->log = 0;
	return (0);
}
