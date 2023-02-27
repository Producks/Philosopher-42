/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:35:29 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/27 01:18:26 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "utils.h"

/*CHECK LATER IF IT'S BETTER*/
void	custom_sleep(int duration)
{
	long	start_time;

	start_time = time_stamp();
	while ((time_stamp() - start_time) * 1000 < duration)
	{
		usleep(1000);
	}
}

/*Function to get the time, has a static struct which
will be our start simulation time the first time we call it*/
unsigned int	time_stamp(void)
{
	static struct timeval	start_simul = {0, 0};
	struct timeval			ms;

	if (start_simul.tv_sec == 0)
		gettimeofday(&start_simul, 0);
	gettimeofday(&ms, 0);
	return ((ms.tv_sec - start_simul.tv_sec) * 1000
		+ (ms.tv_usec - start_simul.tv_usec) / 1000);
}

/*Your typical atoi function*/
int	ft_atoi(const char *str)
{
	long	result;

	result = 0;
	if (*str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		result = result * 10 + (*str - 48);
		if (result > INT_MAX)
			return (-1);
		str++;
	}
	return ((int)result);
}

/*Print the string we sent it to the stderr*/
int	print_error(const char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		write(2, &str[index], 1);
		index++;
	}
	write(2, "\n", 1);
	return (-1);
}

/*Generate a small log after the simulation has ended*/
int	generate_log(bool dead_philo, unsigned int start_simul,
	t_arguments arguments)
{
	printf(
		MAG "Simulation log\n"
		YEL "Configuration:\n"
		"Number of philosophers:%d\n", arguments.nbr_philosophers);
	printf("Time before death:%d\n", arguments.sim_params.time_to_die);
	printf("Time to eat:%d\n", arguments.sim_params.time_to_eat);
	printf("Time to sleep:%d\n", arguments.sim_params.time_to_sleep);
	printf("Number of times to eat:%d\n", arguments.sim_params.nbr_times_eat);
	if (dead_philo == true)
		printf(RED "☠️ One of the philo died☠️\n");
	else
		printf(GRN "🥳 Simulation was a success!🎉\n");
	return (0);
}
