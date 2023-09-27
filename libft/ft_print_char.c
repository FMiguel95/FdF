/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:56:56 by fernacar          #+#    #+#             */
/*   Updated: 2023/04/26 22:42:21 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(char value, t_flags *flags)
{
	int	total;

	total = 0;
	if (flags->dash)
		total += write(1, &value, 1);
	while (flags->width-- > 1)
		total += write(1, " ", 1);
	if (!flags->dash)
		total += write(1, &value, 1);
	return (total);
}
