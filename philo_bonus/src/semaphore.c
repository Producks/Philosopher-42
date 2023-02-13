/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:07:16 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/12 18:17:48 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stdio.h>
#include "../include/semaphore.h"

void	sem_test(void)
{
	t_sema	semaphore;

	sem_init(&semaphore.write, 0, 1);
	sem_post(&semaphore.write);
	sem_wait(&semaphore.write);
	printf("test\n");
	sem_wait(&semaphore.write);
	printf("test\n");
	sem_wait(&semaphore.write);
	sem_close(&semaphore.write);
	return ;
}