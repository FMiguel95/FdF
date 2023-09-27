/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 21:18:11 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/22 19:49:26 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	initialize_bresenham(t_bresenham *bresenham, t_line line)
{
	bresenham->dx = abs(line.p1.x - line.p0.x);
	bresenham->dy = abs(line.p1.y - line.p0.y);
	if (line.p0.x < line.p1.x)
		bresenham->sx = 1;
	else 
		bresenham->sx = -1;
	if (line.p0.y < line.p1.y)
		bresenham->sy = 1;
	else 
		bresenham->sy = -1;
	bresenham->err = bresenham->dx - bresenham->dy;
}

static void	fbresenham(t_bresenham *bresenham, t_line *line)
{
	bresenham->e2 = 2 * bresenham->err;
	if (bresenham->e2 > -bresenham->dy)
	{
		bresenham->err -= bresenham->dy;
		line->p0.x += bresenham->sx;
	}
	if (bresenham->e2 < bresenham->dx)
	{
		bresenham->err += bresenham->dx;
		line->p0.y += bresenham->sy;
	}
}

static int	point_in_screen(t_int2 point)
{
	return (point.x >= 0 && point.x < WINX && point.y >= 0 && point.y < WINY);
}

void	my_pixel_put(t_int2 point, int color, t_image_data *img_data)
{
	int	pixel;

	if (!point_in_screen(point))
		return ;
	pixel = (point.y * img_data->line_bytes) + (point.x * 4);
	if (img_data->endian == 1)
	{
		img_data->buffer[pixel + 0] = (color >> 24);
		img_data->buffer[pixel + 1] = (color >> 16) & 0xFF;
		img_data->buffer[pixel + 2] = (color >> 8) & 0xFF;
		img_data->buffer[pixel + 3] = (color) & 0xFF;
	}
	else if (img_data->endian == 0)
	{
		img_data->buffer[pixel + 0] = (color) & 0xFF;
		img_data->buffer[pixel + 1] = (color >> 8) & 0xFF;
		img_data->buffer[pixel + 2] = (color >> 16) & 0xFF;
		img_data->buffer[pixel + 3] = (color >> 24);
	}
}

void	draw_line(t_image_data *img_data, t_line line, int c1, int c2)
{
	t_bresenham	bresenham;
	int			color;
	float		t;

	if (!point_in_screen(line.p0) && !point_in_screen(line.p1))
		return ;
	initialize_bresenham(&bresenham, line);
	t = 0.0;
	while (line.p0.x != line.p1.x || line.p0.y != line.p1.y)
	{
		if (point_in_screen(line.p0))
		{
			color = interpolate_color(c1, c2, t);
			my_pixel_put((t_int2){line.p0.x, line.p0.y}, color, img_data);
		}
		fbresenham(&bresenham, &line);
		t += 1.0 / (sqrt(bresenham.dx * bresenham.dx
					+ bresenham.dy * bresenham.dy) + 1);
	}
	color = interpolate_color(c1, c2, t);
	my_pixel_put((t_int2){line.p0.x, line.p0.y}, color, img_data);
}
