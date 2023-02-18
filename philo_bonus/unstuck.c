/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unstuck.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 04:45:39 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/18 04:47:29 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>

/*Only use if someone kill the program while running during the correction,
should clear up the names so the program can run again. This is only use
if it's necessary*/
int	main(void)
{
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/launch");
	sem_unlink("/availability");
	sem_unlink("/dead_check");
	return (0);
}
