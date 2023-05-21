#include "fdf.h"
#include "fcntl.h"
#include <string.h>

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

t_coordinate	translate(t_coordinate	coordinate, double radian)
{
	t_coordinate	new;

	new = rotate_z(coordinate, radian);
	radian = 55 * M_PI / 180.0;
	new = rotate_x(new, radian);
	return (new);
}

// int	main(int argc, char *argv[])
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");

	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	// if (argc != 2)
	// 	return (0);
	// int fd = open(argv[1], O_RDONLY);
	// char	*line;
	// while ((line = get_next_line(fd)))
	// {
	// 	ft_printf("%s\n", line);
	// 	free(line);
	// }

	// 座標軸
	t_coordinate	x_axis;
	x_axis.x = X_WIDTH / 3 - 50;
	x_axis.y = 0;
	x_axis.z = 0;
	t_coordinate	y_axis;
	y_axis.x = 0;
	y_axis.y = Y_WIDTH / 2;
	y_axis.z = 0;
	t_coordinate	z_axis;
	z_axis.x = 0;
	z_axis.y = -(Y_WIDTH / 3);
	z_axis.z = 0;
	t_coordinate	origin;
	origin.x = 0;
	origin.y = 0;
	origin.z = 0;

	// put_line(&img, origin, x_axis, 0x00FF0000);
	// put_line(&img, origin, y_axis, 0x0000FF00);
	// put_line(&img, origin, z_axis, 0x0000FFFF);

	double	radian;
	int	theta = 0;
	radian = theta * M_PI / 180.0;

	t_coordinate	a;
	a.x = 0;
	a.y = 0;
	a.z = 0;

	t_coordinate	b;
	b.x = 100;
	b.y = 0;
	b.z = 0;

	t_coordinate	c;
	c.x = 0;
	c.y = 100;
	c.z = 0;

	t_coordinate	d;
	d.x = 100;
	d.y = 100;
	d.z = 0;

	t_coordinate	e;
	e.x = 0;
	e.y = 0;
	e.z = 100;

	t_coordinate	f;
	f.x = 100;
	f.y = 0;
	f.z = 100;

	t_coordinate	g;
	g.x = 0;
	g.y = 100;
	g.z = 100;

	t_coordinate	h;
	h.x = 100;
	h.y = 100;
	h.z = 100;

	while (theta < 360)
	{
		// put_line(&img, translate(origin, radian), translate(x_axis, radian), 0x00FF0000);
		put_line(&img, translate(origin, radian), translate(y_axis, radian), 0x0000FF00);
		put_line(&img, origin, z_axis, 0x000000FF);
		// bzero(img.addr, X_WIDTH * Y_WIDTH * (img.bits_per_pixel / 8));
		radian = theta * M_PI / 180.0;
		put_line(&img, translate(a, radian), translate(b, radian), 0x00FFFFFF);
		put_line(&img, translate(a, radian), translate(c, radian), 0x00FFFFFF);
		put_line(&img, translate(d, radian), translate(b, radian), 0x00FFFFFF);
		put_line(&img, translate(d, radian), translate(c, radian), 0x00FFFFFF);

		put_line(&img, translate(e, radian), translate(f, radian), 0x00FFFFFF);
		put_line(&img, translate(e, radian), translate(g, radian), 0x00FFFFFF);
		put_line(&img, translate(h, radian), translate(f, radian), 0x00FFFFFF);
		put_line(&img, translate(h, radian), translate(g, radian), 0x00FFFFFF);

		put_line(&img, translate(a, radian), translate(e, radian), 0x00FFFFFF);
		put_line(&img, translate(b, radian), translate(f, radian), 0x00FFFFFF);
		put_line(&img, translate(c, radian), translate(g, radian), 0x00FFFFFF);
		put_line(&img, translate(d, radian), translate(h, radian), 0x00FFFFFF);
		theta += 15;
	}

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// mlx_key_hook(&img, my_key_hook, &theta);
	mlx_loop(mlx);
}