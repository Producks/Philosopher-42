/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 01:23:45 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/12 18:14:36 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/semaphore.h"

int	main(int argc, char **argv)
{
	// if (argc < 5 || argc > 6)
	// 	return (1);
	// if (check_arguments(argc, argv) == -1)
	// 	return (1);
	sem_test();
	return (0);
}
