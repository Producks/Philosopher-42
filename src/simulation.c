/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:37:27 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/06 22:24:17 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include "../include/struct.h"
#include "../include/utils.h"

void *test(void *ptr)
{
    t_philo *philo;
    
    philo = (t_philo *)ptr;
    philo->time_last_meal = time_stamp();
    print_philo_state(philo, 0, "");
    print_philo_state(philo, 1, "");
    // print_philo_state(philo, 0, "has taken a fork 🍴\n");
    // print_philo_state(philo, 0, "is eating 🍝\n");
    return (NULL);
}

int simulation(t_params *params)
{
    int         index;
    pthread_t   threads[params->nbr_philosophers];

    index = 0;
    params->start_simul = time_stamp();
    while (index < params->nbr_philosophers)
    {
        pthread_create(&threads[index], NULL, test, &params->param[index]);
        index++;
    }
    index = 0;
    while (index < params->nbr_philosophers)
        pthread_join(threads[index++], NULL);
    return (0);
}