/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 01:23:45 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/13 09:58:58 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include "../include/parsing.h"
#include "../include/semaphore.h"
#include "../include/rules.h"
#include "../include/thread.h"

int	main(int argc, char **argv)
{
	t_hold	temp;

	if (argc < 5 || argc > 6)
		return (1);
	if (check_arguments(argc, argv) == -1)
		return (1);
	init_rules(argc, argv, &temp.rules);
	init_sem(&temp.semaphore, temp.rules.nbr_philosophers);
	init_thread(&temp);
	return (0);
}
