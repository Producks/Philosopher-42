/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:35:29 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/04 04:04:05 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include "../include/error.h"

int	parsing_argv_error(const char *str)
{
	int	index;

	index = 0;
	if (!str[index])
	{
		print_error("Error: argument is empty");
		return (false);
	}
	if (str[index] == '-')
	{
		print_error("Error: integer is negative");
		return (false);
	}
	if (str[index] == '+')
		index++;
	while (str[index])
	{
		if (str[index] < 48 || str[index] > 57)
		{
			print_error("Error: argument is not digit");
			return (false);
		}
		index++;
	}
	return (true);
}

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
