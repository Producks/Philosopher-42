/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:09:16 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/04 04:07:09 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "struct.h"

# define SUCCESS  0
# define ARGC_ERROR 1
# define ARGV_ERROR 2

void	print_error(const char *str);
int		check_atoi_error(t_philo *philo);

#endif