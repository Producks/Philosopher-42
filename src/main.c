/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:01:24 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/02 20:43:48 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <curses.h>
#include "../include/mutex.h"

#define ARGC_ERROR 5

pthread_mutex_t mutex;


void    *die(void *elements)
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 10; i++)
        printf("Dead:%d\n", i);
    pthread_mutex_unlock(&mutex);
    return (NULL);
}

int main(int argc, char **argv)
{
    pthread_t       thread[2];
    param           pthread_param;
    // if (argc != 6)
    //     return (ARGC_ERROR);
    pthread_mutex_init(&pthread_param.mutex, NULL);
    pthread_create(&thread[0], NULL, die, (void *)&pthread_param.mutex);
    pthread_create(&thread[1], NULL, die, (void *)&pthread_param.mutex);
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    pthread_mutex_destroy(&pthread_param.mutex);
    printf("Done!");
    return (0);
}