/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 23:07:05 by fernacar          #+#    #+#             */
/*   Updated: 2023/04/16 20:37:34 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	length_dst;
	size_t	length_src;
	size_t	i;
	size_t	j;

	length_dst = ft_strlen(dst);
	length_src = ft_strlen(src);
	if (length_dst < size - 1 && size > 0)
	{
		i = 0;
		j = length_dst;
		while (src[i] && i < size - length_dst - 1)
		{
			dst[j] = src[i];
			j++;
			i++;
		}
		dst[j] = '\0';
	}
	if (length_dst > size)
		length_dst = size;
	return (length_dst + length_src);
}
