/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 01:20:21 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/27 01:20:42 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRIM_REAPER_H
# define GRIM_REAPER_H

void	grim_reaper(t_philo *philo, t_mutex *mutex,
	unsigned int *start_simul, t_arguments *arguments);

#endif