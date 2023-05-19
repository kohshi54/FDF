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
}	t_line_info	;

void	put_line_landscape(t_data *data, t_line_info info, int color)
{
	int		nabla;
	size_t	i;

	nabla = 2 * info.deltaB - info.deltaA;
	i = 0;
	while (++i <= info.deltaA)
	{
		if (nabla >= 0)
		{
			nabla = nabla + 2 * info.deltaB - 2 * info.deltaA;
			info.y = info.y + info.dy;
		}
		else
		{
			nabla = nabla + 2 * info.deltaB;
		}
		info.x = info.x + info.dx;
		put_pixel(data, info.x, info.y, color);
	}	
}

void	put_line_portrait(t_data *data, t_line_info info, int color)
{
	int		nabla;
	size_t	i;

	nabla = 2 * info.deltaA - info.deltaB;
	i = 0;
	while (++i <= info.deltaB)
	{
		if (nabla >= 0)
		{
			nabla = nabla + 2 * info.deltaA - 2 * info.deltaB;
			info.x = info.x + info.dx;
		}
		else
		{
			nabla = nabla + 2 * info.deltaA;
		}
		info.y = info.y + info.dy;
		put_pixel(data, info.x, info.y, color);
	}
}

#ifndef step
# define	step(a, b) a < b ? 1 : -1;
#endif

void	put_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	t_line_info	info;

	info.dx = step(x0, x1);
	info.dy = step(y0, y1);

	info.x = x0;
	info.y = y0;
	put_pixel(data, info.x, info.y, color);

	info.deltaA = fabs((float)(x1 - x0));
	info.deltaB = fabs((float)(y1 - y0));

	if (info.deltaA > info.deltaB)
		put_line_landscape(data, info, color);
	else
		put_line_portrait(data, info, color);
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