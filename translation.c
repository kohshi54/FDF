/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:53:35 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/05/30 20:53:35 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coordinate	move_map_to_win_center(t_coordinate vertex)
{
	vertex.x += WIN_WIDTH / 2;
	vertex.y += WIN_HEIGHT / 2;
	return (vertex);
}

t_coordinate	move_map_center_to_origin(t_coordinate vertex, \
											t_map_info map_info)
{
	vertex.x -= map_info.width / 2;
	vertex.y -= map_info.height / 2;
	return (vertex);
}

t_coordinate	move(t_coordinate vertex, int x, int y)
{
	vertex.x += x;
	vertex.y += y;
	return (vertex);
}

t_coordinate	zoom(t_coordinate vertex, int scale)
{
	vertex.x *= scale;
	vertex.y *= scale;
	vertex.z *= scale;
	return (vertex);
}

t_coordinate	translate(t_coordinate vertex, t_map_info map_info, \
													double base[3][3])
{
	t_coordinate	new;

	vertex = move_map_center_to_origin(vertex, map_info);
	vertex = zoom(vertex, map_info.scale);
	new.x = vertex.x * base[0][0] + vertex.y * base[0][1] \
									+ vertex.z * base[0][2];
	new.y = vertex.x * base[1][0] + vertex.y * base[1][1] \
									+ vertex.z * base[1][2];
	new.z = vertex.x * base[2][0] + vertex.y * base[2][1] \
									+ vertex.z * base[2][2];
	new = move_map_to_win_center(new);
	new = move(new, map_info.origin_x, map_info.origin_y);
	return (new);
}
