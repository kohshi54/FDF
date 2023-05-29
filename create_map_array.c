#include "fdf.h"

/*
#include <stdio.h>
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
			// printf("(%2d, %2d, %2d, 0x%x)", map[i][j]->x, map[i][j]->y, map[i][j]->z, map[i][j]->color);
			printf("%d,0x%x\n", map[i][j]->z, map[i][j]->color);
			// printf("%3d", map[i][j]->z);
			j++;
		}
		printf("\n");
		i++;
	}
}
*/

int		get_digit(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int		get_color(char *line)
{
	int		i;
	int		num;
	char	*hex;

	while (ft_isdigit(*line))
		line++;
	if (line && *line == ',')
	{
		line++;
		if (ft_strncmp(line, "0x", 2) == 0)
		{
			if (ft_strncmp(line, "0xFFFFFF", 8) == 0)
				return (0xFFFFFF);
			if (ft_strncmp(line, "0xFF0000", 8) == 0)
				return (0xFF0000);
			if (ft_strncmp(line, "0x00FF00", 8) == 0)
				return (0x00FF00);
			if (ft_strncmp(line, "0x0000FF", 8) == 0)
				return (0x00FF00);
			hex = "0123456789abcdef";
			line += 2;
			i = get_digit(line) - 1;
			num = 0;
			while (i >= 0)
				num += (ft_strchr(hex, *line++) - hex) * pow(16, i--);;
			return (num);
		}
	}
	return (0xFFFFFF);
}

void	fill_line(t_coordinate ***map, char **line_spl, size_t counter_y, size_t width, t_map_info *map_info)
{
	size_t	counter_x;

	counter_x = 0;
	while (counter_x < width)
	{
		map[counter_y][counter_x] = malloc(sizeof(t_coordinate));
		map[counter_y][counter_x]->x = counter_x;
		map[counter_y][counter_x]->y = counter_y;
		map[counter_y][counter_x]->z = ft_atoi(line_spl[counter_x]);
		map[counter_y][counter_x]->color = get_color(line_spl[counter_x]);
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
	fd = open(filename, O_RDONLY);
	counter_y = 0;
	while (counter_y < map_info->height)
	{
		line = get_next_line(fd);
		map_info->map[counter_y] = malloc(sizeof(t_coordinate *) * map_info->width);
		line_spl = ft_split(line, ' ');
		fill_line(map_info->map, line_spl, counter_y, map_info->width, map_info);
		counter_y++;
	}
}

/*
int	main(int argc, char *argv[])
{
	t_map_info	map_info;

	if (argc != 2)
		return (0);
	create_map(argv[1], &map_info);
	print_map(map_info.map, map_info.width, map_info.height);
	return (0);
}
*/