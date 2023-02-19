/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:08:54 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/18 18:02:35 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include "arguments.h"
#include "utils.h"
#include "semaphore.h"

/*Ran out of space because of the norminette, garbage 5 functions per file*/
int	pfail(pthread_t *threads, sem_t *dead_lock,
	bool *dead_check, int index)
{
	sem_wait(dead_lock);
	*dead_check = true;
	sem_post(dead_lock);
	while (index > 0)
	{
		pthread_join(threads[index], NULL);
		index--;
	}
	return (print_error("Error: pthread create failure"));
}
