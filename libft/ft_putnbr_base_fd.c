/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:02:41 by fernacar          #+#    #+#             */
/*   Updated: 2023/04/20 20:33:56 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_fd(int n, const char *base, int fd)
{
	long	number;

	number = n;
	if (number < 0)
	{
		write(fd, "-", 1);
		number *= -1;
	}
	if (number >= (long)ft_strlen(base))
		ft_putnbr_base_fd(number / ft_strlen(base), base, fd);
	write(fd, &base[number % ft_strlen(base)], 1);
}
