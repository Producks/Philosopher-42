/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:09:16 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/12 00:26:35 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "struct.h"

# define SUCCESS  0
# define ARGC_ERROR 1
# define ARGV_ERROR 2
# define ENOMEM 12

int	mutex_init_failure(t_params *params, int index);
int	create_failure(t_params *params, int index, pthread_t threads[200]);

#endif
