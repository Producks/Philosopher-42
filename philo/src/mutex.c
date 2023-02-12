/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 00:32:46 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/12 00:37:05 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include "../include/utils.h"

int	mutex_init_failure(t_params *params, int index)
{
	while (index >= 0)
	{
		pthread_mutex_destroy(&params->fork[index]);
		index--;
	}
	return (print_error("Error: mutex init failed"));
}

int	init_mutex(t_params *params)
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
	if (pthread_mutex_init(&params->dead_check, NULL) != 0)
	{
		pthread_mutex_destroy(&params->write);
		return (mutex_init_failure(params, index - 1));
	}
	return (0);
}

void	free_mutexes(t_params *params)
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
