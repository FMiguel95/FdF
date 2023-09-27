/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:00:01 by fernacar          #+#    #+#             */
/*   Updated: 2023/05/16 20:36:27 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_first_flags(const char *format, t_flags *flags)
{
	int	i;

	i = 1;
	while (format[i] == '+' || format[i] == '-' || format[i] == ' ' \
		|| format[i] == '0' || format[i] == '#')
	{
		if (format[i] == '+')
			flags->plus = 1;
		else if (format[i] == '-')
			flags->dash = 1;
		else if (format[i] == ' ')
			flags->space = 1;
		else if (format[i] == '0')
			flags->zero = 1;
		else if (format[i] == '#')
			flags->hash = 1;
		i++;
	}
	return (i);
}

int	print_padding(int n, char c)
{
	int	i;

	i = -1;
	while (++i < n)
		write(1, &c, 1);
	return (i);
}
