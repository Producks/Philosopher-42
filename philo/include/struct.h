/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:20:06 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/16 23:26:07 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>
# include <stdbool.h>

# define RED   "\x1B[31m"

typedef struct s_sim_params
{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_times_eat;
}	t_sim_params;

typedef struct s_arguments
{
	int					nbr_philosophers;
	t_sim_params		sim_params;
}	t_arguments;

#endif