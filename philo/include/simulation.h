/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:36:01 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/15 21:04:32 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "struct.h"
# include "philo.h"

bool	check_death(t_philo *philo);
int		start_simulation(t_arguments *arguments, int index);
void	die(t_philo *philo);

#endif