/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:18:23 by fernacar          #+#    #+#             */
/*   Updated: 2023/04/15 18:59:44 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_number_length(long n)
{
	int	total;

	if (n < 0)
	{
		total = 1;
		n *= -1;
	}
	else
		total = 0;
	while (n >= 10)
	{
		total++;
		n /= 10;
	}
	total++;
	return (total);
}

static void	put_digits(char *s, long number, int index)
{
	if (number >= 10)
		put_digits(s, number / 10, index - 1);
	s[index] = '0' + number % 10;
}

char	*ft_itoa(int n)
{
	char	*result;
	long	number;
	int		number_length;

	number_length = get_number_length(n);
	result = malloc(sizeof(char) * (number_length + 1));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		number = (long)n * -1;
		result[0] = '-';
	}
	else
		number = n;
	put_digits(result, number, number_length - 1);
	result[number_length] = '\0';
	return (result);
}
/*
int main(){
	printf("%s\n", ft_itoa(-2147483648));
}*/