/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:43:39 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/10 19:03:54 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <limits.h>
#include "../include/struct.h"
#include "../include/error.h"

static int	ft_atoi(const char *str)
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

/*screw the norm, making this function look like garbage*/
static void	init_thread_param(t_params *params)
{
	int	index;

	index = 0;
	while (index < params->nbr_philosophers)
	{
		params->param[index].id = (index + 1);
		if ((index + 1) % 2 == 0)
		{
			params->param[index].first_fork = &params->fork[index];
			params->param[index].second_fork = &params->fork[(index + 1)
				% params->nbr_philosophers];
			params->param[index].even = true;
		}
		else
		{
			params->param[index].second_fork = &params->fork[index];
			params->param[index].first_fork = &params->fork[(index + 1)
				% params->nbr_philosophers];
			params->param[index].even = false;
		}
		params->param[index].time_last_meal = 0;
		params->param[index].num_times_eaten = 0;
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
			return (mutex_init_failure(params, (index - 1)));
		index++;
	}
	if (pthread_mutex_init(&params->write, NULL) != 0)
		return (mutex_init_failure(params, index - 1));
	// if (pthread_mutex_init(&params->dead_check, NULL) != 0);
	// {
	// 	pthread_mutex_destroy(&params->write);
	// 	return (mutex_init_failure(params, index - 1));
	// }
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
	init_thread_param(params);
	params->log = 0;
	return (0);
}
