/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unstuck.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 04:45:39 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/27 04:31:10 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>

void	init_meal_sema_message(int index, char *str, char *message)
{
	int		i;
	int		divider;

	i = 0;
	while (*message)
	{
		str[i] = *message;
		message++;
		i++;
	}
	i = 0;
	divider = 100;
	str[5] = (index / divider) + 48;
	index %= divider;
	divider = 10;
	str[6] = (index / divider) + 48;
	index %= divider;
	divider = 1;
	str[7] = (index / divider) + 48;
	index %= divider;
	str[8] = '\0';
}

/*Only use if someone kill the program while running during the correction,
should clear up the names so the program can run again. This is only use
if it's necessary*/
int	main(void)
{
	int		index;
	char	message[8];

	index = 0;
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/launch");
	sem_unlink("/availability");
	sem_unlink("/dead_check");
	while (index < 200)
	{
		init_meal_sema_message(index, message, "/meal");
		index++;
	}
	return (0);
}
