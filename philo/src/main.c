/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:01:24 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/25 00:41:23 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"
#include "error.h"
#include "simulation.h"

int	main(int argc, char **argv)
{
	t_arguments	arguments;

	if (argc < 5 || argc > 6)
		return (print_argc_error());
	if (check_arguments(argc, argv) == -1)
		return (ARGV_ERROR);
	if (init_arguments(argc, argv, &arguments) == -1)
		return (ARGV_ERROR);
	if (start_simulation(&arguments, -1) == -1)
		return (ENOMEM);
	return (SUCCESS);
}
