/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:52:39 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/05/31 17:20:59 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_map(t_coordinate ***map, size_t width, size_t height)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			ft_printf("%d ", map[i][j]->z);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

int	get_digit(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int	get_color(char *line, char *hex)
{
	int		i;
	int		num;

	while (ft_isdigit(*line))
		line++;
	line++;
	if (line && !ft_strncmp(line, "0x", 2))
	{
		if (ft_strncmp(line, "0xFFFFFF", 8) == 0)
			return (0xFFFFFF);
		if (ft_strncmp(line, "0xFF0000", 8) == 0)
			return (0xFF0000);
		if (ft_strncmp(line, "0x00FF00", 8) == 0)
			return (0x00FF00);
		if (ft_strncmp(line, "0x0000FF", 8) == 0)
			return (0x00FF00);
		line += 2;
		i = get_digit(line) - 1;
		num = 0;
		while (i >= 0)
			num += (ft_strchr(hex, *line++) - hex) * pow(16, i--);
		return (num);
	}
	return (0xFFFFFF);
}

void	fill_line(t_coordinate ***map, char **line_spl, \
	size_t counter_y, t_map_info *map_info)
{
	size_t	counter_x;

	counter_x = 0;
	while (counter_x < map_info->width)
	{
		map[counter_y][counter_x] = malloc(sizeof(t_coordinate));
		if (!map[counter_y][counter_x])
			exit(EXIT_FAILURE);
		map[counter_y][counter_x]->x = counter_x;
		map[counter_y][counter_x]->y = counter_y;
		map[counter_y][counter_x]->z = ft_atoi(line_spl[counter_x]);
		map[counter_y][counter_x]->color = get_color(line_spl[counter_x], \
			"0123456789abcdef");
		if ((int)map_info->depth < map[counter_y][counter_x]->z)
		{
			map_info->depth = map[counter_y][counter_x]->z;
		}
		counter_x++;
	}
}

void	create_map(char *filename, t_map_info *map_info)
{
	int				fd;
	size_t			counter_y;
	char			*line;
	char			**line_spl;

	map_info->height = get_height(filename);
	map_info->width = get_width(filename);
	map_info->depth = 0;
	map_info->map = malloc(sizeof(t_coordinate *) * map_info->height);
	if (!(map_info->map))
		exit(EXIT_FAILURE);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	counter_y = 0;
	while (counter_y < map_info->height)
	{
		line = get_next_line(fd);
		if (!line)
			exit(EXIT_FAILURE);
		map_info->map[counter_y] = malloc(sizeof(t_coordinate *) \
			* map_info->width);
		if (!(map_info->map[counter_y]))
			exit(EXIT_FAILURE);
		line_spl = ft_split(line, ' ');
		free(line);
		if (!line_spl)
			exit(EXIT_FAILURE);
		fill_line(map_info->map, line_spl, counter_y, map_info);
		free_split(line_spl);
		counter_y++;
	}
}
