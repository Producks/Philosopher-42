/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:09:16 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/15 21:18:24 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "struct.h"

# define SUCCESS  0
# define ARGC_ERROR 1
# define ARGV_ERROR 2
# define ENOMEM 12

int	create_failure(pthread_t *threads, pthread_mutex_t *dead_lock,
		bool *dead_check, int index);

#endif
