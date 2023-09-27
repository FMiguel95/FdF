/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 01:23:57 by fernacar          #+#    #+#             */
/*   Updated: 2023/08/31 23:13:21 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static unsigned int	read_color_code(char *str)
{
	char	*base;

	base = "0123456789";
	if (ft_strncmp(str, "0x", 2) == 0)
	{
		base = "0123456789abcdef";
		str += 2;
	}
	return (ft_atoi_base(str, base));
}

static unsigned int	get_color(char *str)
{
	unsigned int	color;

	color = 0x00FFFFFF;
	if (ft_strpos(str, ',') >= 0)
	{
		str += ft_strpos(str, ',') + 1;
		color = read_color_code(str);
	}
	return (color);
}

static int	get_map_sizes(char *fdf_path, t_int2 *map_size, int is_valid)
{
	int		fd;
	char	*line;

	fd = open(fdf_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		exit(0);
	}
	line = get_next_line(fd);
	if (!line)
		return (0);
	map_size->x = points_in_line(line);
	map_size->y = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (points_in_line(line) != map_size->x)
			is_valid = 0;
		(map_size->y)++;
	}
	close(fd);
	return (is_valid);
}

static void	assign_points(char *f_path, t_float3 *pts3d, int *clrs, int m_len)
{
	int		fd;
	char	*line;
	char	**line_split;
	int		x;
	int		y;

	fd = open(f_path, O_RDONLY);
	y = -1;
	while (++y || !y)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line_split = ft_split(line, ' ');
		x = -1;
		while (++x < m_len)
		{
			*pts3d++ = (t_float3){x, y, ft_atoi(line_split[x])};
			*clrs++ = get_color(line_split[x]);
		}
		free_split(line_split);
		free(line);
	}
	pts3d->x = INT_MIN;
	close(fd);
}

void	parse_map(char *fdf_path, t_fdf *fdf)
{
	t_int2	map_size;

	if (!get_map_sizes(fdf_path, &map_size, 1))
	{
		ft_printf("Error: Invalid map\n");
		exit(0);
	}
	fdf->points3d = malloc(sizeof(t_float3) * (map_size.x * map_size.y + 1));
	fdf->original_colors = malloc(sizeof(int) * (map_size.x * map_size.y + 1));
	fdf->height_colors = malloc(sizeof(int) * (map_size.x * map_size.y + 1));
	assign_points(fdf_path, fdf->points3d, fdf->original_colors, map_size.x);
	fdf->map_size = map_size;
}
