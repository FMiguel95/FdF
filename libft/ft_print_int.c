/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:58:45 by fernacar          #+#    #+#             */
/*   Updated: 2023/05/01 19:37:32 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_number_digits(int value)
{
	long	n;
	int		total;

	n = value;
	total = 0;
	if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		total++;
		n /= 10;
	}
	total++;
	return (total);
}

static int	get_extra_precision(int value, t_flags *flags)
{
	int	total;

	total = flags->precision - get_number_digits(value);
	if (value == 0 && flags->precision == 0)
		return (-1);
	if (total < 0)
		return (0);
	return (total);
}

static int	get_number_space(int value, t_flags *flags)
{
	int			total;

	total = get_number_digits(value) + get_extra_precision(value, flags);
	if (value < 0 || flags->plus || flags->space)
		total++;
	return (total);
}

static int	print_digits(int value)
{
	long	n;
	int		total;
	char	c;

	n = value;
	if (n < 0)
		n *= -1;
	if (n >= 10)
		total = print_digits(n / 10);
	else
		total = 0;
	c = '0' + (n % 10);
	write(1, &c, 1);
	total++;
	return (total);
}

int	print_int(int value, t_flags *flags)
{
	int	total;
	int	int_space;

	total = 0;
	int_space = get_number_space(value, flags);
	if (!flags->dash && (!flags->zero || flags->precision >= 0))
		total += print_padding(flags->width - int_space, ' ');
	if (value < 0)
		total += write(1, "-", 1);
	else if (flags->plus && value >= 0)
		total += write(1, "+", 1);
	else if (flags->space)
		total += write(1, " ", 1);
	if (flags->zero && !flags->dash && flags->precision < 0)
		total += print_padding(flags->width - int_space, '0');
	total += print_padding(flags->precision - get_number_digits(value), '0');
	if (!(flags->precision == 0 && value == 0))
		total += print_digits(value);
	if (flags->dash)
		total += print_padding(flags->width - int_space, ' ');
	return (total);
}
