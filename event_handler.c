/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:52:49 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/05/30 20:52:49 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_handler(int keycode, t_mlx_info *vars)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit(EXIT_SUCCESS);
	}
	parallel_move(keycode, vars);
	zoom_in_and_out(keycode, vars);
	rotate_x_y_z(keycode, vars);
	projection(keycode, vars);
	axis(keycode, vars);
	return (0);
}

int	destory_handler(t_mlx_info *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(EXIT_SUCCESS);
	return (0);
}

int	loop_handler(t_mlx_info *mlx_info)
{
	ft_bzero(mlx_info->img.addr, WIN_WIDTH * WIN_HEIGHT \
				* (mlx_info->img.bits_per_pixel / 8));
	draw_map_on_img(mlx_info->map_info, mlx_info->img);
	mlx_put_image_to_window(mlx_info->mlx, mlx_info->mlx_win, \
				mlx_info->img.img, 0, 0);
	return (0);
}
