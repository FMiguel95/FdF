/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 22:48:39 by fernacar          #+#    #+#             */
/*   Updated: 2023/05/16 20:40:19 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags	*initialize_flags(t_flags *flags)
{
	flags->width = -1;
	flags->precision = -1;
	flags->zero = 0;
	flags->point = 0;
	flags->dash = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->hash = 0;
	return (flags);
}

int	print_argument(char specifier, va_list args, t_flags *flags)
{
	int	total_printed;

	if (specifier == 'c')
		total_printed = print_char(va_arg(args, int), flags);
	else if (specifier == 's')
		total_printed = print_str(va_arg(args, const char *), flags);
	else if (specifier == 'p')
		total_printed = print_ptr(va_arg(args, unsigned long), flags);
	else if (specifier == 'd')
		total_printed = print_int(va_arg(args, int), flags);
	else if (specifier == 'i')
		total_printed = print_int(va_arg(args, int), flags);
	else if (specifier == 'u')
		total_printed = print_uint(va_arg(args, unsigned int), flags);
	else if (specifier == 'x')
		total_printed = print_hex(va_arg(args, unsigned int), flags);
	else if (specifier == 'X')
		total_printed = print_hex_up(va_arg(args, unsigned int), flags);
	else
		total_printed = write(1, "%%", 1);
	return (total_printed);
}

static int	parse_flags_digits(const char *format, va_list args, int *i)
{
	int	value;

	if (format[*i] == '*')
	{
		value = va_arg(args, int);
		*i += 1;
	}
	else
	{
		value = ft_atoi(&format[*i]);
		while (ft_isdigit(format[*i]))
			*i += 1;
	}
	return (value);
}

int	parse_flags(const char *format, va_list args, t_flags *flags)
{
	int	i;

	i = parse_first_flags(format, flags);
	if (ft_isdigit(format[i]) || format[i] == '*')
		flags->width = parse_flags_digits(format, args, &i);
	if (format[i] == '.')
	{
		i++;
		flags->precision = parse_flags_digits(format, args, &i);
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int		print_size;
	va_list	args;
	t_flags	to_print;
	int		i;

	print_size = 0;
	va_start(args, format);
	i = 0;
	while (format[i])
	{
		if (format[i] != '%')
		{
			print_size += write(1, &format[i], 1);
			i++;
		}
		else
		{
			initialize_flags(&to_print);
			i += parse_flags(&format[i], args, &to_print);
			print_size += print_argument(format[i], args, &to_print);
			i++;
		}
	}
	va_end(args);
	return (print_size);
}
