#include "fdf.h"
#include <mlx.h>
#include <unistd.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

#define	DX(a, b) (a > b ? 1 : (-1))
#define	DY(a, b) (a > b ? 1 : (-1))

#include <math.h>
void	line_put(t_data *data, double x0, double y0, double x1, double y1, int color)
{
	double	delta_x;
	double	delta_y;

	delta_x = x1 - x0;
	delta_y = y1 - y0;

	int	dx;
	int	dy;

	dx = DX(x1, x0);
	dy = DY(y1, y0);

	double	x;
	double	y;

	x = x0;
	y = y0;
	if (delta_x > delta_y)
	{
		while (fabs(x - x1) > 1)
		{
			if (delta_y != 0)
				y = y + (delta_y / delta_x) * dy;
			x = x + dx;
			pixel_put(data, x, y, color);
		}
	}
	else
	{
		while (fabs(y - y1) > 1)
		{
			if (delta_x != 0)
				x = x + (delta_x / delta_y) * dx;
			y = y + dy;
			pixel_put(data, x, y, color);
		}
	}
}

void	draw_box(t_data *data, size_t x, size_t y, int color)
{
	size_t	i;
	size_t	j;

	i = 10;
	while (i < x)
	{
		pixel_put(data, i, 10, color);
		pixel_put(data, 10, i, color);
		i++;
	}
	j = 10;
	while (j < y)
	{
		pixel_put(data, i, j, color);
		pixel_put(data, j, i, color);
		j++;
	}
}

void	draw_triagngle(t_data *data, size_t x, size_t y, int color)
{
	size_t	i;
	size_t	j;

	i = 0;
	y++;
	x++;
	while (i < 100)
	{
		pixel_put(data, 200 + i, 10 + i, color);
		pixel_put(data, 200 - i, 10 + i, color);
		i++;
	}
	j = 200 - i;
	while (j < 200 + i)
	{
		pixel_put(data, j, 10 + i, color);
		j++;
	}
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

	line_put(&img, 10, 10, 300, 100, 0x00FF0000);
	line_put(&img, 100, 100, 300, 100, 0x00FF0000);
	line_put(&img, 100, 100, 10, 10, 0x00FF0000);
	line_put(&img, 10, 10, 100, 300, 0x00FF0000);
	line_put(&img, 100, 100, 100, 500, 0x00FF0000);
	line_put(&img, 300, 100, 100, 500, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}