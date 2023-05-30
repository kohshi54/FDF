#include "fdf.h"

void	set_isometric_base(double base_vector[3][3])
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
}

void	set_standard_base(double base_vector[3][3])
{
	base_vector[0][0] = 1;
	base_vector[1][0] = 0;
	base_vector[2][0] = 0;

	base_vector[0][1] = 0;
	base_vector[1][1] = 1;
	base_vector[2][1] = 0;

	base_vector[0][2] = 0;
	base_vector[1][2] = 0;
	base_vector[2][2] = 1;
}

void	set_inverse_base(double base_vector[3][3])
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