/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:05:23 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/13 01:15:04 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RULES_H
# define RULES_H

typedef struct s_rules
{
	int					nbr_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_times_eat;
}	t_rules;

void	init_rules(int argc, char **argv, t_rules *rules);

#endif