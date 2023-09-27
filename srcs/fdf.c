/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:31:31 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/13 18:26:18 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	set_hooks(t_fdf fdf)
{
	mlx_hook(fdf.win, KeyPress, KeyPressMask, key_down, &fdf);
	mlx_hook(fdf.win, DestroyNotify, StructureNotifyMask, client_message, &fdf);
	mlx_hook(fdf.win, MotionNotify, PointerMotionMask, mouse_move, &fdf);
	mlx_hook(fdf.win, ButtonPress, ButtonPressMask, mouse_click_down, &fdf);
	mlx_hook(fdf.win, ButtonRelease, ButtonReleaseMask, mouse_click_up, &fdf);
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac != 2)
		ft_printf("Usage: ./fdf <filename>\n");
	else if (WINX <= 0 || WINY <= 0)
		ft_printf("Invalid window size\n");
	else
	{
		fdf = (t_fdf){0};
		parse_map(av[1], &fdf);
		adjust_pivot(fdf.points3d, fdf.map_size);
		apply_rotation(fdf.points3d, (t_int2){45, 30});
		set_object_limits(fdf.points3d, &fdf.object_limits);
		create_height_colors(fdf);
		set_projection_distance(&fdf);
		fdf.camera.offset = (t_int2){WINX / 2, WINY / 2};
		fdf.colors = fdf.original_colors;
		fdf.mlx = mlx_init();
		fdf.win = mlx_new_window(fdf.mlx, WINX, WINY, "FdF");
		initialize_zoom(&fdf);
		refresh_image(&fdf);
		set_hooks(fdf);
		mlx_loop(fdf.mlx);
	}
	return (0);
}
