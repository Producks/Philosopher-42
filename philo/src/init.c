/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:21:08 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/15 21:16:44 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include "../include/utils.h"

int	init_arguments(int argc, char **argv, t_arguments *arguments)
{
	arguments->nbr_philosophers = ft_atoi(argv[1]);
	arguments->sim_params.time_to_die = ft_atoi(argv[2]);
	arguments->sim_params.time_to_eat = ft_atoi(argv[3]);
	arguments->sim_params.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arguments->sim_params.nbr_times_eat = ft_atoi(argv[5]);
	else
		arguments->sim_params.nbr_times_eat = 0;
	return (0);
}
