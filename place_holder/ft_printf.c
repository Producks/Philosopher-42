/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:27:54 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/10 23:47:36 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

static void	ft_write(unsigned long int nb)
{
	write(1, &nb, 1);
}

static void ft_write_two(unsigned int nb)
{
	write(1, &nb, 1);
}

static void	ft_write_ld(unsigned long int nb)
{
	if (nb > 9)
		ft_write_ld(nb / 10);
	ft_write(nb % 10 + 48);
}

static void	ft_write_nbr(unsigned int nb)
{
	if (nb > 9)
		ft_write_nbr(nb / 10);
	ft_write_two(nb % 10 + 48);
}

static void	ft_check_type(va_list args, const char type)
{
	if (type == 'l')
		ft_write_ld(va_arg(args, unsigned long int));
	if (type == 'd')
		ft_write_nbr(va_arg(args, unsigned int));
}

void	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;

	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
			ft_check_type(args, str[++i]);
		else
			ft_write(str[i]);
		i++;
	}
	va_end(args);
}
