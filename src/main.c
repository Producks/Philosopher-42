/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:01:24 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/06 10:19:52 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include "../include/init.h"
#include "../include/error.h"
#include "../include/simulation.h"

int	main(int argc, char **argv)
{
	t_params	params;

	// if (argc < 5 || argc > 6)
	// 	return (ARGC_ERROR);
	if (init_params(argc, argv, &params) == -1)
		return (ARGV_ERROR);
	if (simulation(&params) == -1)
		return (-1);
	return (SUCCESS);
}
