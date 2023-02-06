/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:01:24 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/05 23:13:06 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "../include/struct.h"
#include "../include/init.h"
#include "../include/error.h"

int	main(int argc, char **argv)
{
	t_params	params;

	if (argc < 5 || argc > 6)
		return (ARGC_ERROR);
	if (init_params(argc, argv, &params) == -1)
		return (ARGV_ERROR);
	return (0);
}
