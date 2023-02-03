/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:37:55 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/02 20:39:52 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_H
# define MUTEX_H

#include <pthread.h>

typedef struct param_s
{
	pthread_mutex_t	mutex;
}	param;

#endif