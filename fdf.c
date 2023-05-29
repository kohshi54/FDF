#include "fdf.h"

void	copy_matrix(double dst[3][3], double src[3][3])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			dst[i][j] = src[i][j];
			j++;
		}
		i++;
	}
}

void	rotate_x(double base[3][3], double radian)
{
	double	tmp[3][3];

	copy_matrix(tmp, base);
	base[0][0] = tmp[0][0];
	base[1][0] = tmp[1][0] * cos(radian) + tmp[2][0] * sin(radian);
	base[2][0] = -tmp[1][0] * sin(radian) + tmp[2][0] * cos(radian);

	base[0][1] = tmp[0][1];
	base[1][1] = tmp[1][1] * cos(radian) + tmp[2][1] * sin(radian);
	base[2][1] = -tmp[1][1] * sin(radian) + tmp[2][1] * cos(radian);

	base[0][2] = tmp[0][2];
	base[1][2] = tmp[1][2] * cos(radian) + tmp[2][2] * sin(radian);
	base[2][2] = -tmp[1][2] * sin(radian) + tmp[2][2] * cos(radian);
}

void	rotate_y(double base[3][3], double radian)
{
	double	tmp[3][3];

	copy_matrix(tmp, base);
	base[0][0] = tmp[2][0] * sin(radian) + tmp[0][0] * cos(radian);
	base[1][0] = tmp[1][0];
	base[2][0] = tmp[2][0] * cos(radian) - tmp[0][0] * sin(radian);

	base[0][1] = tmp[2][1] * sin(radian) + tmp[0][1] * cos(radian);
	base[1][1] = tmp[1][1];
	base[2][1] = tmp[2][1] * cos(radian) - tmp[0][1] * sin(radian);

	base[0][2] = tmp[2][2] * sin(radian) + tmp[0][2] * cos(radian);
	base[1][2] = tmp[1][2];
	base[2][2] = tmp[2][2] * cos(radian) - tmp[0][2] * sin(radian);
}

void	rotate_z(double base[3][3], double radian)
{
	double	tmp[3][3];

	copy_matrix(tmp, base);
	base[0][0] = tmp[0][0] * cos(radian) - tmp[1][0] * sin(radian);
	base[1][0] = tmp[0][0] * sin(radian) + tmp[1][0] * cos(radian);
	base[2][0] = tmp[2][0];

	base[0][1] = tmp[0][1] * cos(radian) - tmp[1][1] * sin(radian);
	base[1][1] = tmp[0][1] * sin(radian) + tmp[1][1] * cos(radian);
	base[2][1] = tmp[2][1];

	base[0][2] = tmp[0][2] * cos(radian) - tmp[1][2] * sin(radian);
	base[1][2] = tmp[0][2] * sin(radian) + tmp[1][2] * cos(radian);
	base[2][2] = tmp[2][2];
}

t_coordinate	move_map_to_win_center(t_coordinate coordinate)
{
	t_coordinate	new;

	new.x = coordinate.x + WIN_WIDTH/2;
	new.y = coordinate.y + WIN_HEIGHT/2;
	return (new);
}

t_coordinate	scale_up(t_coordinate coordinate)
{
	t_coordinate	new;

	new.x = coordinate.x * 20;
	new.y = coordinate.y * 20;
	new.z = coordinate.z * 20;
	return (new);
}

void	set_default_base_vector(double base_vector[3][3])
{
	base_vector[0][0] = 1 / sqrt(2);
	base_vector[1][0] = -1 / sqrt(2);
	base_vector[2][0] = 0;

	base_vector[0][1] = 1 / sqrt(6);
	base_vector[1][1] = 1 / sqrt(6);
	base_vector[2][1] = -2 / sqrt(6);

	base_vector[0][2] = 1 / sqrt(3);
	base_vector[1][2] = 1 / sqrt(3);
	base_vector[2][2] = 1 / sqrt(3);	
/*
	base_vector[0][0] = 1;
	base_vector[1][0] = 0;
	base_vector[2][0] = 0;

	base_vector[0][1] = 0;
	base_vector[1][1] = 1;
	base_vector[2][1] = 0;

	base_vector[0][2] = 0;
	base_vector[1][2] = 0;
	base_vector[2][2] = 1;
*/
}

void	get_and_set_inverse_matrix(double base_vector[3][3])
{
	size_t	x;
	size_t	y;
	double	tmp;

	y = 0;
	while (y < 3)
	{
		x = y + 1;
		while (x < 3)
		{
			tmp = base_vector[y][x];
			base_vector[y][x] = base_vector[x][y];
			base_vector[x][y] = tmp;
			x++;
		}
		y++;
	}
}

t_coordinate	move_map_center_to_origin(t_coordinate P, t_map_info map_info)
{
	P.x -= map_info.width / 2;
	P.y -= map_info.height / 2;
	return (P);
}

t_coordinate	translate(t_coordinate P, t_map_info map_info)
{
	t_coordinate	new;
	double			base[3][3];

	set_default_base_vector(base);
	// rotate_x(base, (45 * M_PI / 180));
	// rotate_y(base, (45 * M_PI / 180));
	// rotate_z(base, (45 * M_PI / 180));
	get_and_set_inverse_matrix(base);

	P = move_map_center_to_origin(P, map_info);
	P = scale_up(P);

	new.x = P.x * base[0][0] + P.y * base[0][1] + P.z * base[0][2];
	new.y = P.x * base[1][0] + P.y * base[1][1] + P.z * base[1][2];
	new.z = P.x * base[2][0] + P.y * base[2][1] + P.z * base[2][2];

	new = move_map_to_win_center(new);
	return (new);
}

int	close_win(int keycode, t_mlx_info *vars)
{
	// close when esc key is pressed.
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	destory_win(t_mlx_info *vars)
{
	// close when x button is pressed.
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(EXIT_SUCCESS);
	return (0);
}

int	loop_handler(t_mlx_info *mlx_info)
{
	draw_map_on_img(mlx_info->map_info, mlx_info->img);
	mlx_put_image_to_window(mlx_info->mlx, mlx_info->mlx_win, mlx_info->img.img, 0, 0);
	return (0);
}

void	draw_map_on_img(t_map_info map_info, t_data img)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map_info.height)
	{
		j = 0;
		while (j < map_info.width)
		{
			if (i < map_info.height - 1)
				put_line(&img, translate(*(map_info.map[i][j]), map_info), translate(*(map_info.map[i + 1][j]), map_info), 0x00FFFFFF);
			if (j < map_info.width - 1)
				put_line(&img, translate(*(map_info.map[i][j]), map_info), translate(*(map_info.map[i][j + 1]), map_info), 0x00FFFFFF);
			j++;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_mlx_info	mlx_info;

	if (argc != 2)
		return (0);
	create_map(argv[1], &(mlx_info.map_info));

	mlx_info.mlx = mlx_init();
	mlx_info.mlx_win = mlx_new_window(mlx_info.mlx, WIN_WIDTH, WIN_HEIGHT, "FDF");
	mlx_info.img.img = mlx_new_image(mlx_info.mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx_info.img.addr = mlx_get_data_addr(mlx_info.img.img, &(mlx_info.img.bits_per_pixel), &(mlx_info.img.line_length), &(mlx_info.img.endian));

	mlx_hook(mlx_info.mlx_win, 2, 1L<<0, close_win, &mlx_info);
	mlx_hook(mlx_info.mlx_win, 17, 1L<<0, destory_win, &mlx_info);
	mlx_loop_hook(mlx_info.mlx, loop_handler, &mlx_info);
	mlx_loop(mlx_info.mlx);
	return (0);
}