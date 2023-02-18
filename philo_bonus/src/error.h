/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:09:16 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/18 04:49:31 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>
# include "semaphore.h"

# define SUCCESS  0
# define ARGC_ERROR 1
# define ARGV_ERROR 2
# define ENOMEM 12

int	pfail(pthread_t *threads, t_sema *dead_lock,
		bool *dead_check, int index);

#endif
