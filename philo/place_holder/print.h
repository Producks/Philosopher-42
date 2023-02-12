/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 10:28:07 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/11 13:44:43 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

#include "struct.h"

void	print_fork(t_philo *philo, unsigned long int time, int id);
void	print_eat(t_philo *philo, unsigned long int time, int id);
void	print_sleep(t_philo *philo, unsigned long int time, int id);
void	print_think(t_philo *philo, unsigned long int time, int id);

#endif