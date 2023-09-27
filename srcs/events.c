/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 20:34:49 by fernacar          #+#    #+#             */
/*   Updated: 2023/06/30 01:42:03 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	mouse_move(int x, int y, t_fdf *fdf)
{
	fdf->camera.prev_mouse_pos = fdf->camera.mouse_pos;
	fdf->camera.mouse_pos.x = x;
	fdf->camera.mouse_pos.y = y;
	if (fdf->camera.offset_click_down)
	{
		fdf->camera.offset.x += x - fdf->camera.prev_mouse_pos.x;
		fdf->camera.offset.y += y - fdf->camera.prev_mouse_pos.y;
		refresh_image(fdf);
	}
	if (fdf->camera.rot_click_down)
	{
		fdf->camera.rotation.x = x - fdf->camera.prev_mouse_pos.x;
		fdf->camera.rotation.y = y - fdf->camera.prev_mouse_pos.y;
		apply_rotation(fdf->points3d, fdf->camera.rotation);
		refresh_image(fdf);
	}
	return (0);
}

int	mouse_click_down(int button, int x, int y, t_fdf *fdf)
{
	x = y;
	y = x;
	if (button == 1)
		fdf->camera.rot_click_down = 1;
	else if (button == 2)
		fdf->camera.offset_click_down = 1;
	else if (button == 4)
	{
		fdf->camera.zoom *= 1.2;
		refresh_image(fdf);
	}
	else if (button == 5)
	{
		fdf->camera.zoom *= 0.85;
		refresh_image(fdf);
	}
	return (0);
}

int	mouse_click_up(int button, int x, int y, t_fdf *fdf)
{
	x = y;
	y = x;
	if (button == 1)
		fdf->camera.rot_click_down = 0;
	else if (button == 2)
		fdf->camera.offset_click_down = 0;
	return (0);
}

int	key_down(int keycode, t_fdf *fdf)
{
	if (keycode == 0xFF1B)
		close_app(fdf);
	else if (keycode == 0x0070)
	{
		switch_projection(fdf);
		refresh_image(fdf);
	}
	else if (keycode == 0x0063)
	{
		switch_colors(fdf);
		refresh_image(fdf);
	}
	return (0);
}

int	client_message(t_fdf *fdf)
{
	close_app(fdf);
	return (0);
}
