/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:32:06 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/13 19:25:29 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <X11/Xlib.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_int2 {
	int	x;
	int	y;
}				t_int2;

typedef struct s_float3 {
	float	x;
	float	y;
	float	z;
}				t_float3;

typedef struct s_color {
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_line {
	t_int2	p0;
	t_int2	p1;
}				t_line;

typedef struct s_image_data{
	int			pixel_bits;
	int			line_bytes;
	int			endian;
	char		*buffer;
}				t_image_data;

typedef struct s_bresenham {
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	x;
	int	y;
	int	e2;
}				t_bresenham;

typedef struct s_object_limits {
	float	min_x;
	float	max_x;

	float	min_y;
	float	max_y;

	float	min_z;
	float	max_z;
}				t_object_limits;

typedef struct s_camera {
	float		zoom;

	t_int2		mouse_pos;
	t_int2		prev_mouse_pos;

	int			offset_click_down;
	t_int2		offset;

	int			rot_click_down;
	t_int2		rotation;

	int			perspective_projection;
	float		projection_distance;
}				t_camera;

typedef struct s_fdf {
	void			*mlx;
	void			*win;
	t_camera		camera;
	t_float3		*points3d;
	int				*colors;
	int				*original_colors;
	int				*height_colors;
	t_int2			map_size;
	t_object_limits	object_limits;
}				t_fdf;

# ifndef WINX
#  define WINX 1000
# endif
# ifndef WINY
#  define WINY 1000
# endif

void		free_split(char **split_ptr);
int			list_length(char **list);
int			points_in_line(char	*line);
int			ft_strpos(char *str, char c);
void		parse_map(char *fdf_path, t_fdf *fdf);

void		set_object_limits(t_float3 *points, t_object_limits *object_limits);
void		initialize_zoom(t_fdf *fdf);
void		adjust_pivot(t_float3 *points, t_int2 map_size);
void		set_projection_distance(t_fdf *fdf);
void		create_height_colors(t_fdf fdf);

int			client_message(t_fdf *fdf);
int			key_down(int keycode, t_fdf *fdf);
int			mouse_click_down(int button, int x, int y, t_fdf *fdf);
int			mouse_click_up(int button, int x, int y, t_fdf *fdf);
int			mouse_move(int x, int y, t_fdf *fdf);

t_float3	rotate_point_around_x(t_float3 point, float angle);
t_float3	rotate_point_around_z(t_float3 point, float angle);
int			interpolate_color(int color1, int color2, float t);

void		apply_rotation(t_float3 *points3d, t_int2 direction);
void		switch_projection(t_fdf *fdf);
void		switch_colors(t_fdf *fdf);
void		close_app(t_fdf *fdf);

void		draw_line(t_image_data *img_data, t_line line, int c1, int c2);

void		refresh_image(t_fdf *fdf);

#endif
