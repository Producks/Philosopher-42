/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 23:20:18 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/17 04:17:46 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"
#include "utils.h"

/*Check if the arguments are digits only and positive*/
static int	parsing_argv_error(const char *str)
{
	int	index;

	index = 0;
	if (!str[index])
		return (print_error("Error: argument is empty"));
	if (str[index] == '-')
		return (print_error("Error: integer is negative"));
	if (str[index] == '+' && str[index + 1] != '\0')
		index++;
	while (str[index])
	{
		if (str[index] < 48 || str[index] > 57)
			return (print_error("Error: argument is not a nbr"));
		index++;
	}
	return (0);
}

/*Check if the values passed in arguments exceed a certain amount
	or are negative*/
static int	parsing_value(int value, int index)
{
	if (index == 1)
	{
		if (value < 1 || 200 < value)
			return (print_error("Error: nbr of philo is under 1 or over 200"));
		return (0);
	}
	else
	{
		if (value < 0)
			return (print_error("Error: argument over MAX_INT"));
		return (0);
	}
}

/*Function that check if the arguments passed are valid for the project.
Will return -1 with an print in the stder explaing what was the error*/
int	check_arguments(int argc, char **argv)
{
	int	index;

	index = 1;
	while (index != argc)
	{
		if (parsing_argv_error(argv[index]) == -1)
			return (-1);
		if (parsing_value(ft_atoi(argv[index]), index) == -1)
			return (-1);
		index++;
	}
	return (0);
}

/*Initialize t_arguments struct with the arguments the user has given us*/
int	init_arguments(int argc, char **argv, t_arguments *arguments)
{
	arguments->nbr_philosophers = ft_atoi(argv[1]);
	arguments->sim_params.time_to_die = ft_atoi(argv[2]);
	arguments->sim_params.time_to_eat = ft_atoi(argv[3]);
	arguments->sim_params.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arguments->sim_params.nbr_times_eat = ft_atoi(argv[5]);
	else
		arguments->sim_params.nbr_times_eat = 0;
	return (0);
}
