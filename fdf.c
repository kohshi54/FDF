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

t_coordinate	translate(t_coordinate	coordinate)
{
	t_coordinate	new;
	double			radian;

	radian = atan(1);
	new = rotate_z(coordinate, radian);
	radian = atan2(M_SQRT2, 1);
	new = rotate_x(new, radian);
	return (new);
}

void	put_axis(t_data img)
{
	// 座標軸
	t_coordinate	x_axis = {X_WIDTH / 3 - 50, 0, 0};
	t_coordinate	y_axis = {0, Y_WIDTH / 2, 0};
	t_coordinate	z_axis = {0, -(Y_WIDTH / 3), 0};
	t_coordinate	origin = {0, 0, 0};

	put_line(&img, origin, (t_coordinate){500, 0, 0}, 0xC3FF0000);
	put_line(&img, origin, (t_coordinate){0, 500, 0}, 0xC300FF00);

	put_line(&img, translate((t_coordinate){0, 0, 0}), translate(x_axis), 0x00FF0000);
	put_line(&img, translate(origin), translate(y_axis), 0x0000FF00);
	put_line(&img, origin, z_axis, 0x000000FF);
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

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");

	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	put_axis(img);
	put_cube(img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// mlx_key_hook(&img, my_key_hook, &theta);
	mlx_loop(mlx);
}