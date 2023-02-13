/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 01:41:58 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/12 12:41:29 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

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
