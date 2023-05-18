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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_box(t_data *data, size_t x, size_t y, int color)
{
	size_t	i;
	size_t	j;

	i = 10;
	while (i < x)
	{
		my_mlx_pixel_put(data, i, 10, color);
		my_mlx_pixel_put(data, 10, i, color);
		i++;
	}
	j = 10;
	while (j < y)
	{
		my_mlx_pixel_put(data, i, j, color);
		my_mlx_pixel_put(data, j, i, color);
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
		my_mlx_pixel_put(data, 200 + i, 10 + i, color);
		my_mlx_pixel_put(data, 200 - i, 10 + i, color);
		i++;
	}
	j = 200 - i;
	while (j < 200 + i)
	{
		my_mlx_pixel_put(data, j, 10 + i, color);
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

	draw_box(&img, 100, 100, 0x00FF0000);
	draw_triagngle(&img, 100, 100, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	mlx_loop(mlx);
}