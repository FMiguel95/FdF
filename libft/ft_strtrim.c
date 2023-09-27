/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:43:07 by fernacar          #+#    #+#             */
/*   Updated: 2023/04/17 19:43:28 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_start_index(char const *s1, char const *set)
{
	int		i;

	i = 0;
	while (s1[i])
	{
		if (!ft_strrchr(set, s1[i]))
			return (i);
		i++;
	}
	return (-1);
}

static int	get_end_index(char const *s1, char const *set)
{
	int		i;

	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		if (!ft_strrchr(set, s1[i]))
			return (i);
		i--;
	}
	return (-1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		start_index;
	int		end_index;

	start_index = get_start_index(s1, set);
	end_index = get_end_index(s1, set);
	if (start_index < 0 || end_index < 0)
	{
		result = malloc(sizeof(char));
		if (!result)
			return (NULL);
		result[0] = '\0';
	}
	else
	{
		result = malloc(sizeof(char) * (end_index - start_index + 2));
		if (!result)
			return (NULL);
		ft_strlcpy(result, s1 + start_index, end_index - start_index + 2);
	}
	return (result);
}
