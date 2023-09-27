/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 23:27:33 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/13 19:51:22 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	put_instructions(t_fdf fdf)
{
	int	text_color;

	text_color = 0x0000FF00;
	mlx_string_put(fdf.mlx, fdf.win, 1, 10, text_color,
		"left click: rotation");
	mlx_string_put(fdf.mlx, fdf.win, 1, 20, text_color,
		"middle click: translation");
	mlx_string_put(fdf.mlx, fdf.win, 1, 30, text_color,
		"mouse wheel: zoom");
	mlx_string_put(fdf.mlx, fdf.win, 1, 40, text_color,
		"C: alternate color scheme");
	mlx_string_put(fdf.mlx, fdf.win, 1, 50, text_color,
		"P: change projection");
	mlx_string_put(fdf.mlx, fdf.win, 1, 60, text_color,
		"Esc: exit");
}

static void	draw_map(t_fdf *fdf, t_int2 *pts, t_image_data *img_data)
{
	t_line	line;
	int		i;

	i = 0;
	while (pts[i].x != INT_MIN)
	{
		if (i % fdf->map_size.x != fdf->map_size.x - 1)
		{
			line.p0 = (t_int2){pts[i].x, pts[i].y};
			line.p1 = (t_int2){pts[i + 1].x, pts[i + 1].y};
			draw_line(img_data, line, fdf->colors[i], fdf->colors[i + 1]);
		}
		if (i + fdf->map_size.x < fdf->map_size.x * fdf->map_size.y)
		{
			line.p0 = (t_int2){pts[i].x, pts[i].y};
			line.p1 = (t_int2){pts[i + fdf->map_size.x].x,
				pts[i + fdf->map_size.x].y};
			draw_line(img_data, line, fdf->colors[i],
				fdf->colors[i + fdf->map_size.x]);
		}
		i++;
	}
}

static void	isometric_projection(t_fdf fdf, t_int2 *points_to_draw)
{
	while (fdf.points3d->x != INT_MIN)
	{
		points_to_draw->x = fdf.points3d->x
			* fdf.camera.zoom + fdf.camera.offset.x;
		points_to_draw->y = -fdf.points3d->z
			* fdf.camera.zoom + fdf.camera.offset.y;
		fdf.points3d++;
		points_to_draw++;
	}
	points_to_draw->x = INT_MIN;
}

static void	perspective_projection(t_fdf fdf, t_int2 *points_to_draw)
{
	float	distance;

	while (fdf.points3d->x != INT_MIN)
	{
		distance = fdf.camera.projection_distance - fdf.points3d->y;
		points_to_draw->x = fdf.points3d->x / distance
			* fdf.camera.zoom + fdf.camera.offset.x;
		points_to_draw->y = -fdf.points3d->z / distance
			* fdf.camera.zoom + fdf.camera.offset.y;
		fdf.points3d++;
		points_to_draw++;
	}
	points_to_draw->x = INT_MIN;
}

void	refresh_image(t_fdf *fdf)
{
	t_int2			*points_to_draw;
	void			*img;
	t_image_data	img_data;

	img = mlx_new_image(fdf->mlx, WINX, WINY);
	img_data.buffer = mlx_get_data_addr(img, &img_data.pixel_bits, 
			&img_data.line_bytes, &img_data.endian);
	points_to_draw = malloc(sizeof(t_int2)
			* (fdf->map_size.x * fdf->map_size.y + 1));
	if (fdf->camera.perspective_projection)
		perspective_projection(*fdf, points_to_draw);
	else
		isometric_projection(*fdf, points_to_draw);
	draw_map(fdf, points_to_draw, &img_data);
	free(points_to_draw);
	mlx_put_image_to_window(fdf->mlx, fdf->win, img, 0, 0);
	put_instructions(*fdf);
	mlx_destroy_image(fdf->mlx, img);
}
