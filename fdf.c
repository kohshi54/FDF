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

t_coordinate	zoom_in(t_coordinate	coordinate)
{
	coordinate.x /= 2;
	coordinate.y /= 2;
	coordinate.z /= 2;
	return (coordinate);
}

t_coordinate	zoom_out(t_coordinate	coordinate)
{
	coordinate.x *= 2;
	coordinate.y *= 2;
	coordinate.z *= 2;
	return (coordinate);
}

t_coordinate	move(t_coordinate	coordinate)
{
	coordinate.x += 100;
	coordinate.y += 100;
	coordinate.z += 100;
	return (coordinate);
}


t_coordinate	translate(t_coordinate	coordinate)
{
	t_coordinate	new;
	double			radian;

	radian = atan(1);
	new = rotate_z(coordinate, radian);
	radian = atan2(M_SQRT2, 1);
	new = rotate_x(new, radian);
	new = zoom_in(new);
	new = move(new);
	return (new);
}

void	put_axis(t_data img)
{
	// 座標軸
	t_coordinate	origin = {0, 0, 0};

	put_line(&img, origin, (t_coordinate){400, 0, 0}, 0xC3FF0000);
	put_line(&img, origin, (t_coordinate){0, 400, 0}, 0xC300FF00);

	put_line(&img, translate((t_coordinate){0, 0, 0}), translate((t_coordinate){500, 0, 0}), 0x00FF0000);
	put_line(&img, translate(origin), translate((t_coordinate){0, 500, 0}), 0x0000FF00);
	put_line(&img, origin, (t_coordinate){0, -400, 0}, 0x000000FF);
}

void	put_cube(t_data img)
{
	// 立方体の各座標
	t_coordinate	a = {0, 0, 0};
	t_coordinate	b = {100, 0, 0};
	t_coordinate	c = {0, 100, 0};
	t_coordinate	d = {100, 100, 0};
	t_coordinate	e = {0, 0, 100};
	t_coordinate	f = {100, 0, 100};
	t_coordinate	g = {0, 100, 100};
	t_coordinate	h = {100, 100, 100};

	put_line(&img, translate(a), translate(b), 0x00FFFFFF);
	put_line(&img, translate(a), translate(c), 0x00FFFFFF);
	put_line(&img, translate(d), translate(b), 0x00FFFFFF);
	put_line(&img, translate(d), translate(c), 0x00FFFFFF);

	put_line(&img, translate(e), translate(f), 0x00FFFFFF);
	put_line(&img, translate(e), translate(g), 0x00FFFFFF);
	put_line(&img, translate(h), translate(f), 0x00FFFFFF);
	put_line(&img, translate(h), translate(g), 0x00FFFFFF);

	put_line(&img, translate(a), translate(e), 0x00FFFFFF);
	put_line(&img, translate(b), translate(f), 0x00FFFFFF);
	put_line(&img, translate(c), translate(g), 0x00FFFFFF);
	put_line(&img, translate(d), translate(h), 0x00FFFFFF);

}

typedef struct	s_mlx_info {
	void	*mlx;
	void	*mlx_win;
	t_data	img;
}				t_mlx_info;

int	key_hook(int keycode, t_mlx_info *vars)
{
	(void)vars;
	(void)keycode;
	// ft_printf("Hello from key_hook!\n");
	return (0);
}

int	close_win(int keycode, t_mlx_info *vars)
{
	// close when tab key is pressed.
	if (keycode == '0')
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	loop_handler(t_mlx_info *mlx_info)
{
	mlx_info->img.img = mlx_new_image(mlx_info->mlx, 1920, 1080);
	mlx_info->img.addr = mlx_get_data_addr(mlx_info->img.img, &(mlx_info->img.bits_per_pixel), &(mlx_info->img.line_length), &(mlx_info->img.endian));
	put_axis(mlx_info->img);
	put_cube(mlx_info->img);
	mlx_put_image_to_window(mlx_info->mlx, mlx_info->mlx_win, mlx_info->img.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_mlx_info	mlx_info;

	mlx_info.mlx = mlx_init();
	mlx_info.mlx_win = mlx_new_window(mlx_info.mlx, 1920, 1080, "Hello world!");
	mlx_key_hook(mlx_info.mlx_win, key_hook, &mlx_info);
	mlx_hook(mlx_info.mlx_win, 2, 1L<<0, close_win, &mlx_info);
	mlx_loop_hook(mlx_info.mlx, loop_handler, &mlx_info);
	mlx_loop(mlx_info.mlx);
}