/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:53:21 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/05/31 16:35:51 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parallel_move(int keycode, t_mlx_info *vars)
{
	if (keycode == RIGHT_ARROW)
		vars->map_info.origin_x += 10;
	if (keycode == LEFT_ARROW)
		vars->map_info.origin_x -= 10;
	if (keycode == UP_ARROW)
		vars->map_info.origin_y += 10;
	if (keycode == DOWN_ARROW)
		vars->map_info.origin_y -= 10;
}

void	zoom_in_and_out(int keycode, t_mlx_info *vars)
{
	if (keycode == PLUS_KEY)
		vars->map_info.scale += 1;
	if (keycode == MINUS_KEY)
		if (vars->map_info.scale > 0)
			vars->map_info.scale -= 1;
}

void	rotate_x_y_z(int keycode, t_mlx_info *vars)
{
	if (keycode == X_KEY)
		vars->map_info.theta_rx += 10;
	if (keycode == Y_KEY)
		vars->map_info.theta_ry += 10;
	if (keycode == Z_KEY)
		vars->map_info.theta_rz += 10;
}

void	projection(int keycode, t_mlx_info *vars)
{
	if (keycode == P_KEY)
	{
		set_standard_base(vars->map_info.base);
		vars->map_info.theta_rx = 0;
		vars->map_info.theta_ry = 0;
		vars->map_info.theta_rz = 0;
	}
	if (keycode == I_KEY)
	{
		set_isometric_base(vars->map_info.base);
		vars->map_info.theta_rx = 0;
		vars->map_info.theta_ry = 0;
		vars->map_info.theta_rz = 0;
	}
}

void	axis(int keycode, t_mlx_info *vars)
{
	if (keycode == A_KEY)
	{
		if (vars->map_info.axis_flg)
			vars->map_info.axis_flg = 0;
		else
			vars->map_info.axis_flg = 1;
	}
}
