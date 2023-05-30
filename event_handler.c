#include "fdf.h"

void	put_axis(t_data img, t_map_info map_info, double base[3][3])
{
	put_line(&img, translate((t_coordinate){map_info.width/2, map_info.height/2, 0, 0xFFFFFF}, map_info, base), translate((t_coordinate){100, 0, 0, 0xFFFFFF}, map_info, base), 0xFF0000);
	put_line(&img, translate((t_coordinate){map_info.width/2, map_info.height/2, 0, 0xFFFFFF}, map_info, base), translate((t_coordinate){0, 100, 0, 0xFFFFFF}, map_info, base), 0x00FF00);
	put_line(&img, translate((t_coordinate){map_info.width/2, map_info.height/2, 0, 0xFFFFFF}, map_info, base), translate((t_coordinate){0, 0, 100, 0xFFFFFF}, map_info, base), 0x0000FF);

}

void	draw_map_on_img(t_map_info map_info, t_data img)
{
	size_t	i;
	size_t	j;
	double	base[3][3];

	copy_matrix(base, map_info.base);
	rotate_x(base, (map_info.theta_rx * M_PI / 180));
	rotate_y(base, (map_info.theta_ry * M_PI / 180));
	rotate_z(base, (map_info.theta_rz * M_PI / 180));
	set_inverse_base(base);

	if (map_info.axis_flg)
		put_axis(img, map_info, base);

	i = 0;
	while (i < map_info.height)
	{
		j = 0;
		while (j < map_info.width)
		{
			if (i < map_info.height - 1)
				put_line(&img, translate(*(map_info.map[i][j]), map_info, base), translate(*(map_info.map[i + 1][j]), map_info, base), map_info.map[i][j]->color);
			if (j < map_info.width - 1)
				put_line(&img, translate(*(map_info.map[i][j]), map_info, base), translate(*(map_info.map[i][j + 1]), map_info, base), map_info.map[i][j]->color);
			j++;
		}
		i++;
	}
}

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
	ft_bzero(mlx_info->img.addr, WIN_WIDTH * WIN_HEIGHT * (mlx_info->img.bits_per_pixel / 8));
	draw_map_on_img(mlx_info->map_info, mlx_info->img);
	mlx_put_image_to_window(mlx_info->mlx, mlx_info->mlx_win, mlx_info->img.img, 0, 0);
	return (0);
}
