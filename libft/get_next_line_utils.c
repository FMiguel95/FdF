/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 22:59:22 by fernacar          #+#    #+#             */
/*   Updated: 2023/05/18 22:53:08 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s != NULL && (s[i] || c == '\0'))
	{
		if (s[i] == c)
			return (&(s[i]));
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		s1_length;
	int		s2_length;
	size_t	i;
	size_t	j;

	s1_length = 0;
	if (s1 != NULL)
		s1_length = ft_strlen(s1);
	s2_length = 0;
	if (s2 != NULL)
		s2_length = ft_strlen(s2);
	result = ft_calloc(s1_length + s2_length + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while ((++i || !i) && (s1 != NULL && s1[i]))
		result[i] = s1[i];
	j = -1;
	while ((++j || !j) && (s2 != NULL && s2[j]))
		result[i + j] = s2[j];
	return (result);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*result;
	int		i;

	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	if (ft_strlen(s) < start)
		len = 0;
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	return (result);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	while (nmemb--)
		ptr[nmemb] = 0;
	return (ptr);
}
