/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:54:45 by fernacar          #+#    #+#             */
/*   Updated: 2023/04/27 19:27:20 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_str_space(const char *value, t_flags *flags)
{
	int	str_space;

	if (value == (char *)0)
	{
		if (flags->precision >= 6 || flags->precision < 0)
			str_space = 6;
		else
			str_space = 0;
	}
	else
		str_space = ft_strlen(value);
	if (flags->precision >= 0 && flags->precision < str_space)
		str_space = flags->precision;
	return (str_space);
}

int	print_str(const char *value, t_flags *flags)
{
	int	total;
	int	str_space;

	total = 0;
	str_space = get_str_space(value, flags);
	if (!flags->dash)
	{
		while (str_space < flags->width--)
			total += write(1, " ", 1);
	}
	if (value == (char *)0 && (flags->precision >= 6
			|| flags->precision < 0))
		total += write(1, "(null)", 6);
	else
		total += write(1, value, str_space);
	if (flags->dash)
		total += print_padding(flags->width - str_space, ' ');
	return (total);
}
