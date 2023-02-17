/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:08:54 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/17 04:33:00 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include "arguments.h"
#include "mutex.h"
#include "utils.h"

int	create_failure(pthread_t *threads, pthread_mutex_t *dead_lock,
	bool *dead_check, int index)
{
	pthread_mutex_lock(dead_lock);
	*dead_check = true;
	pthread_mutex_unlock(dead_lock);
	while (index > 0)
	{
		pthread_join(threads[index], NULL);
		index--;
	}
	return (print_error("Error: pthread create failure"));
}
