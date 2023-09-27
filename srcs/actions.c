/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 23:33:01 by fernacar          #+#    #+#             */
/*   Updated: 2023/06/30 01:41:55 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	switch_colors(t_fdf *fdf)
{
	if (fdf->colors == fdf->original_colors)
		fdf->colors = fdf->height_colors;
	else
		fdf->colors = fdf->original_colors;
}

void	switch_projection(t_fdf *fdf)
{
	fdf->camera.perspective_projection = !fdf->camera.perspective_projection;
	if (fdf->camera.perspective_projection)
		fdf->camera.zoom *= fdf->camera.projection_distance;
	else
		fdf->camera.zoom /= fdf->camera.projection_distance;
}

void	apply_rotation(t_float3 *points3d, t_int2 direction)
{
	while (points3d->x != INT_MIN)
	{
		*points3d = rotate_point_around_z(*points3d, -direction.x);
		*points3d = rotate_point_around_x(*points3d, -direction.y);
		points3d++;
	}
}

void	close_app(t_fdf *fdf)
{
	mlx_loop_end(fdf->mlx);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	free(fdf->points3d);
	free(fdf->original_colors);
	free(fdf->height_colors);
	exit(0);
}
