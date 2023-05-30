#include "fdf.h"

void	copy_matrix(double dst[3][3], double src[3][3])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			dst[i][j] = src[i][j];
			j++;
		}
		i++;
	}
}

void	rotate_x(double base[3][3], double radian)
{
	double	tmp[3][3];

	copy_matrix(tmp, base);
	base[0][0] = tmp[0][0];
	base[1][0] = tmp[1][0] * cos(radian) + tmp[2][0] * sin(radian);
	base[2][0] = -tmp[1][0] * sin(radian) + tmp[2][0] * cos(radian);

	base[0][1] = tmp[0][1];
	base[1][1] = tmp[1][1] * cos(radian) + tmp[2][1] * sin(radian);
	base[2][1] = -tmp[1][1] * sin(radian) + tmp[2][1] * cos(radian);

	base[0][2] = tmp[0][2];
	base[1][2] = tmp[1][2] * cos(radian) + tmp[2][2] * sin(radian);
	base[2][2] = -tmp[1][2] * sin(radian) + tmp[2][2] * cos(radian);
}

void	rotate_y(double base[3][3], double radian)
{
	double	tmp[3][3];

	copy_matrix(tmp, base);
	base[0][0] = tmp[2][0] * sin(radian) + tmp[0][0] * cos(radian);
	base[1][0] = tmp[1][0];
	base[2][0] = tmp[2][0] * cos(radian) - tmp[0][0] * sin(radian);

	base[0][1] = tmp[2][1] * sin(radian) + tmp[0][1] * cos(radian);
	base[1][1] = tmp[1][1];
	base[2][1] = tmp[2][1] * cos(radian) - tmp[0][1] * sin(radian);

	base[0][2] = tmp[2][2] * sin(radian) + tmp[0][2] * cos(radian);
	base[1][2] = tmp[1][2];
	base[2][2] = tmp[2][2] * cos(radian) - tmp[0][2] * sin(radian);
}

void	rotate_z(double base[3][3], double radian)
{
	double	tmp[3][3];

	copy_matrix(tmp, base);
	base[0][0] = tmp[0][0] * cos(radian) - tmp[1][0] * sin(radian);
	base[1][0] = tmp[0][0] * sin(radian) + tmp[1][0] * cos(radian);
	base[2][0] = tmp[2][0];

	base[0][1] = tmp[0][1] * cos(radian) - tmp[1][1] * sin(radian);
	base[1][1] = tmp[0][1] * sin(radian) + tmp[1][1] * cos(radian);
	base[2][1] = tmp[2][1];

	base[0][2] = tmp[0][2] * cos(radian) - tmp[1][2] * sin(radian);
	base[1][2] = tmp[0][2] * sin(radian) + tmp[1][2] * cos(radian);
	base[2][2] = tmp[2][2];
}