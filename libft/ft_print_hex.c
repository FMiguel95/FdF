/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 01:08:51 by fernacar          #+#    #+#             */
/*   Updated: 2023/04/26 01:22:31 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_number_digits(unsigned int value)
{
	int		total;

	total = 0;
	while (value >= 16)
	{
		total++;
		value /= 16;
	}
	total++;
	return (total);
}

static int	get_extra_precision(unsigned int value, t_flags *flags)
{
	int	total;

	total = flags->precision - get_number_digits(value);
	if (value == 0 && flags->precision == 0)
		return (-1);
	if (total < 0)
		return (0);
	return (total);
}

static int	get_number_space(unsigned int value, t_flags *flags)
{
	int			total;

	total = get_number_digits(value) + get_extra_precision(value, flags);
	if (flags->hash && value != 0)
		total += 2;
	return (total);
}

static int	print_digits(unsigned int value)
{
	int		total;

	if (value >= 16)
		total = print_digits(value / 16);
	else
		total = 0;
	write(1, &"0123456789abcdef"[value % 16], 1);
	total++;
	return (total);
}

int	print_hex(unsigned int value, t_flags *flags)
{
	int	total;
	int	int_space;

	total = 0;
	int_space = get_number_space(value, flags);
	if (!flags->dash && (!flags->zero || flags->precision >= 0))
		total += print_padding(flags->width - int_space, ' ');
	if (flags->hash && value != 0)
		total += write(1, "0x", 2);
	if (flags->zero && !flags->dash && flags->precision < 0)
		total += print_padding(flags->width - int_space, '0');
	total += print_padding(flags->precision - get_number_digits(value), '0');
	if (!(flags->precision == 0 && value == 0))
		total += print_digits(value);
	if (flags->dash)
		total += print_padding(flags->width - int_space, ' ');
	return (total);
}
