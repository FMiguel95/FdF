/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:29:33 by fernacar          #+#    #+#             */
/*   Updated: 2023/06/21 19:24:06 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_base(char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(const char *nptr, const char *base)
{
	unsigned int	value;
	int				base_len;

	base_len = ft_strlen(base);
	value = 0;
	while (is_in_base(ft_tolower(*nptr), base) != -1)
	{
		value = value * base_len + is_in_base(ft_tolower(*nptr), base);
		nptr++;
	}
	return ((int)value);
}
