/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:05:21 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/13 01:17:33 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rules.h"
#include "../include/utils.h"

void	init_rules(int argc, char **argv, t_rules *rules)
{
	rules->nbr_philosophers = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		rules->nbr_times_eat = 0;
	else
		rules->nbr_times_eat = ft_atoi(argv[5]);
}