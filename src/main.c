/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:01:24 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/10 23:15:05 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/struct.h"
#include "../include/init.h"
#include "../include/error.h"
#include "../include/simulation.h"
#include "../include/utils.h"

static void	generate_log(t_params params)
{
	printf(WHT "Simulation log\n");
	printf(MAG "Number of philosophers:%d\n", params.nbr_philosophers);
	printf("Time before death setting:%d\n", params.time_to_die);
	printf("Time to eat setting:%d\n", params.time_to_eat);
	printf("Time to sleep setting:%d\n", params.time_to_sleep);
	printf("Number of time they need to eat:%d\n", params.nbr_times_eat);
	if (params.dead == true)
	{
		printf(RED "Philo who died:%d\n", params.param[params.log].id);
		printf("Number of time eaten:%d\n",
			params.param[params.log].num_times_eaten);
		printf("Time of death:%ld\n", params.param[params.log].time_of_death);
		printf(WHT);
	}
	else
		printf(GRN "Simulation was a success!\n" WHT);
}

static void	free_mutexes(t_params *params)
{
	int	index;

	index = 0;
	while (index < params->nbr_philosophers)
	{
		pthread_mutex_destroy(&params->fork[index]);
		index++;
	}
	pthread_mutex_destroy(&params->write);
	pthread_mutex_destroy(&params->dead_check);
}

int	main(int argc, char **argv)
{
	t_params	params;

	if (argc < 5 || argc > 6)
		return (ARGC_ERROR);
	if (init_params(argc, argv, &params) == -1)
		return (ARGV_ERROR);
	if (start_simulation(&params) == -1)
		return (ENOMEM);
	generate_log(params);
	free_mutexes(&params);
	return (SUCCESS);
}
