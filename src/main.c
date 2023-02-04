/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:01:24 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/04 04:01:46 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "../include/struct.h"
#include "../include/init.h"
#include "../include/error.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 && argc > 6)
		return (ARGC_ERROR);
	if (init_params(argc, argv, &philo) == -1)
		return (ARGV_ERROR);
	return (0);
}
