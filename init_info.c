#include "fdf.h"

double	set_initial_scale(t_map_info map_info)
{
	int				up;
	size_t			max;

	up = 1;
	max = 2;
	if (map_info.width <= map_info.height && map_info.depth <= map_info.height)
		max = map_info.height;
	else if (map_info.height <= map_info.depth && map_info.width <= map_info.depth)
		max = map_info.depth;
	else if (map_info.depth <= map_info.width && map_info.height <= map_info.width)
		max = map_info.width;
	up = (WIN_HEIGHT * 0.3) / max;
	if (up == 0)
		up = 2;
	return (up);
}

void	init_map_info(t_map_info *map_info)
{
	map_info->origin_x = 0;
	map_info->origin_y = 0;
	map_info->scale = set_initial_scale(*map_info);
	map_info->theta_rx = 0;
	map_info->theta_ry = 0;
	map_info->theta_rz = 0;
	set_isometric_base(map_info->base);
}

void	init_mlx_info(t_mlx_info *mlx_info, char *filename)
{
	mlx_info->mlx = mlx_init();
	mlx_info->mlx_win = mlx_new_window(mlx_info->mlx, WIN_WIDTH, WIN_HEIGHT, filename);
	mlx_info->img.img = mlx_new_image(mlx_info->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx_info->img.addr = mlx_get_data_addr(mlx_info->img.img, &(mlx_info->img.bits_per_pixel), &(mlx_info->img.line_length), &(mlx_info->img.endian));
	init_map_info(&(mlx_info->map_info));
}