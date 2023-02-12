/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:08:54 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/12 00:33:21 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "../include/struct.h"
#include "../include/utils.h"

int	create_failure(t_params *params, int index, pthread_t threads[200])
{
	params->dead = true;
	while (index > 0)
	{
		pthread_join(threads[index], NULL);
		index--;
	}
	return (print_error("Error: pthread create failure"));
}
