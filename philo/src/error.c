/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:08:54 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/25 00:40:52 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include "arguments.h"
#include "mutex.h"
#include "utils.h"
#include "error.h"

/*Ran out of space because of the norminette, garbage 5 functions per file*/
int	pfail(pthread_t *threads, pthread_mutex_t *dead_lock,
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

int	print_argc_error(void)
{
	print_error("Error: Wrong number of arguments");
	printf("First argument: Number of philosophers\n");
	printf("Second argument: Time before death\n");
	printf("Third argument: Time to eat\n");
	printf("Fourth argument: Time to sleep\n");
	printf("Fifth argument: Number of time to eat(optional)\n");
	return (ARGC_ERROR);
}