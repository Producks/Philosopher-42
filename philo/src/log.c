/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:07 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/17 12:47:00 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "arguments.h"
#include "log.h"

int	generate_log(bool dead_philo, unsigned int start_simul,
	t_arguments arguments)
{
	printf(MAG "Simulation log\n");
	printf(YEL "Configuration:\n");
	printf("Number of philosophers:%d\n", arguments.nbr_philosophers);
	printf("Time before death:%d\n", arguments.sim_params.time_to_die);
	printf("Time to eat:%d\n", arguments.sim_params.time_to_eat);
	printf("Time to sleep:%d\n", arguments.sim_params.time_to_sleep);
	if (dead_philo == true)
		printf(RED "☠️ One of the philo died☠️\n");
	else
		printf(GRN "🥳 Simulation was a success!🎉\n");
	return (0);
}