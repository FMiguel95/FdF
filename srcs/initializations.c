/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 00:45:58 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/13 18:28:24 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	set_object_limits(t_float3 *points3d, t_object_limits *object_limits)
{
	object_limits->min_x = (float)INT_MAX;
	object_limits->max_x = (float)INT_MIN;
	object_limits->min_y = (float)INT_MAX;
	object_limits->max_y = (float)INT_MIN;
	object_limits->min_z = (float)INT_MAX;
	object_limits->max_z = (float)INT_MIN;
	while (points3d->x != INT_MIN)
	{
		if (points3d->x < object_limits->min_x)
			object_limits->min_x = points3d->x;
		if (points3d->x > object_limits->max_x)
			object_limits->max_x = points3d->x;
		if (points3d->y < object_limits->min_y)
			object_limits->min_y = points3d->y;
		if (points3d->y > object_limits->max_y)
			object_limits->max_y = points3d->y;
		if (points3d->z < object_limits->min_z)
			object_limits->min_z = points3d->z;
		if (points3d->z > object_limits->max_z)
			object_limits->max_z = points3d->z;
		points3d++;
	}
}

void	initialize_zoom(t_fdf *fdf)
{
	float	zoom;
	float	sizes[3];

	sizes[0] = WINX * 0.5f / fdf->object_limits.max_x;
	sizes[1] = WINY * 0.5f / fdf->object_limits.max_y;
	if (fabsf(fdf->object_limits.min_z) > fdf->object_limits.max_z)
		sizes[2] = WINY * 0.5f / fabsf(fdf->object_limits.min_z);
	else
		sizes[2] = WINY * 0.5f / fdf->object_limits.max_z;
	zoom = (float)INT_MAX;
	if (sizes[0] < zoom)
		zoom = sizes[0];
	if (sizes[1] < zoom)
		zoom = sizes[1];
	if (sizes[2] < zoom)
		zoom = sizes[2];
	fdf->camera.zoom = zoom;
}

void	adjust_pivot(t_float3 *points, t_int2 map_size)
{
	while (points->x != INT_MIN)
	{
		points->x -= ((float)map_size.x / 2 - 0.5f);
		points->y -= ((float)map_size.y / 2 - 0.5f);
		points++;
	}
}

void	set_projection_distance(t_fdf *fdf)
{
	if (fabsf(fdf->object_limits.min_x) > fdf->camera.projection_distance)
		fdf->camera.projection_distance = fabsf(fdf->object_limits.min_x);
	if (fabsf(fdf->object_limits.max_x) > fdf->camera.projection_distance)
		fdf->camera.projection_distance = fabsf(fdf->object_limits.max_x);
	if (fabsf(fdf->object_limits.min_y) > fdf->camera.projection_distance)
		fdf->camera.projection_distance = fabsf(fdf->object_limits.min_y);
	if (fabsf(fdf->object_limits.max_y) > fdf->camera.projection_distance)
		fdf->camera.projection_distance = fabsf(fdf->object_limits.max_y);
	if (fabsf(fdf->object_limits.min_z) > fdf->camera.projection_distance)
		fdf->camera.projection_distance = fabsf(fdf->object_limits.min_z);
	if (fabsf(fdf->object_limits.max_z) > fdf->camera.projection_distance)
		fdf->camera.projection_distance = fabsf(fdf->object_limits.max_z);
	fdf->camera.projection_distance *= 1.8f;
}

void	create_height_colors(t_fdf fdf)
{
	int		c_highest;
	int		c_lowest;
	float	t;

	c_highest = 0xFF0000;
	c_lowest = 0x0000FF;
	while (fdf.points3d->x != INT_MIN)
	{
		t = (fdf.points3d->z - fdf.object_limits.min_z)
			/ (fdf.object_limits.max_z - fdf.object_limits.min_z);
		*fdf.height_colors = interpolate_color(c_lowest, c_highest, t);
		fdf.height_colors++;
		fdf.points3d++;
	}
}
