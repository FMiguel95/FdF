/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathf_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 23:14:15 by fernacar          #+#    #+#             */
/*   Updated: 2023/06/30 01:42:14 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_float3	rotate_point_around_x(t_float3 point, float angle)
{
	float	angle_rad;
	float	cos_theta;
	float	sin_theta;
	float	temp_y;
	float	temp_z;

	angle_rad = angle * (3.14159265358979323846 / 180.0);
	cos_theta = cosf(angle_rad);
	sin_theta = sinf(angle_rad);
	temp_y = point.y;
	temp_z = point.z;
	point.y = temp_y * cos_theta - temp_z * sin_theta;
	point.z = temp_y * sin_theta + temp_z * cos_theta;
	return (point);
}

t_float3	rotate_point_around_z(t_float3 point, float angle)
{
	float	angle_rad;
	float	cos_theta;
	float	sin_theta;
	float	temp_x;
	float	temp_y;

	angle_rad = angle * (3.14159265358979323846 / 180.0);
	cos_theta = cosf(angle_rad);
	sin_theta = sinf(angle_rad);
	temp_x = point.x;
	temp_y = point.y;
	point.x = temp_x * cos_theta - temp_y * sin_theta;
	point.y = temp_x * sin_theta + temp_y * cos_theta;
	return (point);
}

int	interpolate_color(int color1, int color2, float t)
{
	t_color	c1;
	t_color	c2;
	int		r;
	int		g;
	int		b;

	c1.r = (color1 >> 16) & 0xFF;
	c1.g = (color1 >> 8) & 0xFF;
	c1.b = color1 & 0xFF;
	c2.r = (color2 >> 16) & 0xFF;
	c2.g = (color2 >> 8) & 0xFF;
	c2.b = color2 & 0xFF;
	r = c1.r + (int)((c2.r - c1.r) * t);
	g = c1.g + (int)((c2.g - c1.g) * t);
	b = c1.b + (int)((c2.b - c1.b) * t);
	return ((r << 16) | (g << 8) | b);
}
