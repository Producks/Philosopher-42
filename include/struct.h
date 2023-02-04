/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:20:06 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/04 04:05:42 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_philo
{
	int	nbr_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_times_eat;
}	t_philo;

#endif