#include <stdio.h>
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
			printf("(%2d, %2d, %2d)", map[i][j]->x, map[i][j]->y, map[i][j]->z);
			// printf("%3d", map[i][j]->z);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	fill_line(t_coordinate ***map, char **line_spl, size_t counter_y, size_t width)
{
	size_t	counter_x;

	counter_x = 0;
	// while (line_spl[counter_y])
	while (counter_x < width)
	{
		map[counter_y][counter_x] = malloc(sizeof(t_coordinate));
		map[counter_y][counter_x]->x = counter_x;
		map[counter_y][counter_x]->y = counter_y;
		map[counter_y][counter_x]->z = ft_atoi(line_spl[counter_x]);
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
	// printf("height: %zu\n", map_info->height);
	// printf("width: %zu\n", map_info->width);
	map_info->map = malloc(sizeof(t_coordinate *) * map_info->height);
	fd = open(filename, O_RDONLY);
	counter_y = 0;
	// while ((line = get_next_line(fd)))
	while (counter_y < map_info->height)
	{
		line = get_next_line(fd);
		map_info->map[counter_y] = malloc(sizeof(t_coordinate *) * map_info->width);
		line_spl = ft_split(line, ' ');
		fill_line(map_info->map, line_spl, counter_y, map_info->width);
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