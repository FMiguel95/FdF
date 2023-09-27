/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:25:22 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/13 18:05:45 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_strpos(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	free_split(char **split_ptr)
{
	int	i;

	i = 0;
	while (split_ptr[i])
	{
		free(split_ptr[i]);
		i++;
	}
	free(split_ptr);
}

int	list_length(char **list)
{
	int	count;

	count = 0;
	while (*list)
	{
		count++;
		list++;
	}
	return (count);
}

int	points_in_line(char	*line)
{
	int		total;
	char	**line_split;

	line_split = ft_split(line, ' ');
	free(line);
	total = list_length(line_split);
	free_split(line_split);
	return (total);
}
