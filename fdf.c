#include "fdf.h"

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