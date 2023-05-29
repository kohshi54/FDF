#include "fdf.h"

t_coordinate	rotate_x(t_coordinate	coordinate, double radian)
{
	t_coordinate	new;

	new.x = coordinate.x;
	new.y = coordinate.y * cos(radian) - coordinate.z * sin(radian);
	new.z = coordinate.y * sin(radian) + coordinate.z * cos(radian);
	return (new);
}

t_coordinate	rotate_y(t_coordinate	coordinate, double radian)
{
	t_coordinate	new;

	new.x = coordinate.z * sin(radian) + coordinate.x * cos(radian);
	new.y = coordinate.y;
	new.z = coordinate.z * cos(radian) - coordinate.x * sin(radian);
	return (new);
}

t_coordinate	rotate_z(t_coordinate	coordinate, double radian)
{
	t_coordinate	new;

	new.x = coordinate.x * cos(radian) - coordinate.y * sin(radian);
	new.y = coordinate.x * sin(radian) + coordinate.y * cos(radian);
	new.z = coordinate.z;
	return (new);
}

t_coordinate	move(t_coordinate coordinate)
{
	t_coordinate	new;

	new.x = coordinate.x + 200;
	new.y = coordinate.y + 200;
	new.z = coordinate.z + 200;
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
	base_vector[0][0] = 1/sqrt(2);
	base_vector[1][0] = -1/sqrt(2);
	base_vector[2][0] = 0;

	base_vector[0][1] = 1/sqrt(6);
	base_vector[1][1] = 1/sqrt(6);
	base_vector[2][1] = -2/sqrt(6);

	base_vector[0][2] = 1 / sqrt(3);
	base_vector[1][2] = 1 / sqrt(3);
	base_vector[2][2] = 1 / sqrt(3);
}

void	get_and_set_inverse_matrix(double base_vector[3][3])
{
	double	tmp_matrix[3][3];

	tmp_matrix[0][0] = base_vector[0][0];
	tmp_matrix[0][1] = base_vector[1][0];
	tmp_matrix[0][2] = base_vector[2][0];

	tmp_matrix[1][0] = base_vector[0][1];
	tmp_matrix[1][1] = base_vector[1][1];
	tmp_matrix[1][2] = base_vector[2][1];

	tmp_matrix[2][0] = base_vector[0][2];
	tmp_matrix[2][1] = base_vector[1][2];
	tmp_matrix[2][2] = base_vector[2][2];

	size_t	i;
	size_t	j;
	j = 0;
	while (j < 3)
	{
		i = 0;
		while (i < 3)
		{
			base_vector[j][i] = tmp_matrix[j][i];
			i++;
		}
		j++;
	}
}

t_coordinate	translate(t_coordinate	P)
{
	t_coordinate	new;
	double	base_vector[3][3];

	set_default_base_vector(base_vector);
	get_and_set_inverse_matrix(base_vector);
	P = scale_up(P);
	new.x = P.x * base_vector[0][0] + P.y * base_vector[0][1] + P.z * base_vector[0][2];
	new.y = P.x * base_vector[1][0] + P.y * base_vector[1][1] + P.z * base_vector[1][2];
	new.z = P.x * base_vector[2][0] + P.y * base_vector[2][1] + P.z * base_vector[2][2];

	new = move(new);
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
			{
				// put_line(&img, *(map_info.map[i][j]), *(map_info.map[i + 1][j]), 0x00FF0000);
				put_line(&img, translate(*(map_info.map[i][j])), translate(*(map_info.map[i + 1][j])), 0x00FFFFFF);
			}
			if (j < map_info.width - 1)
			{
				// put_line(&img, *(map_info.map[i][j]), *(map_info.map[i][j + 1]), 0x0000FF00);
				put_line(&img, translate(*(map_info.map[i][j])), translate(*(map_info.map[i][j + 1])), 0x00FFFFFF);
			}
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
	mlx_loop_hook(mlx_info.mlx, loop_handler, &mlx_info);
	mlx_loop(mlx_info.mlx);
	return (0);
}