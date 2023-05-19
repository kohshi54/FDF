#include "fdf.h"
#include <mlx.h>
#include <unistd.h>
#include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

typedef	struct line_info
{
	int		dx;
	int		dy;
	int		x;
	int		y;
	size_t	deltaA;
	size_t	deltaB;
	int		nabla;
}	t_line_info	;

void	put_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	t_line_info	info;
	size_t		i;

	if (x0 < x1) info.dx = 1; else info.dx = -1;
	if (y0 < y1) info.dy = 1; else info.dy = -1;

	info.x = x0;
	info.y = y0;
	put_pixel(data, info.x, info.y, color);

	info.deltaA = fabs((float)(x1 - x0));
	info.deltaB = fabs((float)(y1 - y0));

	if (info.deltaA > info.deltaB)
	{
		info.nabla = 2 * info.deltaB - info.deltaA;
		i = 0;
		while (++i <= info.deltaA)
		{
			if (info.nabla >= 0)
			{
				info.nabla = info.nabla + 2 * info.deltaB - 2 * info.deltaA;
				info.y = info.y + info.dy;
			}
			else
			{
				info.nabla = info.nabla + 2 * info.deltaB;
			}
			info.x = info.x + info.dx;
			put_pixel(data, info.x, info.y, color);
		}
	}
	else
	{
		info.nabla = 2 * info.deltaA - info.deltaB;
		i = 0;
		while (++i <= info.deltaB)
		{
			if (info.nabla >= 0)
			{
				info.nabla = info.nabla + 2 * info.deltaA - 2 * info.deltaB;
				info.x = info.x + info.dx;
			}
			else
			{
				info.nabla = info.nabla + 2 * info.deltaA;
			}
			info.y = info.y + info.dy;
			put_pixel(data, info.x, info.y, color);
		}
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


	put_line(&img, 10, 10, 100, 100, 0x00FF0000);
	put_line(&img, 10, 10, 200, 100, 0x00FF0000);
	put_line(&img, 10, 10, 100, 200, 0x00FF0000);
	put_line(&img, 10, 100, 100, 10, 0x00FF0000);
	put_line(&img, 10, 10, 100, 10, 0x00FF0000);
	put_line(&img, 10, 10, 10, 100, 0x00FF0000);
	// put_line(&img, 10, 10, 200, 100, 0x00FF0000);
	// put_line(&img, 10, 10, 100, 200, 0x00FF0000);
	// put_line(&img, 10, 10, 10, 100, 0x00FF0000);
	// put_line(&img, 10, 10, 100, 10, 0x00FF0000);
	// put_line(&img, 10, 100, 200, 10, 0x00FF0000);
	// put_line(&img, 10, 100, 100, 10, 0x00FF0000);
	put_line(&img, 300, 300, 300, 400, 0x00FF0000);
	put_line(&img, 300, 300, 400, 300, 0x00FF0000);
	put_line(&img, 300, 300, 400, 400, 0x00FF0000);
	put_line(&img, 300, 400, 400, 400, 0x00FF0000);
	put_line(&img, 400, 300, 400, 400, 0x00FF0000);
	put_line(&img, 300, 300, 350, 250, 0x00FF0000);
	put_line(&img, 400, 300, 450, 250, 0x00FF0000);
	put_line(&img, 350, 250, 450, 250, 0x00FF0000);
	put_line(&img, 450, 250, 450, 350, 0x00FF0000);
	put_line(&img, 400, 400, 450, 350, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}