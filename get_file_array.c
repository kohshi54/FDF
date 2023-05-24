#include "LIBFT/get_next_line.h"
#include "LIBFT/libft.h"
#include "fcntl.h"
#include <stdio.h>
int	get_height(char *filename);
int	get_width(char *filename);

typedef	struct s_coordinate
{
	int					x;
	int					y;
	int					z;
}	t_coordinate;

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
			// printf("(%d, %d, %d)", map[i][j]->x, map[i][j]->y, map[i][j]->z);
			printf("%d ", map[i][j]->z);
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

t_coordinate	***create_map(char *filename)
{
	t_coordinate	***map;
	int				fd;
	size_t			width;
	size_t			height;
	size_t			counter_y;
	char			*line;
	char			**line_spl;

	height = get_height(filename);
	width = get_width(filename);
	map = malloc(sizeof(t_coordinate *) * height);
	fd = open(filename, O_RDONLY);
	counter_y = 0;
	// while ((line = get_next_line(fd)))
	while (counter_y < height)
	{
		line = get_next_line(fd);
		map[counter_y] = malloc(sizeof(t_coordinate *) * width);
		line_spl = ft_split(line, ' ');
		fill_line(map, line_spl, counter_y, width);
		counter_y++;
	}

	// print_map(map, width, height);
	return (map);
}

int	main(int argc, char *argv[])
{
	t_coordinate	***map;

	if (argc != 2)
		return (0);
	map = create_map(argv[1]);

	return (0);
}