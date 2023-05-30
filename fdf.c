/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:52:53 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/05/30 20:52:53 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_mlx_info	mlx_info;

	if (argc != 2)
		return (0);
	create_map(argv[1], &(mlx_info.map_info));
	init_mlx_info(&mlx_info, argv[1]);
	mlx_hook(mlx_info.mlx_win, 2, 1L << 0, key_handler, &mlx_info);
	mlx_hook(mlx_info.mlx_win, 17, 1L << 0, destory_handler, &mlx_info);
	mlx_loop_hook(mlx_info.mlx, loop_handler, &mlx_info);
	mlx_loop(mlx_info.mlx);
	return (0);
}
