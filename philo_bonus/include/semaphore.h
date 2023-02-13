/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:07:17 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/12 18:15:26 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEMAPHORE_H
# define SEMAPHORE_H

# include <semaphore.h>

typedef struct s_sema
{
	sem_t	write;
	sem_t	dead_check;
	sem_t	forks[200];
}	t_sema;

void	sem_test(void);

#endif