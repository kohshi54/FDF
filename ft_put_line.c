/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:53:04 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/05/30 20:53:04 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if ((0 <= y && y < WIN_HEIGHT) && (0 <= x && x < WIN_WIDTH))
	{
		dst = data->addr + (y * data->line_length + x * \
				(data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	put_line_landscape(t_data *data, t_line_info info, int color)
{
	int		nabla;
	size_t	i;

	nabla = 2 * info.delta_b - info.delta_a;
	i = 0;
	while (++i <= info.delta_a)
	{
		if (nabla >= 0)
		{
			nabla = nabla + 2 * info.delta_b - 2 * info.delta_a;
			info.y = info.y + info.dy;
		}
		else
		{
			nabla = nabla + 2 * info.delta_b;
		}
		info.x = info.x + info.dx;
		put_pixel(data, info.x, info.y, color);
	}
}

void	put_line_portrait(t_data *data, t_line_info info, int color)
{
	int		nabla;
	size_t	i;

	nabla = 2 * info.delta_a - info.delta_b;
	i = 0;
	while (++i <= info.delta_b)
	{
		if (nabla >= 0)
		{
			nabla = nabla + 2 * info.delta_a - 2 * info.delta_b;
			info.x = info.x + info.dx;
		}
		else
		{
			nabla = nabla + 2 * info.delta_a;
		}
		info.y = info.y + info.dy;
		put_pixel(data, info.x, info.y, color);
	}
}

int	get_step(int a, int b)
{
	if (a < b)
		return (1);
	return (-1);
}

void	put_line(t_data *data, t_coordinate start, t_coordinate end, int color)
{
	t_line_info	info;
	int			x0;
	int			y0;
	int			x1;
	int			y1;

	x0 = start.x;
	y0 = start.y;
	x1 = end.x;
	y1 = end.y;
	info.dx = get_step(x0, x1);
	info.dy = get_step(y0, y1);
	info.x = x0;
	info.y = y0;
	put_pixel(data, info.x, info.y, color);
	info.delta_a = fabs((float)(x1 - x0));
	info.delta_b = fabs((float)(y1 - y0));
	if (info.delta_a > info.delta_b)
		put_line_landscape(data, info, color);
	else
		put_line_portrait(data, info, color);
}
