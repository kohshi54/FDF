/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:52:44 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/05/30 20:52:44 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_axis(t_data img, t_map_info map_info, double base[3][3])
{
	put_line(&img, translate((t_coordinate){map_info.width / 2, \
			map_info.height / 2, 0, 0xFFFFFF}, map_info, base), \
			translate((t_coordinate){100, 0, 0, 0xFFFFFF}, \
			map_info, base), 0xFF0000);
	put_line(&img, translate((t_coordinate){map_info.width / 2, \
			map_info.height / 2, 0, 0xFFFFFF}, map_info, base), \
			translate((t_coordinate){0, 100, 0, 0xFFFFFF}, \
			map_info, base), 0x00FF00);
	put_line(&img, translate((t_coordinate){map_info.width / 2, \
			map_info.height / 2, 0, 0xFFFFFF}, map_info, base), \
			translate((t_coordinate){0, 0, 100, 0xFFFFFF}, \
			map_info, base), 0x0000FF);
}

void	rotate_base(t_map_info map_info, double base[3][3], t_data img)
{
	copy_matrix(base, map_info.base);
	rotate_x(base, (map_info.theta_rx * M_PI / 180));
	rotate_y(base, (map_info.theta_ry * M_PI / 180));
	rotate_z(base, (map_info.theta_rz * M_PI / 180));
	set_inverse_base(base);
	if (map_info.axis_flg)
		put_axis(img, map_info, base);
}

void	draw_map_on_img(t_map_info map_info, t_data img)
{
	size_t	i;
	size_t	j;
	double	base[3][3];

	rotate_base(map_info, base, img);
	i = 0;
	while (i < map_info.height)
	{
		j = 0;
		while (j < map_info.width)
		{
			if (i < map_info.height - 1)
				put_line(&img, translate(*(map_info.map[i][j]), \
					map_info, base), translate(*(map_info.map[i + 1][j]), \
					map_info, base), map_info.map[i][j]->color);
			if (j < map_info.width - 1)
				put_line(&img, translate(*(map_info.map[i][j]), \
					map_info, base), translate(*(map_info.map[i][j + 1]), \
					map_info, base), map_info.map[i][j]->color);
			j++;
		}
		i++;
	}
}
