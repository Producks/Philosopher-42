/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:13:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/25 02:33:21 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ACTION_H
# define PHILO_ACTION_H

# include "arguments.h"
# include "philo.h"

void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_think(t_philo *philo);
void	print_philo_state(t_philo *philo, int flag);
void	philo_wait_till_death(t_philo *philo);
void	custom_sleep(int duration);

#endif