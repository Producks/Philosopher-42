/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:07:17 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/18 02:47:00 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEMAPHORE_H
# define SEMAPHORE_H

# include <semaphore.h>

typedef struct s_sema
{
	sem_t	*write;
	sem_t	*dead_check;
	sem_t	*forks;
	sem_t	*availability;
	sem_t	*launch;
}	t_sema;

int		init_sem(t_sema	*semaphore, int nbr_of_philo);
void	destroy_sem(t_sema *semaphore);

#endif