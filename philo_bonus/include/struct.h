/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:50:05 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/13 09:57:15 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "semaphore.h"
# include "rules.h"

typedef struct s_hold
{
	t_rules	rules;
	t_sema	semaphore;
}	t_hold;

#endif