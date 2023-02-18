/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 23:19:30 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/17 00:46:33 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENTS_H
# define ARGUMENTS_H

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

int	check_arguments(int argc, char **argv);
int	init_arguments(int argc, char **argv, t_arguments *arguments);

#endif